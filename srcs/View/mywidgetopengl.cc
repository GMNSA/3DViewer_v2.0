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

MyWidgetOPenGL::~MyWidgetOPenGL() {
  // free_matrix_int(&m_polygons);
  // if (m_points.points)
  //   free(m_points.points);

  // TODO(_who): don't forget release WriteToFileConfig.
  controller_->WriteConfig("./config.json");

  // if (modelviewer_) delete modelviewer_;
}

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
    // qDebug() << "line_width: " << model_->get_line_width();
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
  // m_rotateX = mouse_position_.x() - event->pos().x();
  // m_rotateY = mouse_position_.y() - event->pos().y();
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

// void MyWidgetOPenGL::setPointSize(double point_size) {
//   if (point_size >= model_->get_point_size_min() &&
//       point_size <= model_->get_point_size_max()) {
//     model_->set_point_size(point_size);
//     // TODO(_who): need pofix
//     // m_pointSize = newPointSize;
//     // !! update();
//   }
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::setPerspective(int value_) {
//   if (m_perspective != value_) {
//     m_perspective = value_;
//     // !! update();
//   } else {
//   }
// }

// -------------------------------------------------------

void MyWidgetOPenGL::turnOnMouse() { m_isMouse = true; }
// -------------------------------------------------------

void MyWidgetOPenGL::turnOffMouse() { m_isMouse = false; }

// -------------------------------------------------------

void MyWidgetOPenGL::setLineType(int newLineType) {
  m_lineType = newLineType;
  // !! update();
}

// -------------------------------------------------------

void MyWidgetOPenGL::setPointType(int newPointType) {
  m_pointType = newPointType;
  // !! update();
}

// -------------------------------------------------------

// void MyWidgetOPenGL::setLineWidth(double newLineWidth) {
//   m_lineWidth = newLineWidth;
//   // !! update();
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::setLineColor(int value_) {
//   if (value_ == 0 || value_ == 255)
//     m_lineColor.setHsl(255, 255, 255);
//   else
//     m_lineColor.setHsl(value_, 80, 80);
//   // !! update();
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::setPointColor(int value_) {
//   if (value_ == 0 || value_ == 255)
//     m_pointColor.setHsl(255, 255, 255);
//   else
//     m_pointColor.setHsl(value_, 80, 80);
//   // !! update();
// }

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

// int MyWidgetOPenGL::rotateBuffX() const { return m_rotateX; }

// -------------------------------------------------------

// int MyWidgetOPenGL::rotateBuffY() const { return m_rotateY; }

// -------------------------------------------------------

// int MyWidgetOPenGL::rotateBuffZ() const { return m_rotateZ; }

// -------------------------------------------------------

// int MyWidgetOPenGL::maxScale() { return (m_maxScale); }

// -------------------------------------------------------

// int MyWidgetOPenGL::minScale() { return (m_minScale); }

// -------------------------------------------------------

// void MyWidgetOPenGL::setRotateBuffZ(int newRotateBuffZ) {
//   m_rotateZ = newRotateBuffZ;
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::setRotateBuffY(int newRotateBuffY) {
//   m_rotateY = newRotateBuffY;
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::setRotateBuffX(int rotate) { m_rotateX = rotate; }

// -------------------------------------------------------

// void MyWidgetOPenGL::rotateY(int const value_) {
//   // setRotateBuffY(value_);
//   // moveRotation(MOVE_ROTATE_Y, value_);
//   model_->set_rotate_buff_y(value_);
//   model_->MoveRotation(MOVE_ROTATE_Y, value_);
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::rotateX(int const value_) {
//   // setRotateBuffX(value_);
//   //  moveRotation(MOVE_ROTATE_X, value_);
//   model_->set_rotate_buff_x(value_);
//   model_->MoveRotation(MOVE_ROTATE_X, value_);
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::rotateZ(int const value_) {
//   // setRotateBuffZ(value_);
//   // moveRotation(MOVE_ROTATE_Z, value_);
//   model_->set_rotate_buff_z(value_);
//   model_->MoveRotation(MOVE_ROTATE_Z, value_);
// }

// -------------------------------------------------------

// const QString &MyWidgetOPenGL::fileNameObject() const {
//   return m_fileNameObject;
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::setFileNameObject(const QString &newFileNameObject) {
//   m_fileNameObject = newFileNameObject;
//   // updateData();
// }

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

// int MyWidgetOPenGL::updateData() {
//   QFileInfo checkFile(m_fileNameObject);
//   int is_res = 0;
//   m_isValid = 0;
//
//   model_->PolygonsClear();
//
//   if (checkFile.exists() && checkFile.isFile() &&
//   !m_fileNameObject.isEmpty()) {
//     model_->Parse(m_fileNameObject.toStdString().c_str());
//
//     if (model_->Error() == ErrorType::ERROR_OK &&
//     !m_fileNameObject.isEmpty()) {
//       // TODO:(_who): don't forget release DefaultConfigSimple
//       // defaultConfigSimple();
//       m_isValid = true;
//       m_sizePerspective = pow(10, countNumber(model_->MaxSizePerpective()));
//
//       updateInfoObject();
//       emit on_changePerperpertiveRdb(m_perspective);
//
//       if (m_perspective == 4)
//         m_perspective = 1;
//       else if (m_perspective == 5)
//         m_perspective = 0;
//     } else {
//       clearInfo();
//     }
//   } else {
//     clearInfo();
//   }
//
//   return (is_res);
// }

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

    // m_labelVertes->setText("    Vertes: " +
    //                        QString::number(m_points.count_points));
    // m_labelPolygons->setText(
    //     "    Polygons: " +
    //     QString::number(m_polygons.poligons->columns * m_polygons.rows));
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

// void MyWidgetOPenGL::lineWidth(GLfloat nWidth_) {
//   m_widthLine = nWidth_ / 10;
//   // !! update();
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::defaultConfig() {
//   m_lineType = 0;
//   m_perspective = 0;
//   m_lineWidth = 1;
//   m_pointSize = 2;
//   m_pointType = 0;
//   m_lineColor = {1, 1, 1};
//   m_pointColor = {1, 1, 1};
//   m_backgroundColor = {1, 1, 1};
//   m_perspective = 0;
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::defaultConfigSimple() {
//   m_countScale = 10;
//   m_maxScale = 60;
//   m_minScale = -40;
//   m_maxPointSize = 25.0;
//   m_minPointSize = 0.0;
//   m_rotateBeforeX = 0;
//   m_rotateBeforeY = 0;
//   m_rotateBeforeZ = 0;
//   m_moveBeforeX = 0;
//   m_moveBeforeY = 0;
//   m_moveBeforeZ = 0;
// }

// -------------------------------------------------------

// TODO(_who): write and laod file
// bool MyWidgetOPenGL::loadConfig(QString path_) {
//   bool is_res = 1;
//   QString val;
//   QString filename =
//       path_.isEmpty() ? QDir::currentPath() + "/config.json" : path_;
//
//   QFile file(filename);
//
//   file.open(QIODevice::ReadOnly | QIODevice::Text);
//
//   if (file.isOpen()) {
//     val = file.readAll();
//     file.close();
//
//     QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
//     QJsonObject sett2 = d.object();
//     QJsonValue value = sett2.value(QString("lineType"));
//     if (!value.isUndefined() && is_res) {
//       m_lineType = (value.toInt());
//     } else {
//       is_res = 0;
//     }
//
//     value = sett2.value(QString("perspective"));
//     if (!value.isUndefined() && is_res) {
//       m_perspective = (value.toInt());
//     } else {
//       is_res = 0;
//     }
//
//     value = sett2.value(QString("lineWidth"));
//     if (!value.isUndefined() && is_res) {
//       m_lineWidth = (value.toDouble());
//     } else {
//       is_res = 0;
//     }
//
//     value = sett2.value(QString("pointSize"));
//     if (!value.isUndefined() && is_res) {
//       m_pointSize = (value.toInt());
//     } else {
//       is_res = 0;
//     }
//
//     value = sett2.value(QString("pointType"));
//     if (!value.isUndefined() && is_res) {
//       m_pointType = (value.toInt());
//     } else {
//       is_res = 0;
//     }
//
//     value = sett2.value(QString("lineColor"));
//     QJsonArray arr = value.toArray();
//
//     if (!value.isUndefined() && value.isArray() && arr.size() == 3 && is_res)
//     {
//       m_lineColor = {arr[0].toInt(), arr[1].toInt(), arr[2].toInt()};
//     } else {
//       is_res = 0;
//     }
//
//     value = sett2.value(QString("pointColor"));
//     arr = value.toArray();
//
//     if (!value.isUndefined() && value.isArray() && arr.size() == 3 && is_res)
//     {
//       m_pointColor = {arr[0].toInt(), arr[1].toInt(), arr[2].toInt()};
//     } else {
//       is_res = 0;
//     }
//
//     value = sett2.value(QString("backColor"));
//     arr = value.toArray();
//
//     if (!value.isUndefined() && value.isArray() && arr.size() == 3 && is_res)
//     {
//       m_backgroundColor = {arr[0].toInt(), arr[1].toInt(), arr[2].toInt()};
//     } else {
//       is_res = 0;
//     }
//
//   } else {
//     is_res = 0;
//
//     // TODO:(_who) don't forget release "Default Config"
//     // defaultConfig();
//   }
//
//   return (is_res);
// }

// -------------------------------------------------------

// TODO(_who): write to file
// bool MyWidgetOPenGL::writeToFileConfig(QString path_) {
//   bool isRes = 1;
//
//   QString val;
//   QString filename =
//       path_.isEmpty() ? QDir::currentPath() + "/config.json" : path_;
//
//   QFile file(filename);
//
//   file.open(QIODevice::WriteOnly | QIODevice::Text);
//
//   if (file.isOpen()) {
//     QJsonObject tmp;
//
//     tmp.insert("lineType", m_lineType);
//
//     if (m_perspective == 4)
//       m_perspective = 1;
//     else if (m_perspective == 5)
//       m_perspective = 0;
//
//     tmp.insert("perspective", m_perspective);
//     tmp.insert("lineWidth", m_lineWidth);
//     tmp.insert("pointType", m_pointType);
//     tmp.insert("pointSize", m_pointSize);
//
//     QJsonArray jsonArr;
//     jsonArr.push_back(m_lineColor.red());
//     jsonArr.push_back(m_lineColor.green());
//     jsonArr.push_back(m_lineColor.blue());
//
//     tmp.insert("lineColor", jsonArr);
//
//     QJsonArray jsonArrPointColor;
//     jsonArrPointColor.push_back(m_pointColor.red());
//     jsonArrPointColor.push_back(m_pointColor.green());
//     jsonArrPointColor.push_back(m_pointColor.blue());
//
//     tmp.insert("pointColor", jsonArrPointColor);
//
//     QJsonArray jsonArrBackColor;
//     jsonArrBackColor.push_back(m_backgroundColor.red());
//     jsonArrBackColor.push_back(m_backgroundColor.green());
//     jsonArrBackColor.push_back(m_backgroundColor.blue());
//
//     tmp.insert("backColor", jsonArrBackColor);
//
//     QTextStream out(&file);
//     QJsonDocument jsonDocument;
//
//     jsonDocument.setObject(tmp);
//
//     QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Indented);
//     out << byteArray;
//     file.close();
//   } else {
//   }
//
//   return (isRes);
// }

// -------------------------------------------------------

void MyWidgetOPenGL::moveX(float value_) {
  model_->MoveDirection(MOVE_X, value_);
  // moveDirection(MOVE_X, value_);
}

// -------------------------------------------------------

void MyWidgetOPenGL::moveY(float value_) {
  model_->MoveDirection(MOVE_Y, value_);
  // moveDirection(MOVE_Y, value_);
}

// -------------------------------------------------------

void MyWidgetOPenGL::moveZ(float value_) {
  model_->MoveDirection(MOVE_Z, value_);
  // moveDirection(MOVE_Z, value_);
}

// -------------------------------------------------------

void MyWidgetOPenGL::drawObjects(e_typeDraw type_draw) {
  Q_UNUSED(type_draw);
  auto type = type_draw == 0 ? GL_LINE_LOOP : GL_POINTS;
  double x, y, z;
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

// void MyWidgetOPenGL::incrementScale() {
//   if (model_->get_is_valid()) {
//     if (m_countScale < m_maxScale) {
//       ++m_countScale;
//       model_->ScaleObject(1.05);
//       // snewPointSizecale_obj(1.05, &m_points);
//       emit on_scaleStep();
//     }
//     // !! update();
//   }
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::decrementScale() {
//   if (model_->get_is_valid()) {
//     if (m_countScale > m_minScale) {
//       --m_countScale;
//       model_->ScaleObject(0.95);
//       // scale_obj(0.95, &m_points);
//       emit on_scaleStep();
//     }
//     // !! update();
//   }
// }

// -------------------------------------------------------

QString MyWidgetOPenGL::scaleString() {
  return (QString::number(m_countScale));
}

// -------------------------------------------------------

// void MyWidgetOPenGL::lineScaleChange(int value_) {
//   bool isDecrement = 0;
//   isDecrement = m_countScale > value_ ? 1 : 0;
//
//   if (isDecrement && value_ >= m_minScale) {
//     while (m_countScale != value_) decrementScale();
//   } else if (!isDecrement && value_ <= m_maxScale) {
//     while (m_countScale != value_) incrementScale();
//   }
//   if (value_ >= m_minScale && value_ <= m_maxScale) {
//     m_countScale = value_;
//     emit on_scaleStep();
//   }
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::moveDirection(e_moveType direction_, float value_) {
//   Q_UNUSED(direction_);
//   Q_UNUSED(value_);
//   if (m_isValid) {
//     value_ = value_ * model_->max_size_ / 99;
//
//     Point t;
//     float tmp = 0;
//     int isError = 0;
//
//     switch (direction_) {
//       case MOVE_X:
//         tmp = m_moveBeforeX - value_;
//         t = {tmp, 0, 0};
//         m_moveBeforeX = value_;
//         break;
//       case MOVE_Y:
//         tmp = m_moveBeforeY - value_;
//         t = {0, tmp, 0};
//         m_moveBeforeY = value_;
//         break;
//       case MOVE_Z:
//         tmp = m_moveBeforeZ - value_;
//         t = {0, 0, tmp};
//         m_moveBeforeZ = value_;
//         break;
//       default:
//         isError = 1;
//         break;
//     }
//
//     if (!isError) {
//       model_->MoveObj(t);
//       // move_obj(&t, &m_points);
//     }
//     update();
//   }
// }

// -------------------------------------------------------

// void MyWidgetOPenGL::moveRotation(e_moveRotatinoType direction_, float
// value_) {
//   Q_UNUSED(direction_);
//   Q_UNUSED(value_);
//   float tmp = 0;
//   int isError = 0;
//
//   if (m_isValid) {
//     switch (direction_) {
//       case MOVE_ROTATE_X:
//         tmp = m_rotateBeforeX - value_;
//         m_rotateBeforeX = value_;
//         break;
//       case MOVE_ROTATE_Y:
//         tmp = m_rotateBeforeY - value_;
//         m_rotateBeforeY = value_;
//         break;
//       case MOVE_ROTATE_Z:
//         tmp = m_rotateBeforeZ - value_;
//         m_rotateBeforeZ = value_;
//         break;
//       default:
//         isError = 1;
//         break;
//     }
//
//     if (!isError) {
//       model_->TurnObj(tmp, direction_);
//       // turn_obj(tmp, &m_points, direction_);
//     }
//     update();
//   }
// }

// -------------------------------------------------------

// int MyWidgetOPenGL::countNumber(int number_) {
//   int result = 0;
//
//   if (number_ > 0) {
//     while (number_ > 0) {
//       number_ /= 10;
//       result++;
//     }
//   }
//
//   return result;
// }

// -------------------------------------------------------

void MyWidgetOPenGL::Update() {
  // TODO(_who): release
  update();
}

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
