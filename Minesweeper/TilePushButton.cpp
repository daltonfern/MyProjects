// @author Dalton Fernandes
// @date Feb 6th 2024
// @description Create TilePushButton class from QPushButton allowing for both left and right click signals

#include "TilePushButton.h"

// @constructor-name TilePushButton
TilePushButton::TilePushButton(QWidget *parent) :
	QPushButton(parent) {}

// @function-name mouseReleaseEvent
// @description Emit a leftClick or rightClick signal based on a given QMouseEvent object
// @parameter *e - Pointer to mouse event
void TilePushButton::mouseReleaseEvent(QMouseEvent *e)
{
	// Emit left or right click depending on button pressed
	if(e->button() == Qt::LeftButton)
	{
		emit leftClick();
	}
	else if(e->button() == Qt::RightButton) 
	{
		emit rightClick();
	}	
	QPushButton::mouseReleaseEvent(e);
}
