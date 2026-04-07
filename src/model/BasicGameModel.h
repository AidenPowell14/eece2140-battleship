#ifndef BASIC_GAME_MODEL_H
#define BASIC_GAME_MODEL_H

#include "include/GameModel.h"

class BasicGameModel : public GameModel {
    private:
    
    struct Profile {
        Color player;
        ShipBoard* shipBoard;
        HitBoard* hitBoard;
        int numShips;
    };

    int rows;
    int cols;

    Profile* activeProfile;
    Profile* inactiveProfile;

    Profile redProfile;
    Profile blueProfile;

    TurnListener* controller;

    bool started;

    void checkBounds(Point position) const;
    void checkStarted() const;

    friend HitBoard;

    public:

    BasicGameModel();

    ShipBoardBuilder* start(int rows, int cols, std::vector<Ship> redShips, std::vector<Ship> blueShips) override;

    Color getActivePlayer() const override;

    bool isGameOver() const override;

    HitStatus strike(Point position) override;

    const HitBoard& getHits(Color player) const override;

    const ShipBoard& getShips(Color player) const override;

    void setListener(TurnListener* controller) override;

    ~BasicGameModel();
};

#endif