#include "../../includes/Controller/controller.hpp"

namespace s21 {

Controller::Controller(IFacadeModel *model) : model_(model) {
  if (!(view_ = new MainWindow(this, model_))) exit(-1);

  view_->show();
}

// ----------------------------------------------------------------------------

Controller::~Controller() {
  if (view_) delete view_;
}

// ----------------------------------------------------------------------------

void Controller::MoveDirectionX(float value, MoveType direction) {
  model_->MoveDirectionSlider(direction, value);
  view_->ChangeMoveSliderX(value);
}

// ----------------------------------------------------------------------------

void Controller::MoveDirectionY(float value, MoveType direction) {
  model_->MoveDirectionSlider(direction, value);
  view_->ChangeMoveSliderY(value);
}

// ----------------------------------------------------------------------------

void Controller::MoveDirectionZ(float value, MoveType direction) {
  model_->MoveDirectionSlider(direction, value);
  view_->ChangeMoveSliderZ(value);
}

void Controller::MoveRotationX(float value, MoveRotationType direction) {
  model_->MoveRotationSlider(direction, value);
  view_->ChangeRotateSlidersX(value);
}

void Controller::MoveRotationY(float value, MoveRotationType direction) {
  model_->MoveRotationSlider(direction, value);
  view_->ChangeRotateSlidersY(value);
}

void Controller::MoveRotationZ(float value, MoveRotationType direction) {
  model_->MoveRotationSlider(direction, value);
  view_->ChangeRotateSlidersZ(value);
}

// ----------------------------------------------------------------------------

void Controller::TurnObjectX(double const &rotate) {
  model_->MoveRotationMouse(MoveRotationType::MOVE_ROTATE_X, rotate);
}

// ----------------------------------------------------------------------------

void Controller::TurnObjectY(double const &rotate) {
  model_->MoveRotationMouse(MoveRotationType::MOVE_ROTATE_Y, rotate);
}

// ----------------------------------------------------------------------------

void Controller::WriteConfig(QString const &filename) {
  model_->SaveData(filename);
}

// ----------------------------------------------------------------------------

void Controller::LoadConfig(QString const &filename) {
  model_->LoadData(filename);
}

// ----------------------------------------------------------------------------

void Controller::ChangeBackgroundColor(int const &value) {
  model_->ChangeBackgroundColor(value);
}

// ----------------------------------------------------------------------------

void Controller::ChangePointColor(int const &value) {
  model_->ChangePointColor(value);
}

// ----------------------------------------------------------------------------

void Controller::ChangeLinesColor(int const &value) {
  model_->ChangeLinesColor(value);
}

// ----------------------------------------------------------------------------

void Controller::OpenFile(QString const &value) { model_->OpenFile(value); }

// ----------------------------------------------------------------------------

void Controller::IncremenetScale() { model_->IncremenetScale(); }

void Controller::DecrementScale() { model_->DecrementScale(); }

void Controller::ChangeScale(int const &value) { model_->ChangeScale(value); }

// ----------------------------------------------------------------------------

void Controller::ChangeLineWidth(double const &value) {
  GLfloat tmp_value = value / 10.0f;
  model_->ChangeLineWidth(tmp_value);
  view_->ChangeLineWidth(tmp_value * 10);
}

// ----------------------------------------------------------------------------

void Controller::ChangePointSize(int const &value) {
  model_->ChangePointSize(value);
  view_->ChangePointSize(value);
}

// ----------------------------------------------------------------------------

void Controller::ChangeTypePoint(PointType const &type) {
  model_->ChangeTypePoint(type);
}

// ----------------------------------------------------------------------------

void Controller::ChangePerspective(int const &value) {
  model_->ChangePerspective(value);
}

// ----------------------------------------------------------------------------

void Controller::ChangeLineType(LineType const &type) {
  model_->ChangeLineType(type);
}

// ----------------------------------------------------------------------------

void Controller::ScreenshotJPEG(QWidget *widget) {
  model_->ScreenshotJPEG(widget);
}

// ----------------------------------------------------------------------------

void Controller::ScreenshotBMP(QWidget *widget) {
  model_->ScreenshotBMP(widget);
}

// ----------------------------------------------------------------------------

void Controller::Gif(QWidget *widget) { model_->Gif(widget); }

// ----------------------------------------------------------------------------

}  // namespace s21
