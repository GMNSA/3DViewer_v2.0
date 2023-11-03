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
  MainWindow(IControllerInterface *controller, IModelViewer *model,
             QWidget *parent = nullptr);
  ~MainWindow();

  void Update() override;

 private slots:
  void openFileDialog();

  void rotateX(int value_);
  void rotateY(int value_);
  void rotateZ(int value_);

  // void screenshotJPEG();
  //  void screenshotBMP();

 private slots:
  void closeApp();

  void lineScaleChange(QString value_);

  void changeBackgroundColor(int value_);
  void changeColorLines(int value_);
  void changeColorPoints(int value_);

  void changeWidthLines(int value_);
  void changeSizePoint(int value_);
  void changePerperpertiveRdb(int value_);

  void setPointType(PointType const &type);

  void moveObject(int type_, int value_);

 private:
  Ui::MainWindow *ui;

  IControllerInterface *controller_;
  IModelViewer *model_;
  MyWidgetOPenGL *m_myWidget;

  QLabel *m_labelGifTime;

 private:
  void connectsConfiguration();
  void changeRotateSliders();

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
