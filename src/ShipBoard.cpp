#include "include/ShipBoard.h"

ShipBoard::ShipBoard(Color owner, int rows, int cols) : player(owner), numRows(rows), numCols(cols) {}


bool ShipBoard::addShip(Point start, int size, bool horizontal) {
    for (auto& ship : ships) {
        
    }

    // check placement wouldn't go out of bounds or intersect with existing ship
    for (int off = 0; off < size; off++) {
        // establish growth direction: right or down
        int row = start.row + (horizontal ? 0 : off);
        int col = start.col + (horizontal ? off : 0);
        if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
            return false;
        }
        for (auto& ship : ships) {
            Point shipStart = ship->start;
            Point shipEnd = ship->horizontal ? 
                Point {shipStart.row, shipStart.col + ship->size - 1} : 
                Point {shipStart.row + ship->size - 1, shipStart.col};
            
        }
    }
}

void ShipBoard::seal() {
    sealed = true;
}

ShipBoard::~ShipBoard() {}