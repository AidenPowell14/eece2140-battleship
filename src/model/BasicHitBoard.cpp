#include "BasicHitBoard.h"
#include <stdexcept>

BasicHitBoard::BasicHitBoard(Color owner, int rows, int cols) : 
owner(owner), rows(rows), cols(cols), 
board(rows, std::vector<HitStatus>(cols, HitStatus::NONE)) {}

Color BasicHitBoard::getOwner() const {
    return owner;
}

HitStatus BasicHitBoard::get(Point position) const {
    if (position.row < 0 || position.row >= rows || position.col < 0 || position.col >= cols) {
        throw std::invalid_argument("position out of bounds");
    }
    return board[position.row][position.col];
}

void BasicHitBoard::struck(Point position, HitStatus status) {
    if (position.row < 0 || position.row >= rows || position.col < 0 || position.col >= cols) {
        throw std::invalid_argument("position out of bounds");
    }
    if (status == HitStatus::NONE) {
        throw std::invalid_argument("cannot set HitBoard to NONE");
    }
    board[position.row][position.col] = status;
}

BasicHitBoard::~BasicHitBoard() {}