#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>

#include "gamewindow.h"
#include "TetrisPiece.h"
#include "endgamedialog.h"

/**
 * @authors Saif Abbas, Dalton Fernandes, Josiah Stanley, Kiet Tran
 * @class GameWindow::GameWindow Configures, Renders and Updates game window with active game area
 *
 * Configures the game by creating an array of tetris pieces and a game speed time.
 * Renders tetris pieces using the pieceCount to limit the amount of pieces renders to actual number of pieces displayed in the active game area.
 * Updates the tetris pieces positions based on user key input and updates the next, score and level side areas as values change with gameplay.
 */

/**
 * @brief GameWindow::GameWindow Game window constructor
 *
 * Constructs game window by initalizing variables, game speed timer and, array of random tetris pieces.
 * Additionally, calls displayUI used to begin drawing pieces, and populating next, score and level side areas.
 *
 * @param parent Parent widget, always set as mainwindow
 */
GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent), isPaused(false)
{
    clearedLinesCount = 0;
    pieceCount = 0;
    score = 0;
    gameOver = false;
    initRandom();
    GameWindow::displayUI(this);
    // Initalize gamespeed timer
    gameSpeed = new QTimer(this);
    connect(gameSpeed, SIGNAL(timeout()), this, SLOT(movePieceDown()));
    gameSpeed->start(1000);

    // Initalize array of tetris pieces used in game
    initRandom();
    for (int i = 0; i < 100; i++) {
        pieces[i] = createRandomPiece();
    }
}

/**
 * @brief GameWindow::displayUI Initates displaying game window UI
 *
 * Configures the background of the game window UI and begins painting pieces and populating side areas with next piece and texts
 *
 * @param parent Parent widget object pointing to game window
 */
void GameWindow::displayUI(QWidget *parent)
{
    // Display main menu window background
    parent->resize(1280,720);
    QLabel *background = new QLabel(parent);
    QPixmap pix(":/imgs/gameBackground.png");
    background->setGeometry(0,0,1280,720);
    background->setPixmap(pix.scaled(1280,720));

    // Begin painting pieces
    update();
    repaint();
}

/**
 * @brief GameWindow::gameOverCheck Check if user loses game
 *
 * Checks if user loses game and launches end game dialog if true.
 * Lose condition is when a block stops outside the game area
 */
void GameWindow::gameOverCheck() {
    if (!gameOver) {
        for (const TetrisPiece &piece : pieces) {
            for (const Block &block : piece.blocks) {
                if (block.x == 0 && block.y == -1) {
                    gameOver = true;
                    EndGameDialog *dialog = new EndGameDialog(this);
                    if(dialog->exec() == QDialog::Accepted) {
                        this->close();
                    }
                    return;
                }
            }
        }
    }
}

/**
 * @brief GameWindow::paintEvent Painter connected to repaint()/update() calls
 *
 * Updates the drawn pieces, level, score and next piece upon repaint and update calls throughout the class.
 * Additionally, temporaily stops paint updates when isPaused is true
 */
void GameWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    // Create first piece
    if (pieceCount == 0) {
        pieces[0] = createRandomPiece();
        currentPiece = 0;
        pieceCount++;
    }

    // Update drawn pieces, level and score
    drawPieces(painter);
    drawLevelAndScore(painter);
    drawNextPiece(painter);

    // Draw pause message
    if (isPaused) {
        QFont font("Arial", 24, QFont::Bold);
        painter.setFont(font);
        painter.drawText(rect(), Qt::AlignCenter, "PAUSED");
    }
}

/**
 * @brief GameWindow::movePieceDown Performs move piece down action connected to down key and gameSpeed timer
 *
 * Updates the position of the current dropping pieces connected to the game speed timer.
 * Also updates the position of the current dropping piece connect to the down key.
 * Additionally, checks for collisions and upon collisions stops auto down movement of current piece and sets next piece as current piece
 */
void GameWindow::movePieceDown() {
    if (!isPaused) {
        bool canMoveDown = true;

        // Check for collisions
        for (const Block &block : pieces[currentPiece].blocks) {
            int newY = block.y + 1;

            // Check if the block would collide with the bottom

            if (newY >= 15) {
                canMoveDown = false;
                break;
            }

            // Check if the block would collide with an existing placed blocks
            for (int i = 0; i < currentPiece; i++) {
                for (const Block &otherBlock : pieces[i].blocks) {
                    if (block.x == otherBlock.x && newY == otherBlock.y) {
                        canMoveDown = false;
                        break;
                    }
                }
                if (!canMoveDown){
                    gameOverCheck();
                    break;
                }
            }
        }

        // If no collisions were detected, move the piece down
        if (canMoveDown) {
            for (Block &block : pieces[currentPiece].blocks) {
                block.setY(block.y + 1);
            }
            update();
            repaint();
        }
        // Otherwise, generate a new piece and, set the new piece as the current piece
        else{
            clearLineCheck();

            if(currentPiece==pieceCount-1){
                //initRandom();
                //pieces[pieceCount] = createRandomPiece();
                for (Block &block : pieces[pieceCount].blocks) {
                    block.setY(block.y - 2);
                }
                pieceCount++;
                currentPiece++;
            }
        }
    }
}

