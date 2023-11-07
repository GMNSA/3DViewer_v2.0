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

  void Update() override;
  void ChangeMoveSliderX(int const &value);
  void ChangeMoveSliderY(int const &value);
  void ChangeMoveSliderZ(int const &value);
  void ChangeRotateSlidersY(int const &value);
  void ChangeRotateSlidersZ(int const &value);
  void ChangeRotateSlidersX(int const &value);
  void ChangeLineWidth(double const &width);
  void ChangePointSize(int const &value);

  void BlockSlideRotate(bool const &is_block);

  void openFileDialog();

  // void screenshotJPEG();
  //  void screenshotBMP();

 private slots:
  void closeApp();

  void lineScaleChange(QString value_);

  // void changeBackgroundColor(int value_);
  // void changeColorLines(int value_);
  // void changeColorPoints(int value_);

  // void changeWidthLines(int value_);
  void changePerperpertiveRdb(int value_);

  void moveObject(int type_, int value_);

 private:
  Ui::MainWindow *ui;

  IControllerInterface *controller_;
  IFacadeModel *model_;
  MyWidgetOPenGL *m_myWidget;

  QLabel *m_labelGifTime;

 private:
  void connectsConfiguration();
  // void changeRotateSliders();

  void connectsMoves();
  void connectsRotate();
  void connectsColor();
  void connectsPointType();
  void connectsScale();
  void connectsImages();
  void connectsLineWidth();
  void connectPerspective();
  void connectMouseRotate();
};

}  // namespace s21

#endif  // INCLUDES_VIEW_MAINWINDOW_HPP_
