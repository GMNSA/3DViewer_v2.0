#ifndef INCLUDES_VIEW_IWIDGETOPENGLOBSERVED_HPP_
#define INCLUDES_VIEW_IWIDGETOPENGLOBSERVED_HPP_

#include <QtPlugin>

namespace s21 {

class IWidgetOpenglObserved {
 public:
  virtual ~IWidgetOpenglObserved() {}

  virtual void UpdateWidgetOpengGl() = 0;
};

}  // namespace s21

Q_DECLARE_INTERFACE(s21::IWidgetOpenglObserved, "s21_IWidgetOpenglObserved");

#endif  // INCLUDES_VIEW_IWIDGETOPENGLOBSERVED_HPP_
