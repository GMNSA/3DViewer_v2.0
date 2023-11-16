#include "../../includes/Model/modelviewer.hpp"

#include <QColor>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>

namespace s21 {

ModelViewer::ModelViewer() : model_(new Model), data_viewer_(new DataViewer) {
  data_viewer_->ClearData();
  DefaultConfig();
  DefaultConfigSimple();
}

ModelViewer::~ModelViewer() {
  if (model_) delete model_;
  if (data_viewer_) delete data_viewer_;
}

// ----------------------------------------------------------------------------

void ModelViewer::SetRotateX(int const &rotate) {
  data_viewer_->rotate_x = rotate;
}
void ModelViewer::SetRotateY(int const &rotate) {
  data_viewer_->rotate_y = rotate;
}
void ModelViewer::SetRotateZ(int const &rotate) {
  data_viewer_->rotate_z = rotate;
}

// ----------------------------------------------------------------------------

void ModelViewer::SetBackgroundColor(int const value_) {
  if (value_ == 0 || value_ == 255) {
    data_viewer_->background_color.setHsl(0, 0, 0);
  } else {
    data_viewer_->background_color.setHsl(value_, 50, 50);
  }
}

// ----------------------------------------------------------------------------

void ModelViewer::SetPointColor(int const &value) {
  if (value == 0 || value == 255)
    data_viewer_->point_color.setHsl(255, 255, 255);
  else
    data_viewer_->point_color.setHsl(value, 80, 80);
}

// ----------------------------------------------------------------------------

void ModelViewer::SetPerspective(int const &value) {
  if (value != data_viewer_->perspective) {
    data_viewer_->perspective = value;
  }
}

void ModelViewer::SetFilename(QString const &path) {
  data_viewer_->filename_object = path;
}

void ModelViewer::CopyData(DataViewer const &other) {
  data_viewer_->background_color = other.background_color;
  data_viewer_->count_scale = other.count_scale;
  data_viewer_->filename_object = other.filename_object;
  data_viewer_->info_data = other.info_data;
  data_viewer_->is_valid = other.is_valid;
  data_viewer_->line_color = other.line_color;
  data_viewer_->line_type = other.line_type;
  data_viewer_->line_width = other.line_width;
  data_viewer_->max_perspective = other.max_perspective;
  data_viewer_->max_point_size = other.max_point_size;
  data_viewer_->max_scale = other.max_scale;
  data_viewer_->min_point_size = other.min_point_size;
  data_viewer_->min_scale = other.min_scale;
  data_viewer_->move_before_x = other.move_before_x;
  data_viewer_->move_before_y = other.move_before_y;
  data_viewer_->move_before_z = other.move_before_z;
  data_viewer_->perspective = other.perspective;
  data_viewer_->point_color = other.point_color;
  data_viewer_->point_size = other.point_size;
  data_viewer_->point_type = other.point_type;
  data_viewer_->rotate_before_x = other.rotate_before_x;
  data_viewer_->rotate_before_y = other.rotate_before_y;
  data_viewer_->rotate_before_z = other.rotate_before_z;
  data_viewer_->rotate_x = other.rotate_x;
  data_viewer_->rotate_y = other.rotate_y;
  data_viewer_->rotate_z = other.rotate_z;
  data_viewer_->size_perspective = other.size_perspective;
}

// ----------------------------------------------------------------------------

void ModelViewer::SetLineType(LineType const &type) {
  data_viewer_->line_type = type;
}

// ----------------------------------------------------------------------------

void ModelViewer::SetPointType(PointType const &type) {
  data_viewer_->point_type = type;
}

// ----------------------------------------------------------------------------

void ModelViewer::SetPointSize(double const &size) {
  if (size >= data_viewer_->min_point_size &&
      size <= data_viewer_->max_point_size) {
    data_viewer_->point_size = size;
  }
}

// ----------------------------------------------------------------------------

void ModelViewer::SetLinesColor(int const &value) {
  if (value == 0 || value == 255)
    data_viewer_->line_color.setHsl(255, 255, 255);
  else
    data_viewer_->line_color.setHsl(value, 80, 80);
}

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

void ModelViewer::SetLineWidth(double const &value) {
  data_viewer_->line_width = value;
}

// ----------------------------------------------------------------------------

void ModelViewer::SetScale(int const &value) {
  data_viewer_->count_scale = value;
}

// ----------------------------------------------------------------------------

void ModelViewer::SetMaxScale(int const &value) {
  data_viewer_->max_scale = value;
}

// ----------------------------------------------------------------------------

void ModelViewer::SetMinScale(int const &value) {
  data_viewer_->min_scale = value;
}

DataViewer const &ModelViewer::GetDataViewer() const { return *data_viewer_; }

// ----------------------------------------------------------------------------

bool ModelViewer::OpenFileObject(QString const &filename) {
  data_viewer_->filename_object = filename;
  return UpdateData();
}

// ----------------------------------------------------------------------------

void ModelViewer::MoveRotation(MoveRotationType const &direction,
                               float const &value) {
  float tmp = 0;
  int is_error = 0;

  if (data_viewer_->is_valid) {
    switch (direction) {
      case MOVE_ROTATE_X:
        tmp = data_viewer_->rotate_before_x - value;
        data_viewer_->rotate_before_x = value;
        break;
      case MOVE_ROTATE_Y:
        tmp = data_viewer_->rotate_before_y - value;
        data_viewer_->rotate_before_y = value;
        break;
      case MOVE_ROTATE_Z:
        tmp = data_viewer_->rotate_before_z - value;
        data_viewer_->rotate_before_z = value;
        break;
      default:
        is_error = 1;
        break;
    }

    if (!is_error) {
      model_->TurnObj(tmp, direction);
    }
  }
}

// ----------------------------------------------------------------------------

void ModelViewer::MoveDirection(MoveType const &direction, float const &value) {
  float tmp_value = value * model_->get_max_size() / 99.0;
  Point t;
  float tmp = 0;
  int isError = 0;

  switch (direction) {
    case MOVE_DIRECTION_X:
      tmp = data_viewer_->move_before_x - tmp_value;
      t = {tmp, 0, 0};
      data_viewer_->move_before_x = tmp_value;
      break;
    case MOVE_DIRECTION_Y:
      tmp = data_viewer_->move_before_y - tmp_value;
      t = {0, tmp, 0};
      data_viewer_->move_before_y = tmp_value;
      break;
    case MOVE_DIRECTION_Z:
      tmp = data_viewer_->move_before_z - tmp_value;
      t = {0, 0, tmp};
      data_viewer_->move_before_z = tmp_value;
      break;
    default:
      isError = 1;
      break;
  }

  if (!isError) model_->MoveObj(t);
}

// ----------------------------------------------------------------------------

void ModelViewer::PolygonsClear() { model_->PolygonsClear(); }

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
  model_->TurnObj(rotate, MoveRotationType::MOVE_ROTATE_X);
}

void ModelViewer::TurnObjectY(double const &rotate) {
  model_->TurnObj(rotate, MoveRotationType::MOVE_ROTATE_Y);
}

// ----------------------------------------------------------------------------

void ModelViewer::ScaleObject(double const &scale) { model_->ScaleObj(scale); }

// ----------------------------------------------------------------------------

void ModelViewer::DefaultConfig() {
  data_viewer_->line_type = LineType::LINE_SIMPLE;
  data_viewer_->perspective = 0;
  data_viewer_->line_width = 1.0;
  data_viewer_->point_size = 2;
  data_viewer_->point_type = PointType::POINT_NONE;
  data_viewer_->line_color = {1, 1, 1};
  data_viewer_->point_color = {1, 1, 1};
  data_viewer_->background_color = {1, 1, 1};
  data_viewer_->perspective = 0;
  data_viewer_->max_perspective = 0;
}

// ----------------------------------------------------------------------------

void ModelViewer::DefaultConfigSimple() {
  data_viewer_->count_scale = 10;
  data_viewer_->max_scale = 60;
  data_viewer_->min_scale = -40;
  data_viewer_->max_point_size = 25.0;
  data_viewer_->min_point_size = 0.0;
  data_viewer_->rotate_before_x = 0;
  data_viewer_->rotate_before_y = 0;
  data_viewer_->rotate_before_z = 0;
  data_viewer_->move_before_x = 0;
  data_viewer_->move_before_y = 0;
  data_viewer_->move_before_z = 0;
  data_viewer_->max_perspective = model_->get_max_size();
}

// ----------------------------------------------------------------------------

int ModelViewer::CountNumber(int number) {
  int result = 0;

  if (number > 0) {
    while (number > 0) {
      number /= 10;
      result++;
    }
  }

  return result;
}

// ----------------------------------------------------------------------------

bool ModelViewer::UpdateData() {
  QFileInfo check_file(data_viewer_->filename_object);
  bool is_res = false;
  data_viewer_->is_valid = false;

  model_->PolygonsClear();

  if (check_file.exists() && check_file.isFile() &&
      !data_viewer_->filename_object.isEmpty()) {
    model_->Parse(data_viewer_->filename_object.toStdString().c_str());

    if (model_->get_error() == ErrorType::ERROR_OK &&
        !data_viewer_->filename_object.isEmpty()) {
      is_res = true;
      DefaultConfigSimple();
      data_viewer_->is_valid = true;
      data_viewer_->size_perspective =
          pow(10, CountNumber(model_->get_max_size()));

      UpdateInfoObject();

      if (data_viewer_->perspective == 4)
        data_viewer_->perspective = 1;
      else if (data_viewer_->perspective == 5)
        data_viewer_->perspective = 0;
    } else {
      data_viewer_->info_data.ClearInfo();
      is_res = false;
    }
  } else {
    data_viewer_->info_data.ClearInfo();
    is_res = false;
  }

  return (is_res);
}

// ----------------------------------------------------------------------------

void ModelViewer::UpdateInfoObject() {
  if (data_viewer_->is_valid) {
    QFileInfo info(data_viewer_->filename_object);

    data_viewer_->info_data.label_name = ("Name: " + info.baseName());
    data_viewer_->info_data.label_vertex =
        ("    Vertes: " + QString::number(PointsArray().size()));
    data_viewer_->info_data.label_polygons =
        ("    Polygons: " +
         QString::number(Polygons().size() * PointsArray().size()));
  }
}

// ----------------------------------------------------------------------------

}  // namespace s21
