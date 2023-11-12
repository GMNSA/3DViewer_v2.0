#include "../../includes/View/mywidgetopengl.hpp"

#ifdef __LINUX__
#include <GL/gl.h>
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#include <OPenGL/gl.h>
#endif
#include <QColor>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QWheelEvent>

//  координаты вершин (v)
//  координаты текстуры (vt)
//  координаты нормали (vn)
//  Параметры одной поверхности объекта (f)
//  Комментарии (#)

// -------------------------------------------------------

namespace s21 {

MyWidgetOPenGL::MyWidgetOPenGL(IControllerInterface *controller,
                               IFacadeModel *model, QWidget *parent)
    : QOpenGLWidget(parent),
      controller_(controller),
      model_(model),
      label_name_(new QLabel(this)),
      label_vertes_(new QLabel(this)),
      label_polygons_(new QLabel(this)),
      m_layoutH(new QHBoxLayout(this)),
      is_mouse_(false),
      tmp_color_({52, 84, 93}) {
  model_->Attach(qobject_cast<IWidgetOpenglObserver *>(this));

  this->installEventFilter(this);
  resize(800, 600);

  controller_->LoadConfig();

  initialized_ = false;
  DrawInfo();
  // m_labelGifTime->setText("");
  // m_labelGifTime->setAlignment(Qt::AlignTop);
  // m_labelGifTime->setAlignment(Qt::AlignLeft);
  // m_labelGifTime->move(40, 40);
  // m_labelGifTime->raise();
  // QFont font = m_labelGifTime->font();
  // font.setPointSize(20);
  // font.setBold(true);
  // m_labelGifTime->setFont(font);
}

// --------------------------------------------------

MyWidgetOPenGL::~MyWidgetOPenGL() { controller_->WriteConfig("./config.json"); }

// --------------------------------------------------

void MyWidgetOPenGL::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_MULTISAMPLE);  // smoothing the isa
  glClearColor(0.0, 0.1, 0.0, 1.0);

  glEnable(GL_DEPTH_TEST);  // dissabling the buffer deep
  glEnable(GL_CULL_FACE);
  glEnable(GL_LINE_SMOOTH);
  glShadeModel(GL_FLAT);

  initialized_ = true;
}

// --------------------------------------------------

void MyWidgetOPenGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

// --------------------------------------------------

