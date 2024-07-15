#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QTimer>

#include "TetrisPiece.h"

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    void displayUI(QWidget *parent);
    void drawPieces(QPainter &painter);
    void drawLevelAndScore(QPainter &painter);
    void drawNextPiece(QPainter &painter);

public slots:
    void movePieceDown();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void movePieceRight();
    void movePieceLeft();
    void rotatePiece();
    void clearLineCheck();
    void gameOverCheck();

private:
    QTimer *gameSpeed;
    TetrisPiece pieces[100];
    int pieceCount;
    int currentPiece;
    int clearedLinesCount;
    int score;
    bool gameOver;
    bool isPaused;
};

#endif // GAMEWINDOW_H
