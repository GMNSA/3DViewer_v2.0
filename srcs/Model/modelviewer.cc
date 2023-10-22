#include "../../includes/Model/modelviewer.hpp"

namespace s21 {

ModelViewer::ModelViewer() : model_(new Model) {
  // TODO(_who): releae
}

ModelViewer::~ModelViewer() {
  // TODO(_who): releae
  if (model_) delete model_;
}

// ----------------------------------------------------------------------------

void ModelViewer::set_rotate_buff_x(int const &rotate_x) { (void)rotate_x; }
void ModelViewer::set_rotate_buff_y(int const &rotate_y) { (void)rotate_y; }
void ModelViewer::set_rotate_buff_z(int const &rotate_z) { (void)rotate_z; }

int ModelViewer::get_rotate_buff_x() const { return m_rotateX; }
int ModelViewer::get_rotate_buff_y() const { return m_rotateY; }
int ModelViewer::get_rotate_buff_z() const { return m_rotateZ; }

// ----------------------------------------------------------------------------

void ModelViewer::MoveRotation(e_moveRotatinoType direction, float value) {
  Q_UNUSED(direction);
  Q_UNUSED(value);
  float tmp = 0;
  int isError = 0;

  if (m_isValid) {
    switch (direction) {
      case MOVE_ROTATE_X:
        tmp = m_rotateBeforeX - value;
        m_rotateBeforeX = value;
        break;
      case MOVE_ROTATE_Y:
        tmp = m_rotateBeforeY - value;
        m_rotateBeforeY = value;
        break;
      case MOVE_ROTATE_Z:
        tmp = m_rotateBeforeZ - value;
        m_rotateBeforeZ = value;
        break;
      default:
        isError = 1;
        break;
    }

    if (!isError) {
      model_->TurnObj(tmp, direction);
    }
    // update();
  }
}

// ----------------------------------------------------------------------------

void ModelViewer::MoveDirection(e_moveType direction, float value) {
  value = value * model_->max_size_ / 99;

  Point t;
  float tmp = 0;
  int isError = 0;

  switch (direction) {
    case MOVE_X:
      tmp = m_moveBeforeX - value;
      t = {tmp, 0, 0};
      m_moveBeforeX = value;
      break;
    case MOVE_Y:
      tmp = m_moveBeforeY - value;
      t = {0, tmp, 0};
      m_moveBeforeY = value;
      break;
    case MOVE_Z:
      tmp = m_moveBeforeZ - value;
      t = {0, 0, tmp};
      m_moveBeforeZ = value;
      break;
    default:
      isError = 1;
      break;
  }

  if (!isError) {
    model_->MoveObj(t);
  }
  // update();
}

}  // namespace s21
