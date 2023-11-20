
#ifndef INCLUDES_MODEL_FACADEMODEL_HPP_
#define INCLUDES_MODEL_FACADEMODEL_HPP_

#include <vector>

#include "../includes/Model/ifacademodel.hpp"
#include "./datamanager.hpp"
#include "./imagecapture.hpp"
#include "./modelviewer.hpp"

namespace s21 {

class FacadeModel : public IFacadeModel {
 public:
  FacadeModel();
  FacadeModel(FacadeModel const &other) = delete;
  FacadeModel &operator=(FacadeModel const &other) = delete;
  virtual ~FacadeModel();

  // -- -- -- --

  /**
   * @brief Attaching an observer.
   *
   * @param observer - (IWidgetOpenglObserver) observer.
   */
  void Attach(IWidgetOpenglObserver *observer) override;

  /**
   * @brief Detach the observer.
   *
   * @param observer - (IWidgetOpenglObserver) observer.
   */
  void Detach(IWidgetOpenglObserver *observer) override;

  /**
   * @brief Method for notifying observers about changes
   *             in the "Model" information.
                 Iterates through the list of observers and calls
                 their UpdateInfo() method.
                 :INTERFACE: IWidgetOpenglObserver
   */
  void NotifyWidgetOpengl() override;

  /**
   * @brief Method for notifying observers about changes
   *             in the "Model" information.
                 Iterates through the list of observers and calls
                 their Update() method.
                 :INTERFACE: IWidgetOpenglObserver
   */
  void NotifyWidgetOpenglInfo() override;

  void Attach(IMainWindowObserver *observer) override;
  void Detach(IMainWindowObserver *observer) override;

  /**
   * @brief Method for notifying observers about changes
   *             in the "Model" information.
                 Iterates through the list of observers and calls
                 their Update() method.
                 :INTERFACE: IWidgetOpenglObserver
   */
  void NotifyMainWindow() override;

  // -- -------------------------------------------- --

  void ChangeBackgroundColor(int const &value) override;
  void ChangePointColor(int const &value) override;
  void ChangeLinesColor(int const &value) override;

  void OpenFile(QString const &filename) override;

  void ChangeLineWidth(double const &value) override;
  void ChangePointSize(int const &value) override;
  void ChangeTypePoint(PointType const &type) override;
  void ChangePerspective(int const &value) override;
  void ChangeLineType(LineType const &type) override;

  void IncremenetScale() override;
  void DecrementScale() override;
  void ChangeScale(int const &value) override;

  DataViewer const &GetDataViewer() const override;

  void MoveRotationSlider(MoveRotationType const &direction,
                          float const &value) override;
  void MoveDirectionSlider(MoveType const &direction,
                           float const &value) override;
  void MoveRotationMouse(MoveRotationType const &direction,
                         float const &value) override;

  void PolygonsClear() override;
  ErrorType GetError() override;

  /**
   * @brief An arary of vertices.
   *         Point: x y z
   *
   * @return - const &vector<Point>
   */
  std::vector<Point> const &PointsArray() override;

  /**
   * @brief A two-dminsional array of polygons.
   *
   * @return const vector<vector<int>>
   */
  std::vector<std::vector<int>> const &Polygons() override;

  // -- -- -- --

  void ResetData() override;

  // -- -- -- --

  /**
   * @brief Take a screnshot in format "JPEG"
   *
   * @param widget - (widget) screen capture.
   */
  void ScreenshotJPEG(QWidget *widget) override;

  /**
   * @brief Take a screnshot in format "BMP"
   *
   * @param widget - (widget) screen capture.
   */
  void ScreenshotBMP(QWidget *widget) override;

  /**
   * @brief Mkae a gif.
   *
   * @param widget - (widget) screen capture.
   */
  void Gif(QWidget *widget) override;

  /**
   * @brief Starting the gif timer.
   *
   * @return - bool
   */
  bool GifTimerIsRun() override;

  // -- -- -- --

  bool SaveData(QString const &path = "") override;
  bool LoadData(QString const &path = "") override;

  // -- -- -- --

 private:
  QList<IWidgetOpenglObserver *> list_widget_opengl_;
  QList<IMainWindowObserver *> list_main_menu_;

  ModelViewer *model_;
  DataManager *data_manager_;
  ImageCapture *image_capture_;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_FACADEMODEL_HPP_
