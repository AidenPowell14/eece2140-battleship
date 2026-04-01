#ifndef BASIC_GAME_MODEL_H
#define BASIC_GAME_MODEL_H

#include "include/GameModel.h"

class BasicShipModel : public GameModel {
    private:

    HitBoard board;

    public:

    BasicShipModel() {}

    ShipBoardBuilder start(int rows, int cols, std::vector<Ship> redShips, std::vector<Ship> blueShips) override;

    Color getActivePlayer() const override;

    bool isGameOver() const override;

    HitStatus strike(Point position) override;

    const HitBoard& getHits(Color player) override;

    const ShipBoard& getShips(Color player) override;

    void setListener(TurnListener* controller) override;
};

#endif