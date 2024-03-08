// @author Dalton Fernandes
// @date Feb 6th 2024
// @description Generate a new minesweeper gameboard and handle gameplay input on main window

#include <iostream>
#include <QWidget>
#include <QGridLayout>

#include "mainwindow.h"
#include "TilePushButton.h"
#include "ExitDialog.h"

// @constructor-name MainWindow
// @description Create the minesweeper gameboard made up of a QGridLayout of QPushButtons and connect these buttons to their respective methods for gameplay functionality
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  auto gridLayout = new QGridLayout(this);
  gridLayout->setSpacing(0);
  int index = 0;
  openedCount = 0;
  flaggedCount = 0;
  unknownCount = 0;
  
  // Select ninty-nine random tiles to contain mines
  for (int i = 0; i < 99; i++) {
	mines[i] = (rand() % 480);
  }
	
  // Create a 30x16 QGridLayout of QPushButtons
  for (int row = 0; row < 16; ++row) {
	for (int col = 0; col < 30; ++col) {
		buttons[index] = new TilePushButton(this);
		buttons[index]->setGeometry(QRect(QPoint(col*20, row*20), QSize(20, 20)));
		gridLayout->addWidget(buttons[index], row, col);

		// Connect the right and left push button functionality for each button in the grid
		connect(buttons[index], &TilePushButton::rightClick, this,
				[=]{
					MainWindow::onRightClick(index);
				});
		connect(buttons[index], &TilePushButton::leftClick, this,
				[=]{
					MainWindow::onLeftClick(index);
				});
		
		index = index + 1;
	}
  }
}

// @function-name onRightClick
// @description Upon right clicking mark or unmark a tile with a flag or ? if it is not open
// @parameter Index of tile to be marked/unmarked
void MainWindow::onRightClick(int index)
{
	bool open = false;
	bool flag = false;
	bool unknown = false;

	QPushButton *btn = qobject_cast<TilePushButton *>(sender());
	
	// Check if opened
	for (int i = 0; i < openedCount+1; i++) {
		if (opened[i] == index) {
			open = true;
		}
	}

	// Check if marked with flag
	for (int i = 0; i < flaggedCount+1; i++) {
		if (flagged[i] == index) {
			flag = true;
		}
	}

	// Check if marked with ?
	for (int i = 0; i < unknownCount+1; i++) {
		if (unknowns[i] == index) {
			unknown = true;
		}
	}

	// Remove ?
	if (unknown == true) {
		btn->setText(" ");
		for (int i = 0; i < unknownCount+1; i++) {
			if (unknowns[i] == index) {
				unknowns[i] = 500;
				unknownCount--;
			}
		}
		return;
	}

	// Set ? from flag
	if (flag == true) {
		btn->setIcon(QIcon());
		btn->setText("?");
		unknowns[unknownCount] = index;
		unknownCount++;
		for (int i = 0; i < flaggedCount+1; i++) {
			if (flagged[i] == index) {
				flagged[i] = 500;
				flaggedCount--;
			}
		}
		return;
	}

	// Set flagged if not opened
	if (open == false) {
		btn->setIcon(QIcon("imgs/mine_flag.png"));
		btn->setIconSize(QSize(20,20));
		flagged[flaggedCount] = index;
		flaggedCount++;
	}
}

// @function-name onLeftClick
// @description Upon left clicking open a tile revealing a hint, a chain of tile openings, or a mine
// @parameter Index of tile to be opened
void MainWindow::onLeftClick(int index)
{
	int adjMineCount = 0;
	char strMineCount[1000];
	opened[openedCount] = index;
	openedCount++;
	
	QPushButton *btn = qobject_cast<TilePushButton *>(sender());
	
	// Check if the left-clicked tile contains a mine
	for (int i = 0; i < 99; i++) {
		if (mines[i] == index) {
			// Set tile image to exploded mine
			btn->setIcon(QIcon("imgs/bomb_explode.png"));
			btn->setIconSize(QSize(20,20));
			// Launch lose procedure
			ExitDialog *exitDialog = new ExitDialog(0);
			exitDialog->setWindowTitle("Uh Oh!");
			exitDialog->exec();
			// If lose dialog instance ends, user has chosen to play again
			MainWindow::startNewGame();
			return;
		}
	}

	// Count the number of mines under tiles adjacent to left clicked tile
	for (int i = 0; i < 99; i++) {
		if (mines[i] == index+1 || mines[i] == index-1 || mines[i] == index+29 || mines[i] == index+30 || mines[i] == index+31 || mines[i] == index-30 || mines[i] == index-29 || mines[i] == index-31) {
			adjMineCount++;
		}
	}

	// If tile's adjacent tiles contain mine(s), give a hint
	if (adjMineCount != 0) {
		sprintf(strMineCount, "%d", adjMineCount);
		btn->setIcon(QIcon());
		btn->setText(strMineCount);
	}

	// If the tile is not adjacent to a mine, recursively open adjacent tiles which also have no adjacent mines
	else {
		MainWindow::chainOpenTile(index, mines);
	}

	// If there are only 99 unopened tiles, the user has opened all non-mine tiles
	if (openedCount == 381) {
		// Launch win procedure
		ExitDialog *exitDialog = new ExitDialog(1);
		exitDialog->setWindowTitle("Woo Hoo!");
		exitDialog->exec();
		// If win dialog instance ends, user has chosen to play again
		MainWindow::startNewGame();
	}
}

