#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void displayUI(QWidget *parent);
    void start();
private:
    QPushButton *startBtn;
    QStringList usernames;
    QStringList scores;
};
#endif // MAINWINDOW_H
