#ifndef INCLUDES_VIEW_MAINWINDOW_HPP_
#define INCLUDES_VIEW_MAINWINDOW_HPP_

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

  /**
   * @brief Moving the slider by Y.
   *
   * @param value - (int const &) how much to move.
   */
  void ChangeMoveSliderX(int const &value);

  /**
   * @brief Moving the slider by X.
   *
   * @param value - (int const &) how much to move.
   */
  void ChangeMoveSliderY(int const &value);

  /**
   * @brief Moving the slider by Z.
   *
   * @param value - (int const &) how much to move.
   */
  void ChangeMoveSliderZ(int const &value);

  /**
   * @brief Rotate the slider by Y.
   *
   * @param value - (int const &) how much to rotate.
   */
  void ChangeRotateSlidersY(int const &value);

  /**
   * @brief Rotate the slider by Z.
   *
   * @param value - (int const &) how much to rotate.
   */
  void ChangeRotateSlidersZ(int const &value);

  /**
   * @brief Rotate the slider by X.
   *
   * @param value - (int const &) how much to rotate.
   */
  void ChangeRotateSlidersX(int const &value);

  /**
   * @brief Changing the line width.
   *
   * @param width -> (double cost &) How much to change by (width).
   */
  void ChangeLineWidth(double const &width);

  /**
   * @brief Changing the point size.
   *
   * @param value
   */
  void ChangePointSize(int const &value);

  /**
   * @brief Locking slider by rotation.
   *
   * @param is_block - (bool) if true is unlock else block.
   */
  void BlockSlideRotate(bool const &is_block);

  /**
   * @brief Blocking the gif button.
   *
   * @param is_work - (bool) if true is unlock else block.
   */
  void BlockGifButton(bool const &is_work);

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