// @function-name startNewGame
// @description Reset data items, arrays and tiles for a new game
void MainWindow::startNewGame() {
	// Reset tiles to original state
	for (int i = 0; i < 480; i++) {
		buttons[i]->setIcon(QIcon());
		buttons[i]->setText(" ");
		buttons[i]->setVisible(true);
	}
	
	// Clear all opened/marked tile arrays by setting to a tile index outside the gameboard's bounds 
	for (int i = 0; i < openedCount+1; i++) {
		opened[i] = 500;
	}
	for (int i = 0; i < flaggedCount+1; i++) {
		flagged[i] = 500;
	}
	for (int i = 0; i < unknownCount+1; i++) {
		unknowns[i] = 500;
	}

	// Reset opened/marked tile counters
	openedCount = 0;
	flaggedCount = 0;
	unknownCount = 0;
	
	// Select 99 new tiles for mines
	for (int i = 0; i < 99; i++) {
		mines[i] = (rand() % 480);
	}
}

// @function-name chainOpenTile
// @description Recursively open a tile's adjacent tiles if they are not adjacent to a mine
// @parameter index - Index of tile to be recursively opened, mines[99] - Array of mine indexes
void MainWindow::chainOpenTile(int index, const int mines[99]) {
	int adjacentIndexes[8] = {index+1, index-1, index+29, index+30, index+31, index-31, index-30, index-29};
	int currentIndex = 0;
	int adjMineCount = 0;
	bool noAdjMines = true;

	// Inputted index is a tile without adjacent mines, therefore set blank
	buttons[index]->setVisible(false);
	
	// If index tile is a mine, do not open or check adjacents
	for (int i = 0; i < 99; i++) {
		if (index == mines[i]) {
			return;
		}
	}

	// Check if the tiles adjacent to index tile should also have no adjacent mines
	for (int i = 0; i < 8; i++) {
		currentIndex = adjacentIndexes[i];
		noAdjMines = true;
		adjMineCount = 0;

		// To compensate for the tile array being 1-Dimensional, skip checking tiles that are on the otherside of the gameboard
		if ( (index%30==0 && (currentIndex+1)%30==0) || ((index+1)%30==0 && currentIndex%30==0)) {
			continue;
		}
		
		// Count the current adjacent tile's adjacent mines, if it is in the bounds of the gameboard
		if (currentIndex < 480 && currentIndex >= 0) {
			for (int j = 0; j < 99; j++) {
				if (mines[j] == currentIndex+1 || mines[j] == currentIndex-1 || mines[j] == currentIndex+29 || mines[j] == currentIndex+30 || mines[j] == currentIndex+31 || mines[j] == currentIndex-31 || mines[j] == currentIndex-30 || mines[j] == currentIndex-29) {
					// Skip checking tiles that are on the otherside of the gameboard due to tile array being 1-Dimensional
					if ((currentIndex+1)%30!=0 || (currentIndex%30!=0)) {	
						adjMineCount++;
						noAdjMines = false;
					}
					else {
						continue;
					}
				}
			}

			// If tile has no adjacent mines	
			if (noAdjMines == true) {
				bool alreadyOpen = false;
			
				// Check if tile is already open
				for (int k = 0; k < openedCount+1; k++) {
					if (opened[k] == currentIndex) {
						alreadyOpen = true;
					}
				}
			
				// If not already open, open and recursively open tile's adjacent tiles where possible
				if (alreadyOpen == false) {
					opened[openedCount+1] = currentIndex;
					openedCount++;
					MainWindow::chainOpenTile(currentIndex, mines);
				}
			}

			// If the tile has some adjacent mines
			else {
				// Open the tile
				opened[openedCount+1] = currentIndex;
				openedCount++;
				// Convert the adjacent mine count and give a hint
				char str[1000];
				sprintf(str, "%d", adjMineCount);
				buttons[currentIndex]->setIcon(QIcon());
				buttons[currentIndex]->setText(str);
			}
		}
	}
}
