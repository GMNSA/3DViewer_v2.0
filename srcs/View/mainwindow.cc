#include "../../includes/View/mainwindow.hpp"

#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

#include "./ui_mainwindow.h"

// -------------------------------------------------------

namespace s21 {

int const MainWindow::kRotate_value_slider_ = 720;

MainWindow::MainWindow(IControllerInterface *controller, IFacadeModel *model,
                       QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(controller),
      model_(model),
      my_widget_(new MyWidgetOPenGL(controller, model, this)) {
  ui->setupUi(this);
  model_->Attach(qobject_cast<IMainWindowObserver *>(this));

  ui->radioButton_solid->setChecked(true);
  ui->radioButton_no->setChecked(true);

  my_widget_->setParent(ui->widget);
  my_widget_->show();

  ConnectsConfiguration();
  controller_->LoadConfig();
}

// -------------------------------------------------------

MainWindow::~MainWindow() { delete ui; }

// -------------------------------------------------------

void MainWindow::Update() {
  auto data = model_->GetDataViewer();

  ChangePerperpertiveRdb(data.perspective);
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
  int x = (value % kRotate_value_slider_);

  ui->slider_x->setValue(x);
  ui->lineEdit_rotateX->setText(QString::number(x));
}

void MainWindow::ChangeRotateSlidersY(int const &value) {
  int y = (value % kRotate_value_slider_);

  ui->slider_y->setValue(y);
  ui->lineEdit_rotateY->setText(QString::number(y));
}

void MainWindow::ChangeRotateSlidersZ(int const &value) {
  int z = (value % kRotate_value_slider_);

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
    my_widget_->TurnOffMouse();
  } else {
    ui->slider_x->setEnabled(false);
    ui->slider_y->setEnabled(false);
    ui->slider_z->setEnabled(false);
    ui->lineEdit_rotateX->setEnabled(false);
    ui->lineEdit_rotateY->setEnabled(false);
    ui->lineEdit_rotateZ->setEnabled(false);
    my_widget_->TurnOnMouse();
  }
}
// -------------------------------------------------------

void MainWindow::OpenFileDialog() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open Object"), "./objects/", tr("Image Files (*.obj)"));
  controller_->OpenFile(filename);
}

// -------------------------------------------------------

void MainWindow::ConnectsConfiguration() {
  connect(ui->pb_openFIle, &QPushButton::clicked, this,
          &MainWindow::OpenFileDialog);

  connect(ui->widget, &QOpenGLWidget::resized, this, [&]() {
    my_widget_->resize(ui->widget->width(), ui->widget->height());
  });

  connect(ui->radioButton_dotter, &QRadioButton::pressed, this,
          [&]() { controller_->ChangeLineType(LineType::LINE_STIPPLE); });

  connect(ui->radioButton_solid, &QRadioButton::pressed, this,
          [&]() { controller_->ChangeLineType(LineType::LINE_SIMPLE); });

  connect(ui->hSlidder_pointsSize, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->ChangePointSize(value); });

  ConnectsPointType();
  ConnectsRotate();
  ConnectsMoves();
  ConnectsColor();
  ConnectsScale();
  ConnectsImages();
  ConnectsLineWidth();
  ConnectPerspective();
  ConnectMouseRotate();
}

// -------------------------------------------------------

void MainWindow::CloseApp() {
  controller_->WriteConfig();
  close();
}

// -------------------------------------------------------

// -------------------------------------------------------

void MainWindow::ConnectsMoves() {
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

void MainWindow::ConnectsRotate() {
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
}

// -------------------------------------------------------

void MainWindow::ConnectsColor() {
  connect(ui->hSlider_colorLines, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->ChangeLinesColor(value); });
  connect(ui->hSlider_backgroundColor, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->ChangeBackgroundColor(value); });
  connect(ui->hSlider_colorPoints, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->ChangePointColor(value); });
}

// -------------------------------------------------------

void MainWindow::ConnectsPointType() {
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

void MainWindow::ConnectsScale() {
  connect(ui->pb_changeScale, &QPushButton::clicked, this, [&]() {
    controller_->ChangeScale(ui->lineEdit_scale->text().toInt());
  });

  connect(ui->pb_scalePlus, &QPushButton::clicked, my_widget_,
          [&] { controller_->IncremenetScale(); });
  connect(ui->pb_scaleMinus, &QPushButton::clicked, my_widget_,
          [&] { controller_->DecrementScale(); });
}

// -------------------------------------------------------

void MainWindow::ConnectsImages() {
  connect(ui->pb_jpeg, &QPushButton::clicked, this,
          [&]() { controller_->ScreenshotJPEG(my_widget_); });
  connect(ui->pb_bmp, &QPushButton::clicked, this,
          [&]() { controller_->ScreenshotBMP(my_widget_); });
  connect(ui->pb_gif, &QPushButton::clicked, this,
          [&]() { controller_->Gif(my_widget_); });
}

// -------------------------------------------------------

void MainWindow::ConnectPerspective() {
  connect(ui->radioButton_central, &QRadioButton::pressed, this, [&]() {
    controller_->ChangePerspective(PerspectiveType::PERSPECTIVE_CENTRAL);
  });

  connect(ui->radioButton_parallel, &QRadioButton::pressed, this, [&]() {
    controller_->ChangePerspective(PerspectiveType::PERSPECTIVE_PARALLEL);
  });
}

// -------------------------------------------------------

void MainWindow::ConnectMouseRotate() {
  connect(ui->checkBox_mouseOn, &QCheckBox::stateChanged, this,
          [&](int const &state) { BlockSlideRotate(state); });
}

// -------------------------------------------------------

void MainWindow::ConnectsLineWidth() {
  connect(ui->hSlidder_widthLine, &QSlider::valueChanged, this,
          [&](int const &value) { controller_->ChangeLineWidth(value); });
  connect(ui->lineEdit_widthLine, &QLineEdit::textEdited, this,
          [&](QString const &value) {
            controller_->ChangeLineWidth(value.toDouble());
          });
}

// -------------------------------------------------------

void MainWindow::ChangePerperpertiveRdb(int const &value) {
  if (value == 1)
    ui->radioButton_parallel->setChecked(true);
  else
    ui->radioButton_central->setChecked(true);
}

}  // namespace s21
