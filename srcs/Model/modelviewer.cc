#include "../../includes/Model/modelviewer.hpp"

#include <QColor>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>

namespace s21 {

ModelViewer::ModelViewer()
    : model_(new Model),
      is_valid_(0),
      rotate_x_(0),
      rotate_y_(0),
      rotate_z_(0),
      rotate_before_x_(0),
      rotate_before_y_(0),
      rotate_before_z_(0),
      move_before_x_(0),
      move_before_y_(0),
      move_before_z_(0) {
  // TODO(_who): releae
  DefaultConfig();
  DefaultConfigSimple();
}

ModelViewer::~ModelViewer() {
  // TODO(_who): releae
  if (model_) delete model_;
}

// ----------------------------------------------------------------------------

void ModelViewer::set_rotate_x(int const &rotate) { rotate_x_ = rotate; }
void ModelViewer::set_rotate_y(int const &rotate) { rotate_y_ = rotate; }
void ModelViewer::set_rotate_z(int const &rotate) { rotate_z_ = rotate; }

int ModelViewer::get_rotate_x() const { return rotate_x_; }
int ModelViewer::get_rotate_y() const { return rotate_y_; }
int ModelViewer::get_rotate_z() const { return rotate_z_; }

void ModelViewer::set_rotate_buff_x(int const &rotate) { rotate_x_ = rotate; }
void ModelViewer::set_rotate_buff_y(int const &rotate) { rotate_y_ = rotate; }
void ModelViewer::set_rotate_buff_z(int const &rotate) { rotate_z_ = rotate; }

int ModelViewer::get_rotate_buff_x() const { return rotate_x_; }
int ModelViewer::get_rotate_buff_y() const { return rotate_y_; }
int ModelViewer::get_rotate_buff_z() const { return rotate_z_; }

// ----------------------------------------------------------------------------

void ModelViewer::set_background_color(int value_) {
  if (value_ == 0 || value_ == 255) {
    background_color_.setHsl(0, 0, 0);
    // labelName->setStyleSheet("QLabel { color : white; }");
    // labelVertes->setStyleSheet("QLabel { color : white; }");
    // labelPolygons->setStyleSheet("QLabel { color : white; }");

    // TODO:(_who): We need to think how to implement the (ColorGifTime)
    // emit on_changeColorGifTime(0);
  } else {
    background_color_.setHsl(value_, 50, 50);
    // m_labelName->setStyleSheet("QLabel { color : black; }");
    // m_labelVertes->setStyleSheet("QLabel { color : black; }");
    // m_labelPolygons->setStyleSheet("QLabel { color : black; }");
    // emit on_changeColorGifTime(1);
  }

  NotifyWidgetOpengl();
}

QColor ModelViewer::get_background_color() const { return background_color_; }

// ----------------------------------------------------------------------------

void ModelViewer::set_point_color(int const &value) {
  if (value == 0 || value == 255)
    point_color_.setHsl(255, 255, 255);
  else
    point_color_.setHsl(value, 80, 80);
  NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

void ModelViewer::set_perspective(int const &value) {
  if (value != perspective_) {
    perspective_ = value;
    NotifyWidgetOpengl();
  }
}

// ----------------------------------------------------------------------------

int ModelViewer::get_perspective() const { return perspective_; }

// ----------------------------------------------------------------------------

double ModelViewer::get_size_perspective() const { return size_perspective_; }

// ----------------------------------------------------------------------------

QString ModelViewer::get_filename_object() const { return filename_object_; }

// ----------------------------------------------------------------------------

bool ModelViewer::get_is_valid() const { return is_valid_; }

// ----------------------------------------------------------------------------

void ModelViewer::set_line_type(LineType const &type) {
  line_type_ = type;
  NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

LineType ModelViewer::get_line_type() const { return line_type_; }

// ----------------------------------------------------------------------------

void ModelViewer::set_point_type(PointType const &type) { point_type_ = type; }

// ----------------------------------------------------------------------------

PointType ModelViewer::get_point_type() const { return point_type_; }

// ----------------------------------------------------------------------------

void ModelViewer::set_point_size(double const &size) {
  if (size >= min_point_size_ && size <= max_point_size_) {
    point_size_ = size;
    // NotifyWidgetOpengl();
    // TODO(_who): need pofix
    // m_pointSize = newPointSize;
    // !! update();
  }
}

// ----------------------------------------------------------------------------

QColor ModelViewer::get_point_color() const { return point_color_; }

// ----------------------------------------------------------------------------

void ModelViewer::set_lines_color(int const &value) {
  if (value == 0 || value == 255)
    line_color_.setHsl(255, 255, 255);
  else
    line_color_.setHsl(value, 80, 80);
  NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

QColor ModelViewer::get_lines_color() const { return line_color_; }
// ----------------------------------------------------------------------------

double ModelViewer::get_point_size() const { return point_size_; }

// ----------------------------------------------------------------------------

double ModelViewer::get_point_size_max() const { return max_point_size_; }

// ----------------------------------------------------------------------------

double ModelViewer::get_point_size_min() const { return min_point_size_; }

// ----------------------------------------------------------------------------

void ModelViewer::set_line_width(double const &value) { line_width_ = value; }

// ----------------------------------------------------------------------------

double ModelViewer::get_line_width() const { return line_width_; }

// ----------------------------------------------------------------------------

void ModelViewer::set_scale(int const &value) { count_scale_ = value; }

// ----------------------------------------------------------------------------

void ModelViewer::set_max_scale(int const &value) { max_scale_ = value; }

// ----------------------------------------------------------------------------

void ModelViewer::set_min_scale(int const &value) { min_scale_ = value; }

// ----------------------------------------------------------------------------

int ModelViewer::get_scale() const { return count_scale_; }

// ----------------------------------------------------------------------------

int ModelViewer::get_max_scale() const { return max_scale_; }

// ----------------------------------------------------------------------------

int ModelViewer::get_min_scale() const { return min_scale_; }

// ----------------------------------------------------------------------------

void ModelViewer::OpenFileObject(QString const &filename) {
  filename_object_ = filename;
  UpdateData();
  NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

void ModelViewer::MoveRotation(MoveRotationType direction, float value) {
  Q_UNUSED(direction);
  Q_UNUSED(value);
  float tmp = 0;
  int is_error = 0;

  qDebug() << "rotate_before x: " << rotate_before_x_;
  qDebug() << "rotate_before y: " << rotate_before_y_;
  qDebug() << "rotate_before z: " << rotate_before_z_;
  qDebug() << "value: " << value;

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
        is_error = 1;
        break;
    }

    if (!is_error) {
      model_->TurnObj(tmp, direction);
      NotifyMainWindow();
      NotifyWidgetOpengl();
    }
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

  if (!isError) model_->MoveObj(t);
  NotifyWidgetOpengl();
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
  model_->TurnObj(rotate, MoveRotationType::MOVE_ROTATE_X);
  NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

void ModelViewer::TurnObjectY(double const &rotate) {
  model_->TurnObj(rotate, MoveRotationType::MOVE_ROTATE_Y);
  NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

// void ModelViewer::TurnObjectZ(double const &rotate) {
//   model_->TurnObj(rotate, 3);
// }

// ----------------------------------------------------------------------------

void ModelViewer::ScaleObject(double const &scale) {
  model_->ScaleObj(scale);
  NotifyMainWindow();
  NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

void ModelViewer::Attach(IWidgetOpenglObserver *observer) {
  list_widget_opengl_.push_back(observer);
}

// ----------------------------------------------------------------------------

void ModelViewer::Detach(IWidgetOpenglObserver *observer) {
  list_widget_opengl_.removeOne(observer);
}

// ----------------------------------------------------------------------------

void ModelViewer::NotifyWidgetOpengl() {
  QList<IWidgetOpenglObserver *>::iterator iter = list_widget_opengl_.begin();
  QList<IWidgetOpenglObserver *>::iterator iter_end = list_widget_opengl_.end();

  while (iter != iter_end) {
    (*iter)->Update();
    ++iter;
  }
}

// ----------------------------------------------------------------------------

void ModelViewer::NotifyWidgetOpenglInfo() {
  QList<IWidgetOpenglObserver *>::iterator iter = list_widget_opengl_.begin();
  QList<IWidgetOpenglObserver *>::iterator iter_end = list_widget_opengl_.end();

  while (iter != iter_end) {
    (*iter)->UpdateInfo();
    ++iter;
  }
}

// ----------------------------------------------------------------------------

void ModelViewer::Attach(IMainWindowObserver *observer) {
  list_main_menu_.push_back(observer);
}

// ----------------------------------------------------------------------------

void ModelViewer::Detach(IMainWindowObserver *observer) {
  list_main_menu_.removeOne(observer);
}

// ----------------------------------------------------------------------------

void ModelViewer::NotifyMainWindow() {
  QList<IMainWindowObserver *>::iterator iter = list_main_menu_.begin();
  QList<IMainWindowObserver *>::iterator iter_end = list_main_menu_.end();

  while (iter != iter_end) {
    (*iter)->Update();
    ++iter;
  }
}

// ----------------------------------------------------------------------------

void ModelViewer::DefaultConfig() {
  line_type_ = LineType::LINE_SIMPLE;
  perspective_ = 0;
  line_width_ = 1;
  point_size_ = 2;
  point_type_ = PointType::POINT_NONE;
  line_color_ = {1, 1, 1};
  point_color_ = {1, 1, 1};
  background_color_ = {1, 1, 1};
  perspective_ = 0;
}

// ----------------------------------------------------------------------------

void ModelViewer::DefaultConfigSimple() {
  count_scale_ = 10;
  max_scale_ = 60;
  min_scale_ = -40;
  max_point_size_ = 25.0;
  min_point_size_ = 0.0;
  rotate_before_x_ = 0;
  rotate_before_y_ = 0;
  rotate_before_z_ = 0;
  move_before_x_ = 0;
  move_before_y_ = 0;
  move_before_z_ = 0;
}

// ----------------------------------------------------------------------------

bool ModelViewer::WriteToFileConfig(QString path) {
  bool is_res = true;

  QString val;
  QString filename =
      path.isEmpty() ? QDir::currentPath() + "/config.json" : path;

  qDebug() << "filename: " << filename;

  QFile file(filename);

  file.open(QIODevice::WriteOnly | QIODevice::Text);

  if (file.isOpen()) {
    QJsonObject tmp;

    tmp.insert("lineType", line_type_);

    if (perspective_ == 4)
      perspective_ = 1;
    else if (perspective_ == 5)
      perspective_ = 0;

    tmp.insert("perspective", perspective_);
    tmp.insert("lineWidth", line_width_);
    tmp.insert("pointType", point_type_);
    tmp.insert("pointSize", point_size_);

    QJsonArray jsonArr;
    jsonArr.push_back(line_color_.red());
    jsonArr.push_back(line_color_.green());
    jsonArr.push_back(line_color_.blue());

    tmp.insert("lineColor", jsonArr);

    QJsonArray jsonArrPointColor;
    jsonArrPointColor.push_back(point_color_.red());
    jsonArrPointColor.push_back(point_color_.green());
    jsonArrPointColor.push_back(point_color_.blue());

    tmp.insert("pointColor", jsonArrPointColor);

    QJsonArray jsonArrBackColor;
    jsonArrBackColor.push_back(background_color_.red());
    jsonArrBackColor.push_back(background_color_.green());
    jsonArrBackColor.push_back(background_color_.blue());

    tmp.insert("backColor", jsonArrBackColor);

    QTextStream out(&file);
    QJsonDocument jsonDocument;

    jsonDocument.setObject(tmp);

    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Indented);
    out << byteArray;
    file.close();
  }

  return is_res;
}

// ----------------------------------------------------------------------------

bool ModelViewer::LoadConfig(QString path_) {
  bool is_res = 1;
  QString val;
  QString filename =
      path_.isEmpty() ? QDir::currentPath() + "/config.json" : path_;

  QFile file(filename);

  file.open(QIODevice::ReadOnly | QIODevice::Text);

  if (file.isOpen()) {
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("lineType"));
    if (!value.isUndefined() && is_res) {
      line_type_ = static_cast<LineType>((value.toInt()));
    } else {
      is_res = 0;
    }

    value = sett2.value(QString("perspective"));
    if (!value.isUndefined() && is_res) {
      perspective_ = (value.toInt());
    } else {
      is_res = 0;
    }

    value = sett2.value(QString("lineWidth"));
    if (!value.isUndefined() && is_res) {
      line_width_ = (value.toDouble());
    } else {
      is_res = 0;
    }

    value = sett2.value(QString("pointSize"));
    if (!value.isUndefined() && is_res) {
      point_size_ = (value.toInt());
    } else {
      is_res = 0;
    }

    value = sett2.value(QString("pointType"));
    if (!value.isUndefined() && is_res) {
      point_type_ = static_cast<PointType>((value.toInt()));
    } else {
      is_res = 0;
    }

    value = sett2.value(QString("lineColor"));
    QJsonArray arr = value.toArray();

    if (!value.isUndefined() && value.isArray() && arr.size() == 3 && is_res) {
      line_color_ = {arr[0].toInt(), arr[1].toInt(), arr[2].toInt()};
    } else {
      is_res = 0;
    }

    value = sett2.value(QString("pointColor"));
    arr = value.toArray();

    if (!value.isUndefined() && value.isArray() && arr.size() == 3 && is_res) {
      point_color_ = {arr[0].toInt(), arr[1].toInt(), arr[2].toInt()};
    } else {
      is_res = 0;
    }

    value = sett2.value(QString("backColor"));
    arr = value.toArray();

    if (!value.isUndefined() && value.isArray() && arr.size() == 3 && is_res) {
      background_color_ = {arr[0].toInt(), arr[1].toInt(), arr[2].toInt()};
    } else {
      is_res = 0;
    }

  } else {
    is_res = 0;

    // TODO:(_who) don't forget release "Default Config"
    // DefaultConfig();
    NotifyWidgetOpengl();
    NotifyMainWindow();
  }

  return (is_res);
}

// ----------------------------------------------------------------------------

int ModelViewer::CountNumber(int number_) {
  int result = 0;

  if (number_ > 0) {
    while (number_ > 0) {
      number_ /= 10;
      result++;
    }
  }

  return result;
}

// ----------------------------------------------------------------------------

int ModelViewer::UpdateData() {
  QFileInfo check_file(filename_object_);
  bool is_res = false;
  is_valid_ = false;

  model_->PolygonsClear();

  if (check_file.exists() && check_file.isFile() &&
      !filename_object_.isEmpty()) {
    model_->Parse(filename_object_.toStdString().c_str());

    if (model_->get_error() == ErrorType::ERROR_OK &&
        !filename_object_.isEmpty()) {
      // TODO(_who): don't forget release DefaultConfigSimple
      DefaultConfigSimple();
      is_valid_ = true;
      size_perspective_ = pow(10, CountNumber(model_->get_max_size()));

      // updateInfoObject();
      NotifyWidgetOpenglInfo();
      NotifyMainWindow();

      // emit on_changePerperpertiveRdb(m_perspective);

      if (perspective_ == 4)
        perspective_ = 1;
      else if (perspective_ == 5)
        perspective_ = 0;
    } else {
      // clearInfo();
    }
  } else {
    // clearInfo();
  }

  return (is_res);
}

}  // namespace s21
