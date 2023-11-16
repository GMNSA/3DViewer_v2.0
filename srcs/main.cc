#include <signal.h>

#include <QApplication>

#include "../includes/Controller/controller.hpp"
#include "../includes/Model/facademodel.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::FacadeModel model = s21::FacadeModel();
  s21::Controller controller(&model);

  return a.exec();
}
