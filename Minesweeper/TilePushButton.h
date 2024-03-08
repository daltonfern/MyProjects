// @author Dalton Fernandes
// @date Feb 6th 2024
// @description Define TilePushButton's constructor, function and singals

#ifndef TILEPUSHBUTTON_H
#define TILEPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class TilePushButton : public QPushButton
{
	Q_OBJECT

public:
	explicit TilePushButton(QWidget *parent = 0);

private slots:
	void mouseReleaseEvent(QMouseEvent *e);

signals:
	void leftClick();
	void rightClick();
};

#endif
