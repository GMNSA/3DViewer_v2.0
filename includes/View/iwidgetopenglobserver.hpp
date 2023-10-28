#ifndef INCLUDES_VIEW_IWIDGETOPENGLOBSERVER_HPP_
#define INCLUDES_VIEW_IWIDGETOPENGLOBSERVER_HPP_

#include <QtPlugin>

namespace s21 {

class IWidgetOpenglObserver {
 public:
  virtual ~IWidgetOpenglObserver() {}

  virtual void Update() = 0;
  virtual void UpdateInfo() = 0;
};

}  // namespace s21

Q_DECLARE_INTERFACE(s21::IWidgetOpenglObserver, "s21_IWidgetOpenglObserver");

#endif  // INCLUDES_VIEW_IWIDGETOPENGLOBSERVER_HPP_
