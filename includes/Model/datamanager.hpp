#ifndef INCLUDES_MODEL_DATAMANAGER_HPP_
#define INCLUDES_MODEL_DATAMANAGER_HPP_

#include "./customtypes.hpp"

namespace s21 {
class DataManager {
 public:
  DataManager();
  virtual ~DataManager();
  DataManager(DataManager const &other) = delete;
  DataManager &operator=(DataManager const &other) = delete;

  /**
   * @brief Saving data to a file by (path).
   *
   * @param path -> path to file.
   * @param data -> data which we will be write. (DataViewer)
   */
  void SaveData(QString const &path, DataViewer const &data);

  /**
   * @brief Loading data from a file by (path).
   *
   * @param path -> path to file.
   *
   * @return -> (DataViewer)
   */
  DataViewer LoadData(QString const &path);

  bool get_is_valid();

 private:
  bool is_valid_;
  QString default_path_;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_DATAMANAGER_HPP_
