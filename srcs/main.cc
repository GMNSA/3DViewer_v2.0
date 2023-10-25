#include <signal.h>

#include <QApplication>

#include "../includes/Controller/controller.hpp"
#include "../includes/Model/modelviewer.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::ModelViewer model = s21::ModelViewer();
  s21::Controller controller(&model);

  return a.exec();
}
