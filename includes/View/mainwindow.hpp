#ifndef INCLUDES_VIEW_MAINWINDOW_HPP_
#define INCLUDES_VIEW_MAINWINDOW_HPP_

// #include <stdbool.h>

#include <QLabel>
#include <QMainWindow>

#include "../Controller/icontrollerinterface.hpp"
#include "../lib/QtGifImage/includes/gifcreator.h"
#include "./mywidgetopengl.hpp"

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(IControllerInterface *controller, IModelViewer *model,
             QWidget *parent = nullptr);
  ~MainWindow();

 signals:

 private slots:
  void openFileDialog();

  void rotateX(int value_);
  void rotateY(int value_);
  void rotateZ(int value_);

  void screenshotJPEG();
  void screenshotBMP();
  void doGif();
  void startGif();

 private slots:
  void closeApp();

  void lineScaleChange(QString value_);

  void changeBackgroundColor(int value_);
  void changeColorLines(int value_);
  void changeColorPoints(int value_);

  void changeWidthLines(int value_);
  void changeSizePoint(int value_);
  void changePerperpertiveRdb(int value_);

  void setPointType(int value_);

  void moveObject(int type_, int value_);

 private:
  Ui::MainWindow *ui;
  IControllerInterface *controller_;
  IModelViewer *model_;

  MyWidgetOPenGL *m_myWidget;

  bool m_isPositiveHorizontal;
  bool m_isPositiveVertical;
  GifCreator *m_gif;
  QTimer *m_timerGif;
  QLabel *m_labelGifTime;

  double m_startTime;
  int m_endTime;
  int m_countFrame = 0;
  int m_frameNum = 0;

 private:
  void connectsConfiguration();
  void defaultConfig();
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

  void screenshot(int isJpeg = 1);
  void changeColorGifTime(int isBlack_);
};

}  // namespace s21

#endif  // INCLUDES_VIEW_MAINWINDOW_HPP_
