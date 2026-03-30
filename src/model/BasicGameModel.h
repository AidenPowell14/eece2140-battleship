#ifndef BASIC_GAME_MODEL_H
#define BASIC_GAME_MODEL_H

#include "include/GameModel.h"

class BasicShipModel : public GameModel {
    private:

    public:

    ShipBoardBuilder start(int rows, int cols, std::vector<Ship> redShips, std::vector<Ship> blueShips) override;


};

#endif