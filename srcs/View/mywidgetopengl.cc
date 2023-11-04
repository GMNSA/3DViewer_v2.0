#include "../../includes/View/mywidgetopengl.hpp"

#ifdef __LINUX__
#include <GL/gl.h>
#include <GL/glut.h>
#else
// #include <GLUT/glut.h>
// #include <OPenGL/gl.h>
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
                               IModelViewer *model, QWidget *parent)
    : QOpenGLWidget(parent),
      controller_(controller),
      model_(model),
      label_name_(new QLabel(this)),
      label_vertes_(new QLabel(this)),
      label_polygons_(new QLabel(this)),
      m_layoutH(new QHBoxLayout(this)),
      m_isMouse(false),
      m_tmpColor({152, 84, 93}) {
  model_->Attach(qobject_cast<IWidgetOpenglObserver *>(this));

  this->installEventFilter(this);
  resize(800, 600);

  controller_->LoadConfig();

  initialized_ = false;
  drawInfo();
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
  if (!initialized_ || !model_->get_is_valid())
    glClearColor(m_tmpColor.redF(), m_tmpColor.greenF(), m_tmpColor.blueF(),
                 1.0f);
  else
    glClearColor(model_->get_background_color().redF(),
                 model_->get_background_color().greenF(),
                 model_->get_background_color().blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  if (!initialized_ || !model_->get_is_valid()) {
    return;
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (model_->get_is_valid()) {
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    // TODO(_who): We will need to fix (line width - too much fat and tear)
    glLineWidth((GLfloat)model_->get_line_width());

    if (model_->get_line_type() == LineType::LINE_STIPPLE) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(3, 255);
    }
    glMatrixMode(GL_MODELVIEW);

    updatePerspective();
    drawObjects(e_typeDraw::TYPE_LINES);

    if (model_->get_line_type() == LineType::LINE_STIPPLE) {
      glDisable(GL_LINE_STIPPLE);
    }
    if (model_->get_point_type() == PointType::POINT_CIRCLE) {
      glEnable(GL_POINT_SMOOTH);
      glPointSize(model_->get_point_size());
      drawObjects(e_typeDraw::TYPE_POINTS);
      glDisable(GL_POINT_SMOOTH);
    } else if (model_->get_point_type() == PointType::POINT_SQUARE) {
      drawSquare();
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
  model_->set_rotate_x(mouse_position_.x() - event->pos().x());
  model_->set_rotate_y(mouse_position_.y() - event->pos().y());
  mouse_position_ = event->pos();
  ChangeRotate();
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

  if (!m_isMouse) {
    if (event->type() == QEvent::Wheel) {
      res = true;
    } else if (event->type() == QEvent::MouseMove) {
      res = true;
    }
  }

  return (res);
}

// -------------------------------------------------------

void MyWidgetOPenGL::turnOnMouse() { m_isMouse = true; }
// -------------------------------------------------------

void MyWidgetOPenGL::turnOffMouse() { m_isMouse = false; }

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

  // TODO(_who): release controller-> changeBackgroundColor
  // !! update();
}

// -------------------------------------------------------

void MyWidgetOPenGL::updateInfoObject() {
  label_name_->setText(model_->get_info_file().label_name);
  label_vertes_->setText(model_->get_info_file().label_vertex);
  label_polygons_->setText(model_->get_info_file().label_polygons);
}

// -------------------------------------------------------

void MyWidgetOPenGL::ChangeRotate() {
  if (model_->get_is_valid()) {
    if (model_->get_rotate_x()) {
      model_->TurnObjectX(model_->get_rotate_x());
    }
    if (model_->get_rotate_y()) {
      model_->TurnObjectY(model_->get_rotate_y());
    }
  }
}

// -------------------------------------------------------

void MyWidgetOPenGL::moveX(float value_) {
  model_->MoveDirection(MOVE_X, value_);
}

// -------------------------------------------------------

void MyWidgetOPenGL::moveY(float value_) {
  model_->MoveDirection(MOVE_Y, value_);
}

// -------------------------------------------------------

void MyWidgetOPenGL::moveZ(float value_) {
  model_->MoveDirection(MOVE_Z, value_);
}

// -------------------------------------------------------

void MyWidgetOPenGL::drawObjects(e_typeDraw type_draw) {
  auto type = type_draw == 0 ? GL_LINE_LOOP : GL_POINTS;
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  auto point_color = model_->get_point_color();
  auto line_color = model_->get_lines_color();
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

void MyWidgetOPenGL::drawInfo() {
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

QString MyWidgetOPenGL::scaleString() {
  return (QString::number(m_countScale));
}

// -------------------------------------------------------

void MyWidgetOPenGL::Update() { update(); }

// -------------------------------------------------------

void MyWidgetOPenGL::UpdateInfo() {
  updateInfoObject();
  ChangeColorFileInfo(model_->get_background_color().toHsl().hue());
}

// -------------------------------------------------------

void MyWidgetOPenGL::updatePerspective() {
  auto tmp_perspective = model_->get_perspective();
  auto size_perspective = model_->get_size_perspective();

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

void MyWidgetOPenGL::clearInfo() {
  label_name_->setText("");
  label_vertes_->setText("");
  label_polygons_->setText("");
}

// -------------------------------------------------------

void MyWidgetOPenGL::drawSquare() {
  auto point_color = model_->get_point_color();
  glColor3f(point_color.redF(), point_color.greenF(), point_color.blueF());
  double x, y, z, del = model_->get_perspective() == 1 ? 9 : 23;
  del = model_->MaxSizePerpective() / del * model_->get_point_size() / 20;
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

}  // namespace s21
