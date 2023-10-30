#include "../../includes/View/mainwindow.hpp"

#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

#include "../lib/MatrixLib/includes/matrix.hpp"
#include "./ui_mainwindow.h"

#define ROTATE_VALUE 720
#define GIF_FPS 10

// -------------------------------------------------------

namespace s21 {

// m_gif(new QGifImage),
MainWindow::MainWindow(IControllerInterface *controller, IModelViewer *model,
                       QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(controller),
      model_(model),
      m_myWidget(new MyWidgetOPenGL(controller, model, this)),
      m_isPositiveHorizontal(1),
      m_isPositiveVertical(1),
      m_gif(new GifCreator(m_myWidget)),
      m_timerGif(new QTimer(this)),
      m_labelGifTime(new QLabel(m_myWidget)) {
  ui->setupUi(this);
  model_->Attach(qobject_cast<IMainWindowObserver *>(this));

  S21Matrix matrix(3, 3);
  qDebug() << "GET COLS: " << matrix.GetCols();

  ui->radioButton_solid->setChecked(true);
  ui->radioButton_no->setChecked(true);

  m_myWidget->setParent(ui->widget);
  m_myWidget->show();
  connectsConfiguration();

  m_labelGifTime->setText("");
  m_labelGifTime->setAlignment(Qt::AlignTop);
  m_labelGifTime->setAlignment(Qt::AlignLeft);
  m_labelGifTime->move(40, 40);
  m_labelGifTime->raise();
  QFont font = m_labelGifTime->font();
  font.setPointSize(20);
  font.setBold(true);
  m_labelGifTime->setFont(font);
}

// -------------------------------------------------------

MainWindow::~MainWindow() { delete ui; }

// -------------------------------------------------------

void MainWindow::Update() {
  qDebug() << "Update main window";
  // m_myWidget->updateInfoObject();
  changePerperpertiveRdb(model_->get_perspective());
  ui->lineEdit_scale->setText(QString::number(model_->get_scale()));
  ui->hSlidder_pointsSize->setValue(model_->get_point_size());
  ui->hSlider_colorLines->setValue(model_->get_lines_color().toHsl().hue());
  ui->hSlider_colorPoints->setValue(model_->get_point_color().toHsl().hue());
  ui->hSlider_backgroundColor->setValue(
      model_->get_background_color().toHsl().hue());
  if (model_->get_point_type() == PointType::POINT_CIRCLE)
    ui->radioButton_circle->setChecked(true);
  else if (model_->get_point_type() == PointType::POINT_SQUARE)
    ui->radioButton_squard->setChecked(true);

  ui->hSlidder_widthLine->setValue(model_->get_line_width() * 10);
}

// -------------------------------------------------------

void MainWindow::openFileDialog() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open Object"), "./objects/", tr("Image Files (*.obj)"));
  model_->OpenFileObject(filename);

  // m_myWidget->setFileNameObject(filename);
  // m_myWidget->update();
  qDebug() << "open";
}

// -------------------------------------------------------

void MainWindow::rotateX(int value) {
  Q_UNUSED(value)
  // m_myWidget->rotateX(value_);
  // TODO(_who): change rotate -> change buff rotate (safe)

  // qDebug() << "Rotate X";
  controller_->MoveRotationX(value);
  changeRotateSliders();
}

// -------------------------------------------------------

void MainWindow::rotateY(int value) {
  // m_myWidget->rotateY(value_);
  controller_->MoveRotationY(value);
  changeRotateSliders();
}

// -------------------------------------------------------

void MainWindow::rotateZ(int value) {
  // m_myWidget->rotateZ(value_);
  controller_->MoveRotationZ(value);
  changeRotateSliders();
}

// -------------------------------------------------------

void MainWindow::connectsConfiguration() {
  connect(ui->pb_openFIle, &QPushButton::clicked, this,
          &MainWindow::openFileDialog);

  connect(ui->widget, &QOpenGLWidget::resized, this, [&]() {
    m_myWidget->resize(ui->widget->width(), ui->widget->height());
  });

  connect(ui->radioButton_dotter, &QRadioButton::pressed, this, [&]() {
    // m_myWidget->setLineType(1);
    controller_->ChangeLineType(LineType::LINE_STIPPLE);
  });

  connect(ui->radioButton_solid, &QRadioButton::pressed, this, [&]() {
    // m_myWidget->setLineType(0);
    controller_->ChangeLineType(LineType::LINE_SIMPLE);
  });

  connect(ui->hSlidder_pointsSize, &QSlider::valueChanged, this,
          &MainWindow::changeSizePoint);

  connect(m_myWidget, &MyWidgetOPenGL::on_changeColorGifTime, this,
          &MainWindow::changeColorGifTime);

  connect(m_myWidget, &MyWidgetOPenGL::on_changePerperpertiveRdb, this,
          &MainWindow::changePerperpertiveRdb);

  connectsPointType();
  connectsRotate();
  connectsMoves();
  connectsColor();
  connectsScale();
  connectsImages();
  connectsLineWidth();
  connectPerspective();
  connectMouseRotate();
}

// -------------------------------------------------------

void MainWindow::changeRotateSliders() {
  int x = (model_->get_rotate_buff_x() % ROTATE_VALUE);
  int y = (model_->get_rotate_buff_y() % ROTATE_VALUE);
  int z = (model_->get_rotate_buff_z() % ROTATE_VALUE);
  // qDebug() << "x: " << x;
  // qDebug() << "y: " << y;
  // qDebug() << "z: " << z;
  // int x = (m_myWidget->rotateBuffX() % ROTATE_VALUE);
  // int y = (m_myWidget->rotateBuffY() % ROTATE_VALUE);
  // int z = (m_myWidget->rotateBuffZ() % ROTATE_VALUE);
  ui->slider_x->setValue(x);
  ui->slider_y->setValue(y);
  ui->slider_z->setValue(z);
  ui->lineEdit_rotateX->setText(QString::number(x));
  ui->lineEdit_rotateY->setText(QString::number(y));
  ui->lineEdit_rotateZ->setText(QString::number(z));
}

void MainWindow::screenshot(int isJpeg) {
  Q_UNUSED(isJpeg);
  long ttime = time(0);
  QString current_time = ctime(&ttime);
  QString format;
  QPixmap pix(m_myWidget->size() * 2);
  QMessageBox msgBox;

  QString path = QDir::currentPath() + "/screenshots/" + current_time;
  path.chop(1);
  path.replace(" ", "_");

  if (isJpeg == 1) {
    path += ".jpeg";
    format = "JPG";
  } else {
    path += ".bmp";
    format = "BMP";
  }

  pix.setDevicePixelRatio(2);
  m_myWidget->render(&pix);

  if (pix.save(path, format.toLatin1(), 100)) {
    msgBox.setText("Screenshot OK (" + format + ").");
    msgBox.exec();
  } else {
    msgBox.setText("Screenshot ERROR (" + format + ").");
    msgBox.exec();
  }
}

// -------------------------------------------------------

void MainWindow::changeColorGifTime(int isBlack_) {
  Q_UNUSED(isBlack_);
  if (isBlack_)
    m_labelGifTime->setStyleSheet("QLabel { color : black; }");
  else
    m_labelGifTime->setStyleSheet("QLabel { color : white; }");
}

// -------------------------------------------------------

void MainWindow::closeApp() { close(); }

// -------------------------------------------------------

void MainWindow::lineScaleChange(QString value) {
  // m_myWidget->lineScaleChange(value_.toInt());
  // TODO(_who): will need to fix this !!!! Is it necessary or not.

  int tmp_value = value.toInt();
  bool is_decrement = 0;
  auto n_scale = model_->get_scale();
  auto min_scale = model_->get_min_scale();
  auto max_scale = model_->get_max_scale();

  is_decrement = n_scale > tmp_value ? 1 : 0;

  qDebug() << "HERE 0";
  if (is_decrement && tmp_value >= min_scale) {
    while (n_scale != tmp_value) controller_->DecrementScale();
  } else if (!is_decrement && tmp_value <= max_scale) {
    while (n_scale != tmp_value) controller_->IncremenetScale();
  }
  qDebug() << "HERE 1";
  if (tmp_value >= min_scale && tmp_value <= max_scale) {
    qDebug() << "HERE 2";
    n_scale = tmp_value;
    qDebug() << "n_scale: " << n_scale;
    qDebug() << "orogin_scale: " << model_->get_scale();
    // emit on_scaleStep();
  }
}

// -------------------------------------------------------

void MainWindow::changeBackgroundColor(int value) {
  controller_->ChangeBackgroundColor(value);

  // m_myWidget->setBackgroundColor(value_);
  // TODO:(_who) change
}

// -------------------------------------------------------

void MainWindow::changeColorLines(int value) {
  controller_->ChangeLinesColor(value);
  // m_myWidget->setLineColor(value);
}

// -------------------------------------------------------

void MainWindow::changeColorPoints(int value) {
  controller_->ChangePointColor(value);
  // m_myWidget->setPointColor(value_);
}

// -------------------------------------------------------

void MainWindow::changeWidthLines(int value) {
  controller_->ChangeLineWidth(value);
  ui->lineEdit_widthLine->setText(QString::number(value));
  // m_myWidget->setLineWidth(value);
}

// -------------------------------------------------------

void MainWindow::changeSizePoint(int value) {
  controller_->ChangePointSize(value);
  ui->lineEdit_pointsSize->setText(QString::number(value));
  // m_myWidget->setPointSize(value_);
}

// -------------------------------------------------------

void MainWindow::setPointType(PointType const &type) {
  qDebug() << "Type point: " << type;
  controller_->ChangeTypePoint(type);
  // m_myWidget->setPointType(value_);
}

// -------------------------------------------------------

void MainWindow::moveObject(int type, int value) {
  if (type == MOVE_X) {
    controller_->MoveDirectionX(value);
    // m_myWidget->moveX((value_));
    ui->lineEdit_moveX->setText(QString::number(value));
  } else if (type == MOVE_Y) {
    // m_myWidget->moveY((value_));
    controller_->MoveDirectionY(value);
    ui->lineEdit_moveY->setText(QString::number(value));
  } else if (type == MOVE_Z) {
    // m_myWidget->moveZ((value_));
    controller_->MoveDirectionZ(value);
    ui->lineEdit_moveZ->setText(QString::number(value));
  }
}

// -------------------------------------------------------

void MainWindow::screenshotJPEG() { screenshot(1); }

// -------------------------------------------------------

void MainWindow::screenshotBMP() { screenshot(0); }

// -------------------------------------------------------

void MainWindow::doGif() {
  m_startTime = 0;
  m_endTime = 1000 / GIF_FPS;
  m_timerGif->start(1000 / GIF_FPS);
  m_frameNum = 0;
}

// -------------------------------------------------------

void MainWindow::startGif() {
  if (m_startTime == m_endTime) {
    float time = 0;
    QPixmap gif(m_myWidget->size());
    m_myWidget->render(&gif);
    gif.scaled(640, 480, Qt::IgnoreAspectRatio);
    if (!gif.save(m_gif->imageFilePathMask().arg(m_frameNum))) {
      // logging_line(ERROR_ANOTHER, "", __LINE__, "[ERROR] gif not save
      // image.", 1);
    }

    time = m_startTime / 1000;
    m_labelGifTime->setText(QString::number(time));
    m_endTime += 1000 / GIF_FPS;
    ++m_frameNum;
  }

  int gifLength = 5;
  if (m_startTime >= 1000 * gifLength) {
    if (m_gif->createGif(m_frameNum, GIF_FPS)) {
      qDebug() << "GIF OK";
    } else {
      qDebug() << "GIF FALSE";
    }

    m_timerGif->stop();
    qDebug() << "gif path: " << m_gif->gifFilePath();
    m_labelGifTime->setText("");
  }
  m_startTime += 1000.0 / GIF_FPS;
}

// -------------------------------------------------------

void MainWindow::connectsMoves() {
  connect(ui->hSlider_moveX, &QSlider::valueChanged, this, [&](int value) {
    ui->lineEdit_moveX->setText(QString::number(value));
    moveObject(MOVE_X, value);
  });

  connect(ui->hSlider_moveY, &QSlider::valueChanged, this, [&](int value) {
    ui->lineEdit_moveY->setText(QString::number(value));
    moveObject(MOVE_Y, value);
  });

  connect(ui->hSlider_moveZ, &QSlider::valueChanged, this, [&](int value) {
    ui->lineEdit_moveZ->setText(QString::number(value));
    moveObject(MOVE_Z, value);
  });

  /* *****  ***** */

  connect(ui->lineEdit_moveX, &QLineEdit::textEdited, this,
          [&](QString value) { moveObject(MOVE_X, value.toInt()); });

  connect(ui->lineEdit_moveY, &QLineEdit::textEdited, this,
          [&](QString value) { moveObject(MOVE_Y, value.toInt()); });

  connect(ui->lineEdit_moveZ, &QLineEdit::textEdited, this,
          [&](QString value) { moveObject(MOVE_ROTATE_Z, value.toInt()); });
}

// -------------------------------------------------------

void MainWindow::connectsRotate() {
  connect(ui->slider_x, &QSlider::valueChanged, this, &MainWindow::rotateX);
  connect(ui->slider_y, &QSlider::valueChanged, this, &MainWindow::rotateY);
  connect(ui->slider_z, &QSlider::valueChanged, this, &MainWindow::rotateZ);

  connect(ui->lineEdit_rotateX, &QLineEdit::textEdited, this,
          [&](QString value) { rotateX(value.toInt()); });

  connect(ui->lineEdit_rotateY, &QLineEdit::textEdited, this,
          [&](QString value) { rotateY(value.toInt()); });

  connect(ui->lineEdit_rotateZ, &QLineEdit::textEdited, this,
          [&](QString value) { rotateZ(value.toInt()); });

  // connect(m_myWidget, &MyWidgetOPenGL::on_changeRotate, this,
  //         &MainWindow::changeRotateSliders);
}

// -------------------------------------------------------

void MainWindow::connectsColor() {
  connect(ui->hSlider_colorLines, &QSlider::valueChanged, this,
          &MainWindow::changeColorLines);
  connect(ui->hSlider_colorPoints, &QSlider::valueChanged, this,
          &MainWindow::changeColorPoints);
  connect(ui->hSlider_backgroundColor, &QSlider::valueChanged, this,
          &MainWindow::changeBackgroundColor);
  connect(ui->hSlider_colorPoints, &QSlider::valueChanged, this,
          &MainWindow::changeColorPoints);
}

// -------------------------------------------------------

void MainWindow::connectsPointType() {
  connect(ui->radioButton_no, &QRadioButton::pressed, this,
          [&]() { setPointType(PointType::POINT_NONE); });

  connect(ui->radioButton_circle, &QRadioButton::pressed, this,
          [&]() { setPointType(PointType::POINT_CIRCLE); });

  connect(ui->radioButton_squard, &QRadioButton::pressed, this,
          [&]() { setPointType(PointType::POINT_SQUARE); });

  connect(ui->lineEdit_pointsSize, &QLineEdit::textEdited, this,
          [&](QString value_) { changeSizePoint(value_.toInt()); });
}

// -------------------------------------------------------

void MainWindow::connectsScale() {
  connect(m_myWidget, &MyWidgetOPenGL::on_scaleStep, this,
          [&]() { ui->lineEdit_scale->setText(m_myWidget->scaleString()); });

  connect(ui->pb_changeScale, &QPushButton::clicked, this,
          [&]() { lineScaleChange(ui->lineEdit_scale->text()); });

  connect(ui->pb_scalePlus, &QPushButton::clicked, m_myWidget,
          [&] { controller_->IncremenetScale(); });
  connect(ui->pb_scaleMinus, &QPushButton::clicked, m_myWidget,
          [&] { controller_->DecrementScale(); });
}

// -------------------------------------------------------

void MainWindow::connectsImages() {
  connect(ui->pb_jpeg, &QPushButton::clicked, this,
          &MainWindow::screenshotJPEG);
  connect(ui->pb_bmp, &QPushButton::clicked, this, &MainWindow::screenshotBMP);
  connect(ui->pb_gif, &QPushButton::clicked, this, &MainWindow::doGif);
  connect(m_timerGif, &QTimer::timeout, this, &MainWindow::startGif);
}

// -------------------------------------------------------

void MainWindow::connectPerspective() {
  connect(ui->radioButton_central, &QRadioButton::pressed, this, [&]() {
    // m_myWidget->setPerspective(0);
    controller_->ChangePerspective(PerspectiveType::PERSPECTIVE_CENTRAL);
  });

  connect(ui->radioButton_parallel, &QRadioButton::pressed, this, [&]() {
    controller_->ChangePerspective(PerspectiveType::PERSPECTIVE_PARALLEL);
  });
}

// -------------------------------------------------------

void MainWindow::connectMouseRotate() {
  connect(ui->checkBox_mouseOn, &QCheckBox::stateChanged, this,
          [&](int state_) {
            if (!state_) {
              ui->slider_x->setEnabled(true);
              ui->slider_y->setEnabled(true);
              ui->slider_z->setEnabled(true);
              ui->lineEdit_rotateX->setEnabled(true);
              ui->lineEdit_rotateY->setEnabled(true);
              ui->lineEdit_rotateZ->setEnabled(true);
              m_myWidget->turnOffMouse();
            } else {
              ui->slider_x->setEnabled(false);
              ui->slider_y->setEnabled(false);
              ui->slider_z->setEnabled(false);
              ui->lineEdit_rotateX->setEnabled(false);
              ui->lineEdit_rotateY->setEnabled(false);
              ui->lineEdit_rotateZ->setEnabled(false);
              m_myWidget->turnOnMouse();
            }
          });
}

// -------------------------------------------------------

void MainWindow::connectsLineWidth() {
  connect(ui->hSlidder_widthLine, &QSlider::valueChanged, this,
          &MainWindow::changeWidthLines);
  connect(ui->lineEdit_widthLine, &QLineEdit::textEdited, this,
          [&](QString value) { changeWidthLines(value.toDouble()); });
}

// -------------------------------------------------------

void MainWindow::changePerperpertiveRdb(int value_) {
  Q_UNUSED(value_);
  if (value_ == 1)
    ui->radioButton_parallel->setChecked(true);
  else
    ui->radioButton_central->setChecked(true);
}

}  // namespace s21
