#ifndef TETRIS
#define TETRIS

#include <vector>

class Block {
public:
    int x, y;
    Block(int x, int y);
    void setX(int x);
    void setY(int y);
};

class TetrisPiece {
public:
    std::vector<Block> blocks;
    char shape;
    TetrisPiece();
    TetrisPiece(const std::vector<Block>& blocks, char shape);
};

void initRandom();
TetrisPiece createRandomPiece();

#endif // TETRISPIECE_H
