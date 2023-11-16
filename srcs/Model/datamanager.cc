#include "../../includes/Model/datamanager.hpp"

#include <QColor>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace s21 {
DataManager::DataManager() : is_valid_(false), default_path_("/config.json") {}

DataManager::~DataManager() {}

// -- -------------------------------------------- --

void DataManager::SaveData(QString const &path, DataViewer const &data) {
  is_valid_ = false;

  QString val;
  QString filename =
      path.isEmpty() ? QDir::currentPath() + default_path_ : path;

  qDebug() << "filename: " << filename;

  QFile file(filename);

  file.open(QIODevice::WriteOnly | QIODevice::Text);

  if (file.isOpen()) {
    QJsonObject tmp;

    tmp.insert("lineType", data.line_type);

    int tmp_perspective = 0;
    if (data.perspective == 4)
      tmp_perspective = 1;
    else if (data.perspective == 5)
      tmp_perspective = 0;

    tmp.insert("perspective", tmp_perspective);
    tmp.insert("lineWidth", data.line_width);
    tmp.insert("pointType", data.point_type);
    tmp.insert("pointSize", data.point_size);

    QJsonArray jsonArr;
    jsonArr.push_back(data.line_color.red());
    jsonArr.push_back(data.line_color.green());
    jsonArr.push_back(data.line_color.blue());

    tmp.insert("lineColor", jsonArr);

    QJsonArray jsonArrPointColor;
    jsonArrPointColor.push_back(data.point_color.red());
    jsonArrPointColor.push_back(data.point_color.green());
    jsonArrPointColor.push_back(data.point_color.blue());

    tmp.insert("pointColor", jsonArrPointColor);

    QJsonArray jsonArrBackColor;
    jsonArrBackColor.push_back(data.background_color.red());
    jsonArrBackColor.push_back(data.background_color.green());
    jsonArrBackColor.push_back(data.background_color.blue());

    tmp.insert("backColor", jsonArrBackColor);

    QTextStream out(&file);
    QJsonDocument jsonDocument;

    jsonDocument.setObject(tmp);

    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Indented);
    out << byteArray;
    file.close();

    is_valid_ = true;
  }
}

// -- -------------------------------------------- --

DataViewer DataManager::LoadData(QString const &path) {
  DataViewer tmp_data;
  tmp_data.ClearData();

  is_valid_ = true;
  QString val;
  QString filename =
      path.isEmpty() ? QDir::currentPath() + default_path_ : path;

  QFile file(filename);

  file.open(QIODevice::ReadOnly | QIODevice::Text);

  if (file.isOpen()) {
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("lineType"));
    if (!value.isUndefined() && is_valid_) {
      tmp_data.line_type = static_cast<LineType>((value.toInt()));
    } else {
      is_valid_ = false;
    }

    value = sett2.value(QString("perspective"));
    if (!value.isUndefined() && is_valid_) {
      tmp_data.perspective = (value.toInt());
    } else {
      is_valid_ = false;
    }

    value = sett2.value(QString("lineWidth"));
    if (!value.isUndefined() && is_valid_) {
      tmp_data.line_width = (value.toDouble());
    } else {
      is_valid_ = false;
    }

    value = sett2.value(QString("pointSize"));
    if (!value.isUndefined() && is_valid_) {
      tmp_data.point_size = (value.toInt());
    } else {
      is_valid_ = false;
    }

    value = sett2.value(QString("pointType"));
    if (!value.isUndefined() && is_valid_) {
      tmp_data.point_type = static_cast<PointType>((value.toInt()));
    } else {
      is_valid_ = false;
    }

    value = sett2.value(QString("lineColor"));
    QJsonArray arr = value.toArray();

    if (!value.isUndefined() && value.isArray() && arr.size() == 3 &&
        is_valid_) {
      tmp_data.line_color = {arr[0].toInt(), arr[1].toInt(), arr[2].toInt()};
    } else {
      is_valid_ = false;
    }

    value = sett2.value(QString("pointColor"));
    arr = value.toArray();

    if (!value.isUndefined() && value.isArray() && arr.size() == 3 &&
        is_valid_) {
      tmp_data.point_color = {arr[0].toInt(), arr[1].toInt(), arr[2].toInt()};
    } else {
      is_valid_ = false;
    }

    value = sett2.value(QString("backColor"));
    arr = value.toArray();

    if (!value.isUndefined() && value.isArray() && arr.size() == 3 &&
        is_valid_) {
      tmp_data.background_color = {arr[0].toInt(), arr[1].toInt(),
                                   arr[2].toInt()};
    } else {
      is_valid_ = false;
    }

  } else {
    is_valid_ = false;
  }

  return tmp_data;
}

bool DataManager::get_is_valid() { return is_valid_; }

}  // namespace s21
