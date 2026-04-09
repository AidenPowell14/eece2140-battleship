#include "include/HitBoard.h"

HitBoard::HitBoard(Color player, int rows, int cols) : 
owner(player), numRows(rows), numCols(cols), 
board(rows, std::vector<HitStatus>(cols, HitStatus::NONE)) {}

const std::vector<std::vector<HitStatus>>& HitBoard::get() {
    return board;
}

HitStatus HitBoard::get(Point pos) {
    if (pos.row < 0 || pos.row >= numRows || pos.col < 0 || pos.col >= numCols) {
        throw IllegalOperation("Requested position is out of bounds");
    }
    return board[pos.row][pos.col];
}

void HitBoard::struck(Point pos, HitStatus status) {
    if (pos.row < 0 || pos.row >= numRows || pos.col < 0 || pos.col >= numCols) {
        throw IllegalOperation("Requested position is out of bounds");
    }
    board[pos.row][pos.col] = status;
}

HitBoard::~HitBoard() {}