#include "BasicGameModel.h"
#include "BasicHitBoard.h"
#include "BasicShipBoardBuilder.h"
#include <stdexcept>

void BasicGameModel::checkBounds(Point position) const {
    if (position.row < 0 || position.row >= rows || position.col < 0 || position.col >= cols) {
        throw std::invalid_argument("position out of bounds");
    }
}

void BasicGameModel::checkStarted() const {
    if (!started) {
        throw std::invalid_argument("game has not started yet");
    }
}

// default construct with invalid profiles and RED going first
BasicGameModel::BasicGameModel() : 
activeProfile(&redProfile),
inactiveProfile(&blueProfile),
redProfile({Color::RED, nullptr, nullptr, -1}),
blueProfile({Color::BLUE, nullptr, nullptr, -1}),
controller(nullptr),
started(false) {}

ShipBoardBuilder* BasicGameModel::start(int rows, int cols, std::vector<Ship> redShips, std::vector<Ship> blueShips) {
    if (started) {
        throw std::invalid_argument("Game has already been started");
    }
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Cannot have nonpositive board size");
    }
    if (redShips.size() == 0 || blueShips.size() == 0) {
        throw std::invalid_argument("Cannot play with less than one ship");
    }

    int totalSizeRed = 0;
    int totalSizeBlue = 0;
    int totalSizeAllowed = rows * cols * MAX_SHIP_RATIO;

    for (Ship& ship : redShips) {
        totalSizeRed += ship.size();
        if (ship.size() > rows || ship.size() > cols) {
            throw std::invalid_argument("Some ship is larger than the board");
        }
    }
    for (Ship& ship : blueShips) {
        totalSizeBlue += ship.size();
        if (ship.size() > rows || ship.size() > cols) {
            throw std::invalid_argument("Some ship is larger than the board");
        }
    }

    if (totalSizeRed > totalSizeAllowed || totalSizeBlue > totalSizeAllowed) {
        throw std::invalid_argument("Ships occupy too much of the board to play comfortably");
    }

    this->rows = rows;
    this->cols = cols;

    redProfile.hitBoard = &BasicHitBoard(Color::RED, rows, cols);
    blueProfile.hitBoard = &BasicHitBoard(Color::BLUE, rows, cols);

    redProfile.numShips = redShips.size();
    blueProfile.numShips = blueShips.size();

    started = true;
    return &BasicShipBoardBuilder(activeProfile->player, rows, cols, redProfile.shipBoard, blueProfile.shipBoard, redShips, blueShips);
}

Color BasicGameModel::getActivePlayer() const {
    checkStarted();
    return activeProfile->player;
}

bool BasicGameModel::isGameOver() const {
    checkStarted();
    return activeProfile->numShips == 0 || inactiveProfile->numShips == 0;
}

HitStatus BasicGameModel::strike(Point position) {
    checkStarted();
    checkBounds(position);
    // check they haven't struck this position previously
    if (activeProfile->hitBoard->get(position) != NULL) {
        throw std::invalid_argument("Position has already been struck");
    }

    // retrieve strike status from victim ShipBoard and update aggressor HitBoard
    HitStatus status = inactiveProfile->shipBoard->strike(position);
    activeProfile->hitBoard->struck(position, status);

    // if the ship struck by this attack resulted in sinking the ship, report to controller
    if (status == HitStatus::HIT && inactiveProfile->shipBoard->get(position).getShip().status() == ShipStatus::SUNK) {
        controller->battleShipSunk(inactiveProfile->player);
    }

    // invert active and inactive players
    activeProfile = activeProfile->player == Color::RED ? &blueProfile : &redProfile;
    inactiveProfile = inactiveProfile->player == Color::RED ? &blueProfile : &redProfile;

    // notify controller of new active player
    controller->newActivePlayer(activeProfile->player);

    // report strike outcome
    return status;
}

const HitBoard& BasicGameModel::getHits(Color player) const {
    return player == Color::RED ? *redProfile.hitBoard : *blueProfile.hitBoard;
}

const ShipBoard& BasicGameModel::getShips(Color player) const {
    return player == Color::RED ? *redProfile.shipBoard : *blueProfile.shipBoard;
}  

void BasicGameModel::setListener(TurnListener* controller) {
    if (controller != nullptr) {
        this->controller = controller;
    }
}