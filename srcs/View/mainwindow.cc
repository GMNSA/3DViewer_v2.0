#include "../../includes/View/mainwindow.hpp"

#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

#include "../lib/MatrixLib/includes/matrix.hpp"
#include "./ui_mainwindow.h"

// TODO(_who): need change (remvoe) define
#define ROTATE_VALUE 720

// -------------------------------------------------------

namespace s21 {

MainWindow::MainWindow(IControllerInterface *controller, IFacadeModel *model,
                       QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(controller),
      model_(model),
      m_myWidget(new MyWidgetOPenGL(controller, model, this)),
      m_labelGifTime(new QLabel(m_myWidget)) {
  ui->setupUi(this);
  // TODO(_who): remove qdebug
  model_->Attach(qobject_cast<IMainWindowObserver *>(this));

  S21Matrix matrix(3, 3);

  ui->radioButton_solid->setChecked(true);
  ui->radioButton_no->setChecked(true);

  m_myWidget->setParent(ui->widget);
  m_myWidget->show();
  connectsConfiguration();
  controller_->LoadConfig();

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

// -------------------------------------------------------

MainWindow::~MainWindow() { delete ui; }

// -------------------------------------------------------

void MainWindow::Update() {
  // m_myWidget->updateInfoObject();
  auto data = model_->GetDataViewer();

  changePerperpertiveRdb(data.perspective);
  ui->lineEdit_scale->setText(QString::number(data.count_scale));
  ui->hSlidder_pointsSize->setValue(data.point_size);
  ui->hSlider_colorLines->setValue(data.line_color.toHsl().hue());
  ui->hSlider_colorPoints->setValue(data.point_color.toHsl().hue());
  ui->hSlider_backgroundColor->setValue(data.background_color.toHsl().hue());
  if (data.point_type == PointType::POINT_CIRCLE)
    ui->radioButton_circle->setChecked(true);
  else if (data.point_type == PointType::POINT_SQUARE)
    ui->radioButton_squard->setChecked(true);

  ui->hSlidder_widthLine->setValue(data.line_width * 10);
}

// -------------------------------------------------------

void MainWindow::ChangeRotateSlidersX(int const &value) {
  int x = (value % ROTATE_VALUE);

  ui->slider_x->setValue(x);
  ui->lineEdit_rotateX->setText(QString::number(x));
}

void MainWindow::ChangeRotateSlidersY(int const &value) {
  int y = (value % ROTATE_VALUE);

  ui->slider_y->setValue(y);
  ui->lineEdit_rotateY->setText(QString::number(y));
}

void MainWindow::ChangeRotateSlidersZ(int const &value) {
  int z = (value % ROTATE_VALUE);

  ui->slider_z->setValue(z);
  ui->lineEdit_rotateZ->setText(QString::number(z));
}

void MainWindow::ChangeLineWidth(double const &width) {
  ui->lineEdit_widthLine->setText(QString::number(width));
}

void MainWindow::ChangePointSize(int const &value) {
  ui->lineEdit_pointsSize->setText(QString::number(value));
}

void MainWindow::ChangeMoveSliderX(int const &value) {
  ui->lineEdit_moveX->setText(QString::number(value));
}

void MainWindow::ChangeMoveSliderY(int const &value) {
  ui->lineEdit_moveY->setText(QString::number(value));
}

void MainWindow::ChangeMoveSliderZ(int const &value) {
  ui->lineEdit_moveZ->setText(QString::number(value));
}

void MainWindow::BlockSlideRotate(bool const &is_block) {
  if (!is_block) {
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
}
// -------------------------------------------------------

void MainWindow::openFileDialog() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open Object"), "./objects/", tr("Image Files (*.obj)"));
  controller_->OpenFile(filename);

  qDebug() << "open";
}

// -------------------------------------------------------

void MainWindow::connectsConfiguration() {
  connect(ui->pb_openFIle, &QPushButton::clicked, this,
          &MainWindow::openFileDialog);

  connect(ui->widget, &QOpenGLWidget::resized, this, [&]() {
    m_myWidget->resize(ui->widget->width(), ui->widget->height());
  });

  connect(ui->radioButton_dotter, &QRadioButton::pressed, this,
          [&]() { controller_->ChangeLineType(LineType::LINE_STIPPLE); });

  connect(ui->radioButton_solid, &QRadioButton::pressed, this,
          [&]() { controller_->ChangeLineType(LineType::LINE_SIMPLE); });

  connect(ui->hSlidder_pointsSize, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->ChangePointSize(value); });

  //   connect(m_myWidget, &MyWidgetOPenGL::on_changeColorGifTime, this,
  //           &MainWindow::changeColorGifTime);

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

// void MainWindow::changeColorGifTime(int isBlack_) {
//   Q_UNUSED(isBlack_);
//   if (isBlack_)
//     m_labelGifTime->setStyleSheet("QLabel { color : black; }");
//   else
//     m_labelGifTime->setStyleSheet("QLabel { color : white; }");
// }

// -------------------------------------------------------

void MainWindow::closeApp() {
  controller_->WriteConfig();
  close();
}

// -------------------------------------------------------

// -------------------------------------------------------

void MainWindow::connectsMoves() {
  connect(ui->hSlider_moveX, &QSlider::valueChanged, this,
          [&](int value) { controller_->MoveDirectionX(value); });

  connect(ui->hSlider_moveY, &QSlider::valueChanged, this,
          [&](int value) { controller_->MoveDirectionY(value); });

  connect(ui->hSlider_moveZ, &QSlider::valueChanged, this,
          [&](int value) { controller_->MoveDirectionZ(value); });

  /* *****  ***** */

  connect(ui->lineEdit_moveX, &QLineEdit::textEdited, this,
          [&](QString value) { controller_->MoveDirectionX(value.toInt()); });

  connect(ui->lineEdit_moveY, &QLineEdit::textEdited, this,
          [&](QString value) { controller_->MoveDirectionY(value.toInt()); });

  connect(ui->lineEdit_moveZ, &QLineEdit::textEdited, this,
          [&](QString value) { controller_->MoveDirectionZ(value.toInt()); });
}

// -------------------------------------------------------

void MainWindow::connectsRotate() {
  connect(ui->slider_x, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->MoveRotationX(value); });
  connect(ui->slider_y, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->MoveRotationY(value); });
  connect(ui->slider_z, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->MoveRotationZ(value); });

