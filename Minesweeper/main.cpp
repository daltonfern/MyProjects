// @author Dalton Fernandes
// @date Feb 26th 2024
// @description Start a new QApplication of MainWindow

#include <QApplication>

#include "mainwindow.h"

// @description Launch a new QApplication using MainWindow
// @parameters Launch arguments
int main(int argc, char *argv[]) 
{
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.resize(600,320);
  mainWindow.show();
  return app.exec();
}
