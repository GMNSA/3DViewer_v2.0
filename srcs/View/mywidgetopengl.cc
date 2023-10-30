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
      m_labelName(new QLabel(this)),
      m_labelVertes(new QLabel(this)),
      m_labelPolygons(new QLabel(this)),
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

    updatePerspective();
    drawObjects(e_typeDraw::TYPE_LINES);

    if (model_->get_line_type() == LineType::LINE_STIPPLE) {
      glDisable(GL_LINE_STIPPLE);
    }
    if (model_->get_point_type() == PointType::POINT_CIRCLE) {
      glEnable(GL_POINT_SMOOTH);
      qDebug() << "HERE point circle";
      qDebug() << "point size: " << model_->get_point_size();
      glPointSize(model_->get_point_size());
      drawObjects(e_typeDraw::TYPE_POINTS);
      glDisable(GL_POINT_SMOOTH);
    } else if (model_->get_point_type() == PointType::POINT_SQUARE) {
      qDebug() << "HERE point square";
      drawSquare();
    }
  }
}

// --------------------------------------------------

void MyWidgetOPenGL::wheelEvent(QWheelEvent *event) {
  auto is_decrement = event->angleDelta().ry() < 0 ? 1 : 0;
  (is_decrement) ? controller_->DecrementScale()
                 : controller_->IncremenetScale();
  // emit on_scaleStep();
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

void MyWidgetOPenGL::setBackgroundColor(int value_) {
  if (value_ == 0 || value_ == 255) {
    // m_backgroundColor.setHsl(0, 0, 0);
    m_labelName->setStyleSheet("QLabel { color : white; }");
    m_labelVertes->setStyleSheet("QLabel { color : white; }");
    m_labelPolygons->setStyleSheet("QLabel { color : white; }");
    emit on_changeColorGifTime(0);
  } else {
    // m_backgroundColor.setHsl(value_, 50, 50);
    m_labelName->setStyleSheet("QLabel { color : black; }");
    m_labelVertes->setStyleSheet("QLabel { color : black; }");
    m_labelPolygons->setStyleSheet("QLabel { color : black; }");
    emit on_changeColorGifTime(1);
  }

  // TODO(_who): release controller-> changeBackgroundColor
  // !! update();
}

// -------------------------------------------------------

void MyWidgetOPenGL::connectionsConfiguration() {}

// -------------------------------------------------------

void MyWidgetOPenGL::qColorToRGB(const QColor &c_, float &r_, float &g_,
                                 float &b_) const {
  r_ = normalize_0_1(c_.redF(), 1.0f, 255.0f);
  g_ = normalize_0_1(c_.greenF(), 1.0f, 255.0f);
  b_ = normalize_0_1(c_.blueF(), 1.0f, 255.0f);
}

// -------------------------------------------------------

int MyWidgetOPenGL::normalize_0_1(float val, float min, float max) const {
  return (val - min) / (max - min);
}

// -------------------------------------------------------

void MyWidgetOPenGL::updateInfoObject() {
  if (model_->get_is_valid()) {
    qDebug() << "[HERE update info object]!!! Filename: "
             << model_->get_filename_object();
    QFileInfo info(model_->get_filename_object());

    m_labelName->setText("Name: " + info.baseName());
    m_labelVertes->setText("    Vertes: " +
                           QString::number(model_->PointsArray().size()));
    m_labelPolygons->setText("    Polygons: " +
                             QString::number(model_->Polygons().size() *
                                             model_->PointsArray().size()));
  }
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
  size_t n_polygons = model_->Polygons().size();

  for (size_t i = 1; i < n_polygons; i++) {
    glBegin(type);
    if (type_draw == TYPE_LINES)
      glColor3f(line_color.redF(), line_color.greenF(), line_color.blueF());
    else
      glColor3f(point_color.redF(), point_color.greenF(), point_color.blueF());
    for (size_t j = 0; j < model_->Polygons()[i].size(); j++) {
      x = model_->PointsArray()[model_->Polygons()[i][j]].x;
      y = model_->PointsArray()[model_->Polygons()[i][j]].y;
      z = model_->PointsArray()[model_->Polygons()[i][j]].z;

      glVertex3f(x, y, z);
    }
    glEnd();
  }
}

// -------------------------------------------------------

void MyWidgetOPenGL::drawInfo() {
  m_labelName->setText("Name: ");
  m_labelVertes->setText("Vertes: ");
  m_labelPolygons->setText("Polygons: ");
  m_layoutH->setAlignment(Qt::AlignTop);
  m_layoutH->addStretch();
  m_layoutH->addWidget(m_labelName);
  m_layoutH->addWidget(m_labelVertes);
  m_layoutH->addWidget(m_labelPolygons);
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
  qDebug() << "Update Info";
}

// -------------------------------------------------------

void MyWidgetOPenGL::updatePerspective() {
  // TODO(_who): NEEED FIX !!!
  auto tmp_perspective = model_->get_perspective();
  auto size_perspective = model_->get_size_perspective();

  if (tmp_perspective == 1) {
    glLoadIdentity();
    glFrustum(-size_perspective, size_perspective, -size_perspective,
              size_perspective, size_perspective / 2.5, size_perspective * 2);
    glTranslatef(0, 0, -size_perspective / 2.5 * 3);
    // m_perspective = 4;
  } else if (tmp_perspective == 0) {
    glLoadIdentity();
    glOrtho(-size_perspective, size_perspective, -size_perspective,
            size_perspective, -size_perspective, size_perspective);
    // m_perspective = 5;
  }
}

// -------------------------------------------------------

void MyWidgetOPenGL::clearInfo() {
  m_labelName->setText("");
  m_labelVertes->setText("");
  m_labelPolygons->setText("");
}

// -------------------------------------------------------

void MyWidgetOPenGL::drawSquare() {
  auto point_color = model_->get_point_color();
  glColor3f(point_color.redF(), point_color.greenF(), point_color.blueF());
  // double x, y, z, del = m_perspective == 4 ? 9 : 23;
  double x, y, z, del = model_->get_perspective() == 1 ? 9 : 23;

  del = model_->MaxSizePerpective() / del * model_->get_point_size() / 20;

  for (size_t i = 1; i < model_->Polygons().size(); i++) {
    for (size_t j = 0; j < model_->Polygons()[i].size(); j++) {
      glBegin(GL_POLYGON);
      x = model_->PointsArray()[model_->Polygons()[i][j]].x;
      y = model_->PointsArray()[model_->Polygons()[i][j]].y;
      z = model_->PointsArray()[model_->Polygons()[i][j]].z;
      glVertex3f(x - del, y - del, z);
      glVertex3f(x + del, y - del, z);
      glVertex3f(x + del, y + del, z);
      glVertex3f(x - del, y + del, z);
      glEnd();
    }
  }
}

}  // namespace s21