void MyWidgetOPenGL::paintGL() {
  if (!initialized_ || !model_->GetDataViewer().is_valid)
    glClearColor(tmp_color_.redF(), tmp_color_.greenF(), tmp_color_.blueF(),
                 1.0f);
  else
    glClearColor(model_->GetDataViewer().background_color.redF(),
                 model_->GetDataViewer().background_color.greenF(),
                 model_->GetDataViewer().background_color.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  if (!initialized_ || !model_->GetDataViewer().is_valid) {
    return;
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (model_->GetDataViewer().is_valid) {
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    // TODO(_who): We will need to fix (line width - too much fat and tear)
    glLineWidth((GLfloat)model_->GetDataViewer().line_width);

    if (model_->GetDataViewer().line_type == LineType::LINE_STIPPLE) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(3, 255);
    }
    glMatrixMode(GL_MODELVIEW);

    UpdatePerspective();
    DrawObjects(e_typeDraw::TYPE_LINES);

    if (model_->GetDataViewer().line_type == LineType::LINE_STIPPLE) {
      glDisable(GL_LINE_STIPPLE);
    }
    if (model_->GetDataViewer().point_type == PointType::POINT_CIRCLE) {
      glEnable(GL_POINT_SMOOTH);
      glPointSize(model_->GetDataViewer().point_size);
      DrawObjects(e_typeDraw::TYPE_POINTS);
      glDisable(GL_POINT_SMOOTH);
    } else if (model_->GetDataViewer().point_type == PointType::POINT_SQUARE) {
      DrawSquare();
    }
  }
}

// --------------------------------------------------

void MyWidgetOPenGL::wheelEvent(QWheelEvent *event) {
  auto is_decrement = event->angleDelta().ry() < 0 ? 1 : 0;
  (is_decrement) ? controller_->DecrementScale()
                 : controller_->IncremenetScale();
}

// --------------------------------------------------

void MyWidgetOPenGL::mouseMoveEvent(QMouseEvent *event) {
  controller_->TurnObjectX(mouse_position_.x() - event->pos().x());
  controller_->TurnObjectY(mouse_position_.y() - event->pos().y());
  mouse_position_ = event->pos();
}

// --------------------------------------------------

void MyWidgetOPenGL::mousePressEvent(QMouseEvent *event) {
  mouse_position_ = event->pos();
}

// -------------------------------------------------------

void MyWidgetOPenGL::mouseReleaseEvent(QMouseEvent *event) { Q_UNUSED(event); }

// -------------------------------------------------------

bool MyWidgetOPenGL::eventFilter(QObject *watched, QEvent *event) {
  Q_UNUSED(watched);
  bool res = false;

  if (!is_mouse_) {
    if (event->type() == QEvent::Wheel) {
      res = true;
    } else if (event->type() == QEvent::MouseMove) {
      res = true;
    }
  }

  return (res);
}

// -------------------------------------------------------

void MyWidgetOPenGL::TurnOnMouse() { is_mouse_ = true; }
// -------------------------------------------------------

void MyWidgetOPenGL::TurnOffMouse() { is_mouse_ = false; }

// -------------------------------------------------------

void MyWidgetOPenGL::ChangeColorFileInfo(int const &value) {
  if (value == -1) {
    label_name_->setStyleSheet("QLabel { color : white; }");
    label_vertes_->setStyleSheet("QLabel { color : white; }");
    label_polygons_->setStyleSheet("QLabel { color : white; }");
    // emit on_changeColorGifTime(0);
  } else {
    label_name_->setStyleSheet("QLabel { color : grey; }");
    label_vertes_->setStyleSheet("QLabel { color : grey; }");
    label_polygons_->setStyleSheet("QLabel { color : grey; }");
    // emit on_changeColorGifTime(1);
  }
}

// -------------------------------------------------------

void MyWidgetOPenGL::UpdateInfoObject() {
  auto &info = model_->GetDataViewer().info_data;

  label_name_->setText(info.label_name);
  label_vertes_->setText(info.label_vertex);
  label_polygons_->setText(info.label_polygons);
}

// -------------------------------------------------------

void MyWidgetOPenGL::MoveX(float value) { controller_->MoveDirectionX(value); }

// -------------------------------------------------------

void MyWidgetOPenGL::MoveY(float value) { controller_->MoveDirectionY(value); }

// -------------------------------------------------------

void MyWidgetOPenGL::MoveZ(float value) { controller_->MoveDirectionZ(value); }

// -------------------------------------------------------

void MyWidgetOPenGL::DrawObjects(e_typeDraw const &type_draw) {
  auto type = type_draw == 0 ? GL_LINE_LOOP : GL_POINTS;
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  auto point_color = model_->GetDataViewer().point_color;
  auto line_color = model_->GetDataViewer().line_color;
  auto polygons = model_->Polygons();
  size_t n_polygons = polygons.size();
  auto points_array = model_->PointsArray();

  for (size_t i = 1; i < n_polygons; i++) {
    glBegin(type);
    if (type_draw == TYPE_LINES)
      glColor3f(line_color.redF(), line_color.greenF(), line_color.blueF());
    else
      glColor3f(point_color.redF(), point_color.greenF(), point_color.blueF());
    for (size_t j = 0; j < polygons[i].size(); j++) {
      x = points_array[polygons[i][j]].x;
      y = points_array[polygons[i][j]].y;
      z = points_array[polygons[i][j]].z;

      glVertex3f(x, y, z);
    }
    glEnd();
  }
}

// -------------------------------------------------------

void MyWidgetOPenGL::DrawInfo() {
  // label_name_->setText("Name: ");
  // label_vertes_->setText("Vertes: ");
  // label_polygons_->setText("Polygons: ");
  m_layoutH->setAlignment(Qt::AlignTop);
  m_layoutH->addStretch();
  m_layoutH->addWidget(label_name_);
  m_layoutH->addWidget(label_vertes_);
  m_layoutH->addWidget(label_polygons_);
}

// -------------------------------------------------------

void MyWidgetOPenGL::Update() { update(); }

// -------------------------------------------------------

void MyWidgetOPenGL::UpdateInfo() {
  UpdateInfoObject();
  ChangeColorFileInfo(model_->GetDataViewer().background_color.toHsl().hue());
}

// -------------------------------------------------------

void MyWidgetOPenGL::UpdatePerspective() {
  auto tmp_perspective = model_->GetDataViewer().perspective;
  auto size_perspective = model_->GetDataViewer().size_perspective;

  glLoadIdentity();
  if (tmp_perspective == 1) {
    glFrustum(-size_perspective, size_perspective, -size_perspective,
              size_perspective, size_perspective / 2.5, size_perspective * 2);
    glTranslatef(0, 0, -size_perspective / 2.5 * 3);
  } else if (tmp_perspective == 0) {
    glOrtho(-size_perspective, size_perspective, -size_perspective,
            size_perspective, -size_perspective, size_perspective);
  }
}

// -------------------------------------------------------

void MyWidgetOPenGL::ClearInfo() {
  label_name_->setText("");
  label_vertes_->setText("");
  label_polygons_->setText("");
}

// -------------------------------------------------------

void MyWidgetOPenGL::DrawSquare() {
  auto point_color = model_->GetDataViewer().point_color;
  glColor3f(point_color.redF(), point_color.greenF(), point_color.blueF());
  double x, y, z, del = model_->GetDataViewer().perspective == 1 ? 9 : 23;
  del = model_->GetDataViewer().max_perspective / del *
        model_->GetDataViewer().point_size / 20;
  auto polygons = model_->Polygons();
  size_t n_polygons = polygons.size();
  auto points_array = model_->PointsArray();

  for (size_t i = 1; i < n_polygons; i++) {
    for (size_t j = 0; j < polygons[i].size(); j++) {
      glBegin(GL_POLYGON);
      x = points_array[polygons[i][j]].x;
      y = points_array[polygons[i][j]].y;
      z = points_array[polygons[i][j]].z;
      glVertex3f(x - del, y - del, z);
      glVertex3f(x + del, y - del, z);
      glVertex3f(x + del, y + del, z);
      glVertex3f(x - del, y + del, z);
      glEnd();
    }
  }
}

// void MainWindow::changeColorGifTime(int isBlack_) {
//   Q_UNUSED(isBlack_);
//   if (isBlack_)
//     m_labelGifTime->setStyleSheet("QLabel { color : black; }");
//   else
//     m_labelGifTime->setStyleSheet("QLabel { color : white; }");
// }

// -------------------------------------------------------

}  // namespace s21
