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

int ModelViewer::get_rotate_buff_x() const { return rotate_x_; }
int ModelViewer::get_rotate_buff_y() const { return rotate_y_; }
int ModelViewer::get_rotate_buff_z() const { return rotate_z_; }

// ----------------------------------------------------------------------------

void ModelViewer::MoveRotation(MoveRotationType direction, float value) {
  Q_UNUSED(direction);
  Q_UNUSED(value);
  float tmp = 0;
  int isError = 0;

  if (is_valid_) {
    switch (direction) {
      case MOVE_ROTATE_X:
        tmp = rotate_before_x_ - value;
        rotate_before_x_ = value;
        break;
      case MOVE_ROTATE_Y:
        tmp = rotate_before_y_ - value;
        rotate_before_y_ = value;
        break;
      case MOVE_ROTATE_Z:
        tmp = rotate_before_z_ - value;
        rotate_before_z_ = value;
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

void ModelViewer::MoveDirection(MoveType direction, float value) {
  value = value * model_->get_max_size() / 99;

  Point t;
  float tmp = 0;
  int isError = 0;

  switch (direction) {
    case MOVE_X:
      tmp = move_before_x_ - value;
      t = {tmp, 0, 0};
      move_before_x_ = value;
      break;
    case MOVE_Y:
      tmp = move_before_y_ - value;
      t = {0, tmp, 0};
      move_before_y_ = value;
      break;
    case MOVE_Z:
      tmp = move_before_z_ - value;
      t = {0, 0, tmp};
      move_before_z_ = value;
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

// ----------------------------------------------------------------------------

void ModelViewer::PolygonsClear() { model_->PolygonsClear(); }

// ----------------------------------------------------------------------------

void ModelViewer::Parse(QString const &str) {
  model_->Parse(str.toStdString());
}

// ----------------------------------------------------------------------------

ErrorType ModelViewer::Error() { return model_->get_error(); }

// ----------------------------------------------------------------------------

double ModelViewer::MaxSizePerpective() { return model_->get_max_size(); }

// ----------------------------------------------------------------------------

std::vector<Point> const &ModelViewer::PointsArray() {
  return model_->get_points_array();
}

// ----------------------------------------------------------------------------

std::vector<std::vector<int>> const &ModelViewer::Polygons() {
  return model_->get_polygons();
}

// ----------------------------------------------------------------------------

void ModelViewer::TurnObjectX(double const &rotate) {
  model_->TurnObj(rotate, 2);
}

// ----------------------------------------------------------------------------

void ModelViewer::TurnObjectY(double const &rotate) {
  model_->TurnObj(rotate, 1);
}

// ----------------------------------------------------------------------------

void ModelViewer::TurnObjectZ(double const &rotate) {
  model_->TurnObj(rotate, 3);
}

// ----------------------------------------------------------------------------

void ModelViewer::ScaleObject(double const &scale) { model_->ScaleObj(scale); }

// ----------------------------------------------------------------------------

void ModelViewer::Attach(IWidgetOpenglObserved *observer) {
  list_widget_opengl_.push_back(observer);
}

// ----------------------------------------------------------------------------

void ModelViewer::Detach(IWidgetOpenglObserved *observer) {
  list_widget_opengl_.removeOne(observer);
}

// ----------------------------------------------------------------------------

void ModelViewer::NotifyWidgetOpengl() {
  auto iter = list_widget_opengl_.begin();
  auto iter_end = list_widget_opengl_.end();

  while (iter != iter_end) {
    // (*iter)->UpdateWidgetOpengGl();
    // ++iter;
  }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

}  // namespace s21
