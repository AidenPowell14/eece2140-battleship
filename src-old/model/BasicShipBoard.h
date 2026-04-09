#ifndef BASIC_SHIP_BOARD_H
#define BASIC_SHIP_BOARD_H

#include "include/ShipBoard.h"
#include <vector>
#include <memory>

class BasicShipBoard : public ShipBoard {
    private:

    int numRows;
    int numCols;

    const std::vector<std::vector<std::unique_ptr<ShipNode>>> board;

    Color owner;

    public:

    BasicShipBoard(std::vector<std::vector<std::unique_ptr<ShipNode>>> board, int rows, int cols, Color player);

    Color getOwner() const override;

    const std::unique_ptr<ShipNode> get(Point position) const override;

    HitStatus strike(Point position) override;

    const int rows() const override;

    const int cols() const override;

    ~BasicShipBoard();
};

#endif