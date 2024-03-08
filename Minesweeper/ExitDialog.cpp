// @author Dalton Fernandes
// @date Feb 6th 2024
// @description Create ExitDialog class presented at game win/loss 

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>

#include "ExitDialog.h"

// @constructor-name ExitDialog
// @description Create ExitDialog object containing text and buttons dependent on winLossValue
// @parameter winLossValue - Value indiciating if dialog is being displayed for a win or loss
ExitDialog::ExitDialog(int winLossValue, QWidget *parent) : QDialog(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	QLabel *label;

	// Display specific text depending on if dialog is presented at win or loss
	if (winLossValue == 0) {
		label = new QLabel("You have hit a mine and exploded.", this);
	}
	else {
		label = new QLabel("Congrats you have won the game!", this);
	}

	// Create play again and exit game buttons
	QPushButton *restartBtn = new QPushButton("Play Again?", this);
	QPushButton *exitBtn = new QPushButton("Exit", this);

	layout->addWidget(label);
	layout->addWidget(restartBtn);
	layout->addWidget(exitBtn);
	
	// Connect the buttons to functions for their specifc functionality
	connect(restartBtn, &QPushButton::clicked, this, &ExitDialog::restartGame);
	connect(exitBtn, &QPushButton::clicked, this, &ExitDialog::exitGame);
}

// @function-name restartGame
// @description Close dialog window to allow for new game to generate
void ExitDialog::restartGame(){
	this->close();
}

// @function-name exitGame
// @description Close QApplication
void ExitDialog::exitGame() {
	QApplication::exit();
}
