// @author Dalton Fernandes
// @date Feb 6th 2024
// @description Define ExitDialog's constructor and functions

#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <QDialog>

class ExitDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ExitDialog(int winLossValue, QWidget *parent = 0);

public slots:
	void restartGame();
	void exitGame();
};

#endif
