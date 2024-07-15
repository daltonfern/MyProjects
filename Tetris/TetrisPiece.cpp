#include <vector>
#include <cstdlib>
#include <ctime>

#include <TetrisPiece.h>

/**
 * @author Saif Abbas
 * @class TetrisPiece Constructs the block object and TetrisPiece
 *
 * Constructs the block object and TetrisPiece object made up of four blocks and one charecter denoting the piece shape
 */

/**
 * @brief Block::Block Constructs block object with x and y coordinates
 * @param x Block x coordinate
 * @param y Block y coordinate
 */
Block::Block(int x, int y) : x(x), y(y) {}

/**
 * @brief Block::setX Block X Value Setter
 * @param x X value to be set
 */
void Block::setX(int x){
    this->x = x;
}

/**
 * @brief Block::setY Block Y Value Setter
 * @param y Y value to be set
 */
void Block::setY(int y){
    this->y = y;
}

/**
 * @brief TetrisPiece::TetrisPiece Deafult Constructor
 *
 * Default tetris piece object used for default initalization of array of tetris pieces
 *
 */
TetrisPiece::TetrisPiece() : shape(' ') {}

/**
 * @brief TetrisPiece::TetrisPiece Parameterized Constructor
 *
 * Real tetris piece object containing 4 blocks and a shape attribute
 *
 * @param blocks vector of four blocks which form one piece
 * @param shape Charecter indicating shape of piece
 */
TetrisPiece::TetrisPiece(const std::vector<Block>& blocks, char shape) : blocks(blocks), shape(shape) {}

/**
 * @brief initRandom Initalize random number generator
 */
void initRandom() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

/**
 * @brief createRandomPiece Creates one random tetris piece
 *
 * Generates random TetrisPiece object positioning the four blocks and configuring the shape attribute
 *
 * @return random shape TetrisPiece object
 */
TetrisPiece createRandomPiece() {
    std::vector<std::pair<std::vector<Block>, char>> pieceShapes = {
        {{Block(0, 0), Block(1, 0), Block(2, 0), Block(3, 0)}, 'I'},
        {{Block(0, 0), Block(1, 0), Block(2, 0), Block(2, 1)}, 'L'},
        {{Block(0, 0), Block(0, 1), Block(1, 0), Block(2, 0)}, 'J'},
        {{Block(0, 0), Block(1, 0), Block(1, 1), Block(2, 1)}, 'S'},
        {{Block(0, 1), Block(1, 1), Block(1, 0), Block(2, 0)}, 'Z'},
        {{Block(0, 0), Block(1, 0), Block(1, 1), Block(2, 0)}, 'T'},
        {{Block(0, 0), Block(1, 0), Block(0, 1), Block(1, 1)}, 'O'},
    };

    int randomIndex = std::rand() % pieceShapes.size();
    return TetrisPiece(pieceShapes[randomIndex].first, pieceShapes[randomIndex].second);
}

