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

void Controller::MoveDirectionX(float const &value, MoveType const &direction) {
  model_->MoveDirectionSlider(direction, value);
  view_->ChangeMoveSliderX(value);
}

// ----------------------------------------------------------------------------

void Controller::MoveDirectionY(float const &value, MoveType const &direction) {
  model_->MoveDirectionSlider(direction, value);
  view_->ChangeMoveSliderY(value);
}

// ----------------------------------------------------------------------------

void Controller::MoveDirectionZ(float const &value, MoveType const &direction) {
  model_->MoveDirectionSlider(direction, value);
  view_->ChangeMoveSliderZ(value);
}

void Controller::MoveRotationX(float const &value,
                               MoveRotationType const &direction) {
  model_->MoveRotationSlider(direction, value);
  view_->ChangeRotateSlidersX(value);
}

void Controller::MoveRotationY(float const &value,
                               MoveRotationType const &direction) {
  model_->MoveRotationSlider(direction, value);
  view_->ChangeRotateSlidersY(value);
}

void Controller::MoveRotationZ(float const &value,
                               MoveRotationType const &direction) {
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
  view_->ChangeLineWidth(value);
  model_->ChangeLineWidth(value);
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

void Controller::Gif(QWidget *widget) {
  model_->Gif(widget);
  view_->BlockGifButton(true);
}

// ----------------------------------------------------------------------------

}  // namespace s21
