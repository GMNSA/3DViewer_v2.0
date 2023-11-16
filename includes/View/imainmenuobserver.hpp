#ifndef INCLUDES_VIEW_IMAINWINDOW_HPP_
#define INCLUDES_VIEW_IMAINWINDOW_HPP_

#include <QtPlugin>

namespace s21 {

class IMainWindowObserver {
 public:
  virtual ~IMainWindowObserver() {}

  virtual void Update() = 0;

 private:
};

}  // namespace s21

Q_DECLARE_INTERFACE(s21::IMainWindowObserver, "s21_IMainWindowObserver");

#endif  // INCLUDES_VIEW_IMAINWINDOW_HPP_
