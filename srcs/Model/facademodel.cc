#include "../includes/Model/facademodel.hpp"

#include "../includes/Model/customtypes.hpp"

namespace s21 {

FacadeModel::FacadeModel()
    : model_(new ModelViewer()),
      data_manager_(new DataManager()),
      image_capture_(new ImageCapture()) {}

FacadeModel::~FacadeModel() {
  if (model_) delete model_;
  if (data_manager_) delete data_manager_;
  if (image_capture_) delete image_capture_;
}

// ----------------------------------------------------------------------------

void FacadeModel::Attach(IWidgetOpenglObserver *observer) {
  list_widget_opengl_.push_back(observer);
}

void FacadeModel::Detach(IWidgetOpenglObserver *observer) {
  list_widget_opengl_.removeOne(observer);
}

void FacadeModel::NotifyWidgetOpengl() {
  QList<IWidgetOpenglObserver *>::iterator iter = list_widget_opengl_.begin();
  QList<IWidgetOpenglObserver *>::iterator iter_end = list_widget_opengl_.end();

  while (iter != iter_end) {
    (*iter)->Update();
    ++iter;
  }
}

void FacadeModel::NotifyWidgetOpenglInfo() {
  QList<IWidgetOpenglObserver *>::iterator iter = list_widget_opengl_.begin();
  QList<IWidgetOpenglObserver *>::iterator iter_end = list_widget_opengl_.end();

  while (iter != iter_end) {
    (*iter)->UpdateInfo();
    ++iter;
  }
}

// -- -- -- --

void FacadeModel::Attach(IMainWindowObserver *observer) {
  list_main_menu_.push_back(observer);
}

void FacadeModel::Detach(IMainWindowObserver *observer) {
  list_main_menu_.removeOne(observer);
}

void FacadeModel::NotifyMainWindow() {
  QList<IMainWindowObserver *>::iterator iter = list_main_menu_.begin();
  QList<IMainWindowObserver *>::iterator iter_end = list_main_menu_.end();

  while (iter != iter_end) {
    (*iter)->Update();
    ++iter;
  }
}

// ----------------------------------------------------------------------------

void FacadeModel::ChangeBackgroundColor(int const &value) {
  model_->SetBackgroundColor(value);
  NotifyWidgetOpengl();
}

void FacadeModel::ChangePointColor(int const &value) {
  model_->SetPointColor(value);
  NotifyWidgetOpengl();
}

void FacadeModel::ChangeLinesColor(int const &value) {
  model_->SetLinesColor(value);
  NotifyWidgetOpengl();
}

void FacadeModel::OpenFile(QString const &filename) {
  // LoadData();
  model_->SetFilename(filename);
  bool res = model_->OpenFileObject(filename);

  if (res) {
    NotifyWidgetOpenglInfo();
    NotifyMainWindow();
  }
}

void FacadeModel::ChangeLineWidth(double const &value) {
  model_->SetLineWidth(value);
  NotifyWidgetOpengl();
}

void FacadeModel::ChangePointSize(int const &value) {
  model_->SetPointSize(value);
  NotifyWidgetOpengl();
}

void FacadeModel::ChangeTypePoint(PointType const &type) {
  model_->SetPointType(type);
  NotifyWidgetOpengl();
}

void FacadeModel::ChangePerspective(int const &value) {
  model_->SetPerspective(value);
  NotifyWidgetOpengl();
}

void FacadeModel::ChangeLineType(LineType const &type) {
  model_->SetLineType(type);
  NotifyWidgetOpengl();
}

// ----------------------------------------------------------------------------

void FacadeModel::IncremenetScale() {
  auto current_scale = model_->GetDataViewer().count_scale;
  if (current_scale < model_->GetDataViewer().max_scale) {
    model_->SetScale(current_scale + 1);
    model_->ScaleObject(1.05);
    NotifyWidgetOpengl();
    NotifyMainWindow();
  }
}

void FacadeModel::DecrementScale() {
  auto current_scale = model_->GetDataViewer().count_scale;
  auto min_scale = model_->GetDataViewer().min_scale;

  if (current_scale > min_scale) {
    model_->SetScale(current_scale - 1);
    model_->ScaleObject(0.95);
    NotifyWidgetOpengl();
    NotifyMainWindow();
  }
}

void FacadeModel::ChangeScale(int const &value) {
  bool is_decrement = 0;
  auto n_scale = model_->GetDataViewer().count_scale;
  auto min_scale = model_->GetDataViewer().min_scale;
  auto max_scale = model_->GetDataViewer().max_scale;

  is_decrement = n_scale > value ? 1 : 0;

  if (is_decrement && value >= min_scale) {
    while (n_scale != value) {
      n_scale = model_->GetDataViewer().count_scale;
      DecrementScale();
    }
  } else if (!is_decrement && value <= max_scale) {
    while (n_scale != value) {
      n_scale = model_->GetDataViewer().count_scale;
      IncremenetScale();
    }
  }
}

// ----------------------------------------------------------------------------

DataViewer const &FacadeModel::GetDataViewer() const {
  return model_->GetDataViewer();
}

void FacadeModel::MoveRotationSlider(MoveRotationType direction, float value) {
  model_->MoveRotation(direction, value);
  NotifyWidgetOpengl();
}

void FacadeModel::MoveDirectionSlider(MoveType direction, float value) {
  model_->MoveDirection(direction, value);
  NotifyWidgetOpengl();
}

void FacadeModel::MoveRotationMouse(MoveRotationType direction, float value) {
  switch (direction) {
    case MOVE_ROTATE_X:
      model_->TurnObjectX(value);
      break;
    case MOVE_ROTATE_Y:
      model_->TurnObjectY(value);
      break;
    case MOVE_ROTATE_Z:
      break;
    default:
      break;
  }
  NotifyWidgetOpengl();
}

void FacadeModel::PolygonsClear() { model_->PolygonsClear(); }

ErrorType FacadeModel::get_error() { return {}; }

std::vector<Point> const &FacadeModel::PointsArray() {
  return model_->PointsArray();
}

std::vector<std::vector<int>> const &FacadeModel::Polygons() {
  return model_->Polygons();
}

// -- -- -- --

void FacadeModel::ResetData() { model_->DefaultConfig(); }

// -- -------------------------------------------- --

void FacadeModel::ScreenshotJPEG(QWidget *widget) {
  image_capture_->set_widget(widget);
  image_capture_->ScreenshotJPEG();
}

void FacadeModel::ScreenshotBMP(QWidget *widget) {
  image_capture_->set_widget(widget);
  image_capture_->ScreenshotBMP();
}

void FacadeModel::Gif(QWidget *widget) {
  image_capture_->set_widget(widget);
  image_capture_->DoGif();
}

QLabel *FacadeModel::GetLabelGifTime() const { return nullptr; }

// -- -------------------------------------------- --

bool FacadeModel::SaveData(QString const &path) {
  data_manager_->SaveData(path, model_->GetDataViewer());
  return data_manager_->get_is_valid();
}

bool FacadeModel::LoadData(QString const &path) {
  auto data = data_manager_->LoadData(path);
  model_->CopyData(data);
  bool res = model_->UpdateData();

  return res;
}

// -- -- -- --

}  // namespace s21
