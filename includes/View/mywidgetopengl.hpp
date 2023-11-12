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

 public:
  explicit MyWidgetOPenGL(IControllerInterface *controller, IFacadeModel *model,
                          QWidget *parent = nullptr);
  MyWidgetOPenGL(MyWidgetOPenGL const &other) = delete;
  MyWidgetOPenGL(MyWidgetOPenGL &&other) = delete;
  void operator=(MyWidgetOPenGL const &other) = delete;
  void operator=(MyWidgetOPenGL &&other) = delete;
  virtual ~MyWidgetOPenGL();

  /* **** ***** **** */

  void ChangeColorFileInfo(int const &value);

  void TurnOnMouse();
  void TurnOffMouse();

  void MoveX(float value);
  void MoveY(float value);
  void MoveZ(float value);

  void Update() override;
  void UpdateInfo() override;

 protected:  // -- override --
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
  void UpdateInfoObject();

  // void ChangeRotate();
  void UpdatePerspective();

  void DrawObjects(e_typeDraw const &type_);
  void DrawInfo();
  void ClearInfo();
  void DrawSquare();

 private:
  IControllerInterface *controller_;
  IFacadeModel *model_;

  bool initialized_;
  QPoint mouse_position_;

  QLabel *label_name_;
  QLabel *label_vertes_;
  QLabel *label_polygons_;
  QLabel *label_gif_time_;
  QHBoxLayout *m_layoutH;

  bool is_mouse_;
  QColor tmp_color_;
};

}  // namespace s21

#endif  // MYWIDGETOPENGL_HPP
