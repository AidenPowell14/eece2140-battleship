#ifndef MODEL_H
#define MODEL_H

#include "data.h"
#include "ShipBoard.h"
#include "HitBoard.h"
#include <memory>
#include <vector>
#include <string>

#define MAX_OCCUPIED_AREA 0.5

class Controller;

class Model {
    private:

    struct Profile {
        Color player;
        std::unique_ptr<ShipBoard> shipBoard;
        std::unique_ptr<HitBoard> hitBoard;
        int ships;
    };

    Profile redProfile = Profile {Color::RED, nullptr, nullptr};
    Profile blueProfile = Profile {Color::BLUE, nullptr, nullptr};

    Profile* activeProfile;
    Profile* inactiveProfile;

    int numRows;
    int numCols;

    Controller* controller;

    bool started = false;

    void checkStartConditions(int rows, int cols, std::vector<int> redShips, std::vector<int> blueShips);
    void checkGameStarted() const;

    void switchActive();

    void publishError(std::string message) const;

    public:

    Model();

    void start(int rows, int cols, std::vector<int> redShips, std::vector<int> blueShips);

    HitStatus strike(Point pos);

    void setShip(Point start, int size, bool horizontal);

    Color isGameOver() const;

    const std::vector<std::vector<HitStatus>>& getHits(Color player) const;

    const std::vector<std::unique_ptr<Ship>>& getShips(Color player) const;

    int rows() const;

    int cols() const;

    void setListener(Controller* controller);
    
    ~Model();
};

#endif