/**
 * @brief GameWindow::movePieceRight Performs move right action
 *
 * Updates current piece's x coordinate on right key press and draws the current piece.
 * Checks for collisions before moving current piece
 */
void GameWindow::movePieceRight()
{
    bool canMoveRight = true;

    // Check for collisions
    for (const Block &block : pieces[currentPiece].blocks) {
        int newX = block.x - 1;

        // Check if the block would collide with the bottom
        if (newX < -5) {
            canMoveRight = false;
            break;
        }

        // Check if the block would collide with an existing placed blocks
        for (int i = 0; i < currentPiece; i++) {
            for (const Block &otherBlock : pieces[i].blocks) {
                if (newX == otherBlock.x && block.y == otherBlock.y) {
                    canMoveRight = false;
                    break;
                }
            }
            if (!canMoveRight) break;
        }
    }

    // If no collisions were detected, move the piece right
    if (canMoveRight) {
        for (Block &block : pieces[currentPiece].blocks) {
            block.setX(block.x - 1);
        }
        update();
    }
}

/**
 * @brief GameWindow::movePieceLeft Performs move left action
 *
 * Updates current piece's x coordinate on left key press and draws the current piece.
 * Checks for collisions before moving current piece
 */
void GameWindow::movePieceLeft()
{
    bool canMoveLeft = true;

    // Check for collisions
    for (const Block &block : pieces[currentPiece].blocks) {
        int newX = block.x + 1;

        // Check if the block would collide with the bottom
        if (newX > 6) {
            canMoveLeft = false;
            break;
        }

        // Check if the block would collide with an existing placed blocks
        for (int i = 0; i < currentPiece; i++) {
            for (const Block &otherBlock : pieces[i].blocks) {
                if (newX == otherBlock.x && block.y == otherBlock.y) {
                    canMoveLeft = false;
                    break;
                }
            }
            if (!canMoveLeft) break;
        }
    }

    // If no collisions were detected, move the piece left
    if (canMoveLeft) {
        for (Block &block : pieces[currentPiece].blocks) {
            block.setX(block.x + 1);
            update();
        }
    }
}

/**
 * @brief GameWindow::rotatePiece Perform rotate piece action
 *
 * Computes current piece's rotated X and Y values for each block relative to pivot coordinate associated with the 'middle' block of most pieces
 */
void GameWindow::rotatePiece()
{
    if (pieces[currentPiece].shape == 'O') return;

    int pivotIndex = 1;
    int pivotX = pieces[currentPiece].blocks[pivotIndex].x;
    int pivotY = pieces[currentPiece].blocks[pivotIndex].y;

    // Perform rotation
    for (Block &block : pieces[currentPiece].blocks) {
        int relativeX = block.x - pivotX;
        int relativeY = block.y - pivotY;

        // Clockwise rotation
        int rotatedX = relativeY;
        int rotatedY = -relativeX;

        block.x = rotatedX + pivotX;
        block.y = rotatedY + pivotY;
    }
}

/**
 * @brief GameWindow::keyPressEvent Handles key presses
 *
 * Actively fetches key presses events and calls associated movement method.
 * Only accepts key press events aside from escape key, when game is not paused
 *
 * @param event Key press event
 */
void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        isPaused = !isPaused;
        update();
    } else if (!isPaused) {
        // Handle other key events only if the game is not paused
        if (event->key() == Qt::Key_Down) {
            movePieceDown();
        } else if (event->key() == Qt::Key_Right) {
            movePieceRight();
        } else if (event->key() == Qt::Key_Left) {
            movePieceLeft();
        } else if (event->key() == Qt::Key_R) {
            rotatePiece();
        } else {
            QWidget::keyPressEvent(event);
        }
    }
}

/**
 * @brief GameWindow::clearLineCheck Checks for and clears complete lines
 *
 * Performs check to see if a row in the game area is filled with blocks from left to right.
 * When a row in the game area is considered complete is is added the vector of completeLine row indexes and the rows are cleared.
 * Blocks above row which area cleared and then dropped down according to the number of complete lines.
 */
