#include "../../includes/Controller/controller.hpp"

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

void Controller::SetRotateBuffY(int const &value) { Q_UNUSED(value); }

// ----------------------------------------------------------------------------

void Controller::SetRotateBuffX(int const &value) { Q_UNUSED(value); }

// ----------------------------------------------------------------------------

void Controller::SetRotateBuffZ(int const &value) { Q_UNUSED(value); }

// ----------------------------------------------------------------------------

void Controller::MoveDirectionX(float value, MoveType direction) {
  Q_UNUSED(value);
  Q_UNUSED(direction);
}

// ----------------------------------------------------------------------------

void Controller::MoveDirectionY(float value, MoveType direction) {
  Q_UNUSED(value);
  Q_UNUSED(direction);
}

// ----------------------------------------------------------------------------

void Controller::MoveDirectionZ(float value, MoveType direction) {
  Q_UNUSED(value);
  Q_UNUSED(direction);
}

// ----------------------------------------------------------------------------

void Controller::MoveRotationX(float value, MoveType direction) {
  Q_UNUSED(value);
  Q_UNUSED(direction);
}

// ----------------------------------------------------------------------------

void Controller::MoveRotationY(float value, MoveType direction) {
  Q_UNUSED(value);
  Q_UNUSED(direction);
}

// ----------------------------------------------------------------------------

void Controller::MoveRotationZ(float value, MoveType direction) {
  Q_UNUSED(value);
  Q_UNUSED(direction);
}

// ----------------------------------------------------------------------------

}  // namespace s21
