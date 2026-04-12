#include "include/ShipBoard.h"

// ensure that B is always below or right of A
bool ShipBoard::checkPointBetween(Point test, Point a, Point b) {
    return test.row >= a.row && test.row <= b.row && test.col >= a.col && test.col <= b.col;
}

ShipBoard::ShipBoard(Color owner, int rows, int cols) : player(owner), numRows(rows), numCols(cols) {}

const std::vector<std::unique_ptr<Ship>>& ShipBoard::seeShips() const {
    return ships;
}

void ShipBoard::addShip(Point start, int size, bool horizontal) {
    // sealed boards cannot be added to 
    if (sealed) {
        throw IllegalOperation("This board was already built -- cannot add any more ships");
    }
    // check placement wouldn't go out of bounds or intersect with existing ship
    for (int off = 0; off < size; off++) {
        // establish growth direction: right or down
        int row = start.row + (horizontal ? 0 : off);
        int col = start.col + (horizontal ? off : 0);
        if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
            throw IllegalOperation("This position is out of bounds");
        }
        for (auto& ship : ships) {
            Point shipStart = ship->start;
            Point shipEnd = ship->horizontal ? 
                Point {shipStart.row, shipStart.col + ship->size - 1} : 
                Point {shipStart.row + ship->size - 1, shipStart.col};
            if (checkPointBetween(Point {row, col}, shipStart, shipEnd)) {
                throw IllegalOperation("Placing a ship here would intersect with an existing ship");
            }
        }
    }
    // add to list of ships
    ships.push_back(std::make_unique<Ship>(Ship{start, size, horizontal}));
}

void ShipBoard::seal() {
    sealed = true;
}

ShipBoard::~ShipBoard() {}