void GameWindow::clearLineCheck() {
    int blocksWidth = 12;
    std::vector<int> completeLines;

    // Count number of blocks placed in each row in the game area
    for (int y = 0; y < 16; ++y) {
        int blockCount = 0;
        for (const TetrisPiece &piece : pieces) {
            for (const Block &block : piece.blocks) {
                if (block.y == y) {
                    ++blockCount;
                }
            }
        }

        // If the row is complete add it to completeLines
        if (blockCount == blocksWidth) {
            completeLines.push_back(y);
            clearedLinesCount++;
        }
    }

    // Increment score according to number of lines being cleared at same time
    if (completeLines.size() == 1) {
        score += 100;
    }
    else if (completeLines.size() == 2) {
        score += 300;
    }
    else if (completeLines.size() == 3) {
        score += 500;
    }
    else if (completeLines.size() == 4) {
        score += 1000;
    }

    // Clear complete lines
    for (int line : completeLines) {
        // Delete blocks in the line
        for (TetrisPiece &piece : pieces) {
            auto &blocks = piece.blocks;
            blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [line](const Block& block) {
                             return block.y == line;
                         }), blocks.end());
        }

        // Move down blocks above the cleared line
        for (TetrisPiece &piece : pieces) {
            for (Block &block : piece.blocks) {
                if (block.y < line) {
                    block.setY(block.y + 1);
                }
            }
        }
    }

    if (!completeLines.empty()) {
        update();
        repaint();
    }
}

/**
 * @brief GameWindow::drawLevelAndScore Draws and updates level and score text
 *
 * Sets the font object used by the painter to draw text.
 * Configures the position of the level and score text and performs the drawing of these texts.
 * Additonally, updates the game speed interval based on the computed level value
 *
 * @param painter Parent painter object of game window
 */
void GameWindow::drawLevelAndScore(QPainter &painter) {
    QFont font("Helvetica", 20);
    painter.setFont(font);
    painter.setPen(Qt::magenta);
    int level = (clearedLinesCount / 5) + 1;
    QPoint levelNumberPos(985, 585);
    QPoint scoreNumberPos(985, 672);
    painter.drawText(levelNumberPos, QString::number(level));
    painter.drawText(scoreNumberPos, QString::number(score));

    // Update gamespeed interval
    if (level < 20) {
        int interval = 1050 - 50 * level;
        gameSpeed->setInterval(interval);
    }
}

/**
 * @brief GameWindow::drawNextPiece Draw next piece in next window
 *
 * Configure position of next piece to be set in next window and draw each block
 *
 * @param painter Parent painter object of game window
 */
void GameWindow::drawNextPiece(QPainter &painter) {
    painter.setRenderHint(QPainter::Antialiasing);
    int blockSize = 40;
    for (const Block &block : pieces[currentPiece+1].blocks) {
        int blockX = block.x * blockSize - 475;
        int blockY = block.y * blockSize + 95 - clearedLinesCount*40;
        // Special case: Adjust I Piece to be centered
        if (pieces[currentPiece + 1].shape == 'I') {
            blockX -= 20;
            blockY += 15;
        }
        blockX = (1280 / 2) - blockX;
        QRect blockRect(blockX, blockY, blockSize, blockSize);
        // Depending on the shape associate the drawn block with a color
        switch (pieces[currentPiece+1].shape) {
        case 'I': painter.fillRect(blockRect, Qt::cyan); break;
        case 'J': painter.fillRect(blockRect, Qt::darkBlue); break;
        case 'L': painter.fillRect(blockRect, Qt::darkYellow); break;
        case 'O': painter.fillRect(blockRect, Qt::yellow); break;
        case 'S': painter.fillRect(blockRect, Qt::green); break;
        case 'T': painter.fillRect(blockRect, Qt::magenta); break;
        case 'Z': painter.fillRect(blockRect, Qt::red); break;
        }
        painter.drawRect(blockRect);
    }
}

/**
 * @brief GameWindow::drawPieces Draw all active tetris pieces
 *
 * Draw each block of active tetris pieces using the pieceCount to limit to previous and current pieces being drawn.
 *
 * @param painter Parent painter object of game window
 */
void GameWindow::drawPieces(QPainter &painter) {
    painter.setRenderHint(QPainter::Antialiasing);
    int blockSize = 40;
    // For each existing piece on the game window
    for (int i = 0; i < pieceCount; i++) {
        const TetrisPiece piece  = pieces[i];
        // Update/redraw the four blocks of every piece
        for (const Block &block : piece.blocks) {
            int blockX = block.x * blockSize;
            int blockY = block.y * blockSize + 80;
            blockX = (1280 / 2) - blockX;
            QRect blockRect(blockX, blockY, blockSize, blockSize);
            // Depending on the shape associate the drawn block with a color
            switch (piece.shape) {
            case 'I': painter.fillRect(blockRect, Qt::cyan); break;
            case 'J': painter.fillRect(blockRect, Qt::darkBlue); break;
            case 'L': painter.fillRect(blockRect, Qt::darkYellow); break;
            case 'O': painter.fillRect(blockRect, Qt::yellow); break;
            case 'S': painter.fillRect(blockRect, Qt::green); break;
            case 'T': painter.fillRect(blockRect, Qt::magenta); break;
            case 'Z': painter.fillRect(blockRect, Qt::red); break;
            }
            painter.drawRect(blockRect);
        }
    }
}
