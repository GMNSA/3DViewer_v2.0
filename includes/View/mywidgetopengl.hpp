#ifndef MYWIDGETOPENGL_HPP
#define MYWIDGETOPENGL_HPP

#ifdef __MACOS__
#define GL_SILENCE_DEPRECATION
#endif

#include <QObject>
#include <QOpenGLFunctions>
#include <QtOpenGLWidgets>

#define RGB_MIN 1
#define RGB_MAX 255

#include "../Controller/icontrollerinterface.hpp"
#include "../Model/ifacademodel.hpp"
#include "./iwidgetopenglobserver.hpp"

namespace s21 {

typedef enum e_typeDraw {
  TYPE_LINES = 0,
  TYPE_POINTS,
  END_TYPE_DRAW
} e_typeDraw;

// -------------------------------------------------------

// -------------------------------------------------

class MyWidgetOPenGL : public QOpenGLWidget,
                       protected QOpenGLFunctions,
                       public IWidgetOpenglObserver {
  Q_OBJECT
  Q_INTERFACES(s21::IWidgetOpenglObserver)

 signals:
  // void on_moveChange(float value_);
  void on_changeRotate();
  void on_scaleStep();
  void on_changeColorGifTime(int const &is_black);
  void on_changePerperpertiveRdb(int value);

 public:
  explicit MyWidgetOPenGL(IControllerInterface *controller, IFacadeModel *model,
                          QWidget *parent = nullptr);
  MyWidgetOPenGL(MyWidgetOPenGL const &other_) = delete;
  MyWidgetOPenGL(MyWidgetOPenGL &&other_) = delete;
  void operator=(MyWidgetOPenGL const &other_) = delete;
  void operator=(MyWidgetOPenGL &&other_) = delete;
  virtual ~MyWidgetOPenGL();

  /* **** ***** **** */

  void ChangeColorFileInfo(int const &value);

  void turnOnMouse();
  void turnOffMouse();

  QString scaleString();

  void moveX(float value_);
  void moveY(float value_);
  void moveZ(float value_);

  void Update() override;
  void UpdateInfo() override;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  // QWidget interface
  void wheelEvent(QWheelEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

  // QObject interface
  bool eventFilter(QObject *watched, QEvent *event) override;

 private:
  int updateData();
  void updateInfoObject();

  // void ChangeRotate();
  void updatePerspective();

  void drawObjects(e_typeDraw type_);
  void drawInfo();
  void clearInfo();
  void drawSquare();

 private:
  IControllerInterface *controller_;
  IFacadeModel *model_;

  QString m_fileNameObject;

  int m_countScale;

  bool initialized_;
  QPoint mouse_position_;
  double m_sizePerspective;

  QLabel *label_name_;
  QLabel *label_vertes_;
  QLabel *label_polygons_;
  QHBoxLayout *m_layoutH;

  bool m_isMouse;
  QColor m_tmpColor;

  // ModelViewer *modelviewer_;
  // Point m_points;
  // matrix_poligon m_polygons;
};

}  // namespace s21

#endif  // MYWIDGETOPENGL_HPP
