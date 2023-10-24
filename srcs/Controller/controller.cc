#include "../../includes/Controller/controller.hpp"

namespace s21 {

Controller::Controller() {}

Controller::~Controller() {
  // TODO(_who): remove
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
