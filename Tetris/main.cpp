#include <QApplication>

#include "mainwindow.h"

/**
 * @author Dalton Fernandes
 * @brief main Main startup point of application
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit status of application
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1280,720);
    w.show();
    return a.exec();
}
