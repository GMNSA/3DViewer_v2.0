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
  // model_->set_rotate_x(value);
  model_->MoveRotationSlider(direction, value);
  view_->ChangeRotateSlidersX(value);
}

void Controller::MoveRotationY(float value, MoveRotationType direction) {
  // model_->set_rotate_y(value);
  model_->MoveRotationSlider(direction, value);
  view_->ChangeRotateSlidersY(value);
}

void Controller::MoveRotationZ(float value, MoveRotationType direction) {
  // model_->set_rotate_z(value);
  model_->MoveRotationSlider(direction, value);
  view_->ChangeRotateSlidersZ(value);
}

// ----------------------------------------------------------------------------

void Controller::TurnObjectX(double const &rotate) {
  // model_->TurnObjectX(rotate);
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
  // TODO(_who): release
  model_->ChangeBackgroundColor(value);
}

// ----------------------------------------------------------------------------

void Controller::ChangePointColor(int const &value) {
  model_->ChangePointColor(value);
}

// ----------------------------------------------------------------------------

void Controller::ChangeLinesColor(int const &value) {
  model_->ChangeLinesColor(value);
  // TODO(_who): release set color lines
}

// ----------------------------------------------------------------------------

void Controller::OpenFile(QString const &value) {
  Q_UNUSED(value);
  model_->OpenFile(value);
}

// ----------------------------------------------------------------------------

void Controller::IncremenetScale() {
  model_->IncremenetScale();
  //  if (model_->get_is_valid()) {
  //    auto current_scale = model_->get_scale();
  //    if (model_->get_scale() < model_->get_max_scale()) {
  //      model_->set_scale(current_scale + 1);
  //      model_->ScaleObject(1.05);
  //      // scale_obj(1.05, &m_points);
  //      // emit on_scaleStep();
  //    }
  //  }
}

// ----------------------------------------------------------------------------

void Controller::DecrementScale() {
  model_->DecrementScale();
  // if (model_->get_is_valid()) {
  //   auto current_scale = model_->get_scale();
  //   if (model_->get_scale() > model_->get_min_scale()) {
  //     model_->set_scale(current_scale - 1);
  //     model_->ScaleObject(0.95);
  //     // scale_obj(0.95, &m_points);
  //     // emit on_scaleStep();
  //   }
  // }
}

// ----------------------------------------------------------------------------

void Controller::ChangeLineWidth(double const &value) {
  // TODO(_who): We wll to think maybe to move notifywidgetopen (model).
  GLfloat tmp_value = value / 10.0f;
  model_->ChangeLineWidth(tmp_value);
  view_->ChangeLineWidth(tmp_value);
}

// ----------------------------------------------------------------------------

void Controller::ChangePointSize(int const &value) {
  // TODO(_who): We wll to think maybe to move notifywidgetopen (model).
  model_->ChangePointSize(value);
  view_->ChangePointSize(value);
  // model_->NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

void Controller::ChangeTypePoint(PointType const &type) {
  model_->ChangeTypePoint(type);
  // model_->NotifyWidgetOpengl();
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