  connect(
      ui->lineEdit_rotateX, &QLineEdit::textEdited, this,
      [&](QString const &value) { controller_->MoveRotationX(value.toInt()); });

  connect(
      ui->lineEdit_rotateY, &QLineEdit::textEdited, this,
      [&](QString const &value) { controller_->MoveRotationY(value.toInt()); });

  connect(
      ui->lineEdit_rotateZ, &QLineEdit::textEdited, this,
      [&](QString const &value) { controller_->MoveRotationZ(value.toInt()); });

  // connect(m_myWidget, &MyWidgetOPenGL::on_changeRotate, this,
  //         &MainWindow::changeRotateSliders);
}

// -------------------------------------------------------

void MainWindow::connectsColor() {
  connect(ui->hSlider_colorLines, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->ChangeLinesColor(value); });
  connect(ui->hSlider_backgroundColor, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->ChangeBackgroundColor(value); });
  connect(ui->hSlider_colorPoints, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->ChangePointColor(value); });
}

// -------------------------------------------------------

void MainWindow::connectsPointType() {
  connect(ui->radioButton_no, &QRadioButton::pressed, this,
          [&]() { controller_->ChangeTypePoint(PointType::POINT_NONE); });

  connect(ui->radioButton_circle, &QRadioButton::pressed, this,
          [&]() { controller_->ChangeTypePoint(PointType::POINT_CIRCLE); });

  connect(ui->radioButton_squard, &QRadioButton::pressed, this,
          [&]() { controller_->ChangeTypePoint(PointType::POINT_SQUARE); });

  connect(ui->lineEdit_pointsSize, &QLineEdit::textEdited, this,
          [&](QString const &value) {
            controller_->ChangePointSize(value.toInt());
          });
}

// -------------------------------------------------------

void MainWindow::connectsScale() {
  // connect(m_myWidget, &MyWidgetOPenGL::on_scaleStep, this,
  //         [&]() { ui->lineEdit_scale->setText(m_myWidget->scaleString()); });

  connect(ui->pb_changeScale, &QPushButton::clicked, this, [&]() {
    controller_->ChangeScale(ui->lineEdit_scale->text().toInt());
  });

  connect(ui->pb_scalePlus, &QPushButton::clicked, m_myWidget,
          [&] { controller_->IncremenetScale(); });
  connect(ui->pb_scaleMinus, &QPushButton::clicked, m_myWidget,
          [&] { controller_->DecrementScale(); });
}

// -------------------------------------------------------

void MainWindow::connectsImages() {
  connect(ui->pb_jpeg, &QPushButton::clicked, this,
          [&]() { controller_->ScreenshotJPEG(m_myWidget); });
  connect(ui->pb_bmp, &QPushButton::clicked, this,
          [&]() { controller_->ScreenshotBMP(m_myWidget); });
  connect(ui->pb_gif, &QPushButton::clicked, this,
          [&]() { controller_->Gif(m_myWidget); });
  // connect(ui->pb_gif, &QPushButton::clicked, this, [&]() { doGif(); });
  // connect(m_timerGif, &QTimer::timeout, this, &MainWindow::startGif);
}

// -------------------------------------------------------

void MainWindow::connectPerspective() {
  connect(ui->radioButton_central, &QRadioButton::pressed, this, [&]() {
    controller_->ChangePerspective(PerspectiveType::PERSPECTIVE_CENTRAL);
  });

  connect(ui->radioButton_parallel, &QRadioButton::pressed, this, [&]() {
    controller_->ChangePerspective(PerspectiveType::PERSPECTIVE_PARALLEL);
  });
}

// -------------------------------------------------------

void MainWindow::connectMouseRotate() {
  connect(ui->checkBox_mouseOn, &QCheckBox::stateChanged, this,
          [&](int const &state) { BlockSlideRotate(state); });
}

// -------------------------------------------------------

void MainWindow::connectsLineWidth() {
  connect(ui->hSlidder_widthLine, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->ChangeLineWidth(value); });
  connect(ui->lineEdit_widthLine, &QLineEdit::textEdited, this,
          [&](QString const &value) {
            controller_->ChangeLineWidth(value.toDouble());
          });
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
