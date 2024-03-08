// @author Dalton Fernandes
// @date Feb 6th 2024
// @description Define the constructor, functions and data members of MainWindow

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <TilePushButton.h>

namespace Ui {
  class MainWindow;
}
 
class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
private slots:
  void onRightClick(int index);
  void onLeftClick(int index);
  void startNewGame();
  void chainOpenTile(int index, const int mines[99]);
private:
  TilePushButton *buttons[480];
  QPushButton *btn;
  int mines[99];
  int opened[480];
  int openedCount;
  int flagged[480];
  int flaggedCount;
  int unknowns[480];
  int unknownCount;
};
#endif // MAINWINDOW_H
