#include "BasicShipBoard.h"
#include <vector>
#include <stdexcept>

BasicShipBoard::BasicShipBoard(std::vector<std::vector<std::unique_ptr<ShipNode>>> board, int rows, int cols, Color player) : 
board(board), numRows(rows), numCols(cols), owner(player) {}

Color BasicShipBoard::getOwner() const {
    return owner;
}

const std::unique_ptr<ShipNode> BasicShipBoard::get(Point position) const {
    if (position.row < 0 || position.row > numRows || position.col < 0 || position.col > numCols) {
        throw std::invalid_argument("Position is out of bounds");
    }
    return board[position.row][position.col];
}

HitStatus BasicShipBoard::strike(Point position) {
    if (position.row < 0 || position.row > numRows || position.col < 0 || position.col > numCols) {
        throw std::invalid_argument("Position is out of bounds");
    }
    // if no ship present, report miss
    if (board[position.row][position.col] == nullptr) {
        return HitStatus::MISS;
    }
    // else update relevant node and report hit
    board[position.row][position.col]->strike();
    return HitStatus::HIT;
}

const int BasicShipBoard::rows() const {
    return numRows;
}

const int BasicShipBoard::cols() const {
    return numCols;
}

BasicShipBoard::~BasicShipBoard() {}