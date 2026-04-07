#ifndef BASIC_SHIP_BOARD_BUILDER_H
#define BASIC_SHIP_BOARD_BUILDER_H

#include "include/ShipBoardBuilder.h"
#include "include/ShipNode.h"
#include <vector>

class BasicShipBoardBuilder : public ShipBoardBuilder {
    private:

    std::vector<std::vector<ShipNode*>> redBoard;
    std::vector<std::vector<ShipNode*>> blueBoard;

    const int rows;
    const int cols;

    Color activePlayer;

    static bool redSealed;
    static bool blueSealed;

    int redPlaced = 0;
    int bluePlaced = 0;

    std::vector<Ship> redShips;
    std::vector<Ship> blueShips;    

    public:
    BasicShipBoardBuilder(Color startingPlayer, 
        int rows, int cols, 
        ShipBoard* redBoard, ShipBoard* blueBoard, 
        std::vector<Ship> redShips, std::vector<Ship> blueShips);

    void setShip(Color player, Ship& ship, Point position, bool horizontal) override;

    ShipBoard* submit(Color player) override;

    const std::vector<Ship> getShips(Color player) const override;

    //void removeShip(Color player, Point position) override;
};

#endif