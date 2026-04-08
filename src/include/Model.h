#ifndef MODEL_H
#define MODEL_H

#include "data.h"
#include "ShipBoard.h"
#include "HitBoard.h"
#include "Controller.h"
#include <memory>
#include <vector>
#include <string>

#define MAX_OCCUPIED_AREA 0.5

class Model {
    private:

    Profile redProfile = Profile {Color::RED, nullptr, nullptr};
    Profile blueProfile = Profile {Color::BLUE, nullptr, nullptr};

    Profile* activeProfile;
    Profile* inactiveProfile;

    int numRows;
    int numCols;

    Controller* controller;

    bool started = false;

    bool checkStartConditions(int rows, int cols, std::vector<int> redShips, std::vector<int> blueShips);
    bool checkGameStarted();

    void publishError(std::string message);

    public:

    Model();

    bool start(int rows, int cols, std::vector<int> redShips, std::vector<int> blueShips);

    HitStatus strike(Point pos);

    bool setShip(Color player, Point start, int size, bool horizontal);

    const std::vector<std::vector<HitStatus>> getHits(Color player) const;

    const std::vector<std::vector<Point>> getShipPoints(Color player) const;

    int rows() const;

    int cols() const;

    void setListener(Controller* controller);
    
    ~Model();
};

#endif