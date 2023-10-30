#include "../../includes/Controller/controller.hpp"

#include <GL/gl.h>

namespace s21 {

Controller::Controller(IModelViewer *model) : model_(model) {
  if (!(view_ = new MainWindow(this, model_))) exit(-1);

  view_->show();
}

// ----------------------------------------------------------------------------

Controller::~Controller() {
  if (view_) delete view_;
}

// ----------------------------------------------------------------------------

void Controller::SetRotateBuffY(int const &value) {
  model_->set_rotate_buff_y(value);
}

// ----------------------------------------------------------------------------

void Controller::SetRotateBuffX(int const &value) {
  model_->set_rotate_buff_x(value);
}

// ----------------------------------------------------------------------------

void Controller::SetRotateBuffZ(int const &value) {
  model_->set_rotate_buff_z(value);
}

// ----------------------------------------------------------------------------

void Controller::MoveDirectionX(float value, MoveType direction) {
  model_->MoveDirection(direction, value);
}

// ----------------------------------------------------------------------------

void Controller::MoveDirectionY(float value, MoveType direction) {
  model_->MoveDirection(direction, value);
}

// ----------------------------------------------------------------------------

void Controller::MoveDirectionZ(float value, MoveType direction) {
  model_->MoveDirection(direction, value);
}

// ----------------------------------------------------------------------------

void Controller::MoveRotationX(float value, MoveRotationType direction) {
  model_->set_rotate_buff_x(value);
  model_->MoveRotation(direction, value);
}

// ----------------------------------------------------------------------------

void Controller::MoveRotationY(float value, MoveRotationType direction) {
  model_->set_rotate_buff_y(value);
  model_->MoveRotation(direction, value);
}

// ----------------------------------------------------------------------------

void Controller::MoveRotationZ(float value, MoveRotationType direction) {
  model_->set_rotate_buff_z(value);
  model_->MoveRotation(direction, value);
}

// ----------------------------------------------------------------------------

void Controller::TurnObjectX(double const &rotate) {
  model_->TurnObjectX(rotate);
}

// ----------------------------------------------------------------------------

void Controller::TurnObjectY(double const &rotate) {
  model_->TurnObjectY(rotate);
}

// ----------------------------------------------------------------------------

void Controller::WriteConfig(QString const &filename) {
  model_->WriteToFileConfig(filename);
}

// ----------------------------------------------------------------------------

void Controller::LoadConfig(QString const &filename) {
  model_->LoadConfig(filename);
}

// ----------------------------------------------------------------------------

void Controller::ChangeBackgroundColor(int const &value) {
  // TODO(_who): release
  model_->set_background_color(value);
}

// ----------------------------------------------------------------------------

void Controller::ChangePointColor(int const &value) {
  model_->set_point_color(value);
}

// ----------------------------------------------------------------------------

void Controller::ChangeLinesColor(int const &value) {
  model_->set_lines_color(value);
  // TODO(_who): release set color lines
}

// ----------------------------------------------------------------------------

void Controller::OpenFile(QString const &value) {
  model_->OpenFileObject(value);
}

// ----------------------------------------------------------------------------

void Controller::IncremenetScale() {
  if (model_->get_is_valid()) {
    auto current_scale = model_->get_scale();
    if (model_->get_scale() < model_->get_max_scale()) {
      model_->set_scale(current_scale + 1);
      model_->ScaleObject(1.05);
      // scale_obj(1.05, &m_points);
      // emit on_scaleStep();
    }
  }
}

// ----------------------------------------------------------------------------

void Controller::DecrementScale() {
  if (model_->get_is_valid()) {
    auto current_scale = model_->get_scale();
    if (model_->get_scale() > model_->get_min_scale()) {
      model_->set_scale(current_scale - 1);
      model_->ScaleObject(0.95);
      // scale_obj(0.95, &m_points);
      // emit on_scaleStep();
    }
  }
}

// ----------------------------------------------------------------------------

void Controller::ChangeLineWidth(int const &value) {
  // TODO(_who): We wll to think maybe to move notifywidgetopen (model).
  GLfloat tmp_value = value / 10.0f;
  model_->set_line_width(tmp_value);
  model_->NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

void Controller::ChangePointSize(int const &value) {
  // TODO(_who): We wll to think maybe to move notifywidgetopen (model).
  qDebug() << "Change point size [controller]: ";
  model_->set_point_size(value);
  model_->NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

void Controller::ChangeTypePoint(PointType const &type) {
  model_->set_point_type(type);
  model_->NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

void Controller::ChangePerspective(int const &value) {
  model_->set_perspective(value);
}

// ----------------------------------------------------------------------------

void Controller::ChangeLineType(LineType const &type) {
  model_->set_line_type(type);
}

// ----------------------------------------------------------------------------

}  // namespace s21
