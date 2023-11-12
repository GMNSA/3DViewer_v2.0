#ifndef INCLUDES_VIEW_MAINWINDOW_HPP_
#define INCLUDES_VIEW_MAINWINDOW_HPP_

// #include <stdbool.h>

#include <QLabel>
#include <QMainWindow>

#include "../Controller/icontrollerinterface.hpp"
#include "./imainmenuobserver.hpp"
#include "./mywidgetopengl.hpp"

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow, virtual public IMainWindowObserver {
  Q_OBJECT
  Q_INTERFACES(s21::IMainWindowObserver)

 public:
  MainWindow(IControllerInterface *controller, IFacadeModel *model,
             QWidget *parent = nullptr);
  ~MainWindow();

  void ChangeMoveSliderX(int const &value);
  void ChangeMoveSliderY(int const &value);
  void ChangeMoveSliderZ(int const &value);
  void ChangeRotateSlidersY(int const &value);
  void ChangeRotateSlidersZ(int const &value);
  void ChangeRotateSlidersX(int const &value);
  void ChangeLineWidth(double const &width);
  void ChangePointSize(int const &value);

  void BlockSlideRotate(bool const &is_block);

  void OpenFileDialog();

 public:  // -- override --
  void Update() override;

 private slots:
  void CloseApp();
  void ChangePerperpertiveRdb(int const &value_);

 private:
  Ui::MainWindow *ui;

  IControllerInterface *controller_;
  IFacadeModel *model_;
  MyWidgetOPenGL *my_widget_;

  static int const kRotate_value_slider_;

 private:
  void ConnectsConfiguration();
  void ConnectsMoves();
  void ConnectsRotate();
  void ConnectsColor();
  void ConnectsPointType();
  void ConnectsScale();
  void ConnectsImages();
  void ConnectsLineWidth();
  void ConnectPerspective();
  void ConnectMouseRotate();
};

}  // namespace s21

#endif  // INCLUDES_VIEW_MAINWINDOW_HPP_
