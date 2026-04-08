#ifndef SHIP_BOARD_H
#define SHIP_BOARD_H

#include "data.h"
#include <vector>
#include <memory>

struct Ship {
    Point start;
    int size;
    bool horizontal;
};

class ShipBoard {
    private:

    const Color player;
    const int numRows;
    const int numCols;

    std::vector<std::unique_ptr<Ship>> ships;

    bool sealed = false;

    public:

    ShipBoard(Color owner, int rows, int cols);
    
    const std::vector<std::unique_ptr<Ship>>& seeShips() const;

    bool addShip(Point start, int size, bool horizontal);

    void seal();

    ~ShipBoard();
};

#endif