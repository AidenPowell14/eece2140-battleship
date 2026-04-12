#include "include/Model.h"
#include "include/Controller.h"
#include <iostream>

void Model::checkStartConditions(int rows, int cols, std::vector<int> redShips, std::vector<int> blueShips) {
    // check for invalid board size
    if (rows < 0 || rows > 26 || cols < 0 || cols > 26) {
        throw IllegalOperation("Each board dimension must be between 1 and 26 cells");
    }
    // check for empty ship list
    if (redShips.empty() || blueShips.empty()) {
        throw IllegalOperation("Cannot play without any ships");
    }
    int redSum = 0;
    int blueSum = 0;
    for (int length : redShips) {
        // check for ship longer than board
        if (length > rows && length > cols) {
            throw IllegalOperation("Cannot play with ships larger than board");
        }
        redSum += length;
    }
    for (int length : blueShips) {
        // check for ship longer than board
        if (length > rows && length > cols) {
            throw IllegalOperation("Cannot play with ships larger than board");
        }
        blueSum += length;
    }
    // check total area occupied isn't greater than MAX_OCCUPIED_AREA
    if ((double) redSum / (rows * cols) > MAX_OCCUPIED_AREA || (double) blueSum / (rows * cols) > MAX_OCCUPIED_AREA) {
        throw IllegalOperation("Cannot comfortably fit ships on board of this size");
    }
}

void Model::checkGameStarted() const {
    if (!started) {
        throw IllegalOperation("Game has not started");
    }
}

void Model::switchActive() {
    if (activeProfile->player == Color::RED) {
        activeProfile = &blueProfile;
        inactiveProfile = &redProfile;
    } else {
        activeProfile = &redProfile;
        inactiveProfile = &blueProfile;
    }
}

void Model::publishError(std::string message) const {
    if (controller) {
        controller->displayError(message);
    }
}



Model::Model() {}

void Model::start(int rows, int cols, std::vector<int> redShips, std::vector<int> blueShips) {
    checkStartConditions(rows, cols, redShips, blueShips);
    numRows = rows;
    numCols = cols;
    started = true;
    // red goes first
    activeProfile = &redProfile;
    inactiveProfile = &blueProfile;
    // give each pllayer empty boards
    activeProfile->hitBoard = std::move(std::make_unique<HitBoard>(activeProfile->player, numRows, numCols));
    inactiveProfile->hitBoard = std::move(std::make_unique<HitBoard>(inactiveProfile->player, numRows, numCols));
    activeProfile->shipBoard = std::move(std::make_unique<ShipBoard>(activeProfile->player, numRows, numCols));
    inactiveProfile->shipBoard = std::move(std::make_unique<ShipBoard>(inactiveProfile->player, numRows, numCols));
    // set each player's number of ships before defeat
    redProfile.ships = redShips.size();
    blueProfile.ships = blueShips.size();
    if (controller) {
        controller->switchPlayer(Color::RED);
    }
    // request controller callback to place all ships
    for (int length : redShips) {
        if (controller) {
            controller->promptPlaceShip(length);
        }
    }
    redProfile.shipBoard->seal();
    // give controller a chance to flush display
    switchActive();
    if (controller) {
        controller->switchPlayer(Color::BLUE);
    }
    for (int length : blueShips) {
        if (controller) {
            controller->promptPlaceShip(length);
        }
    }
    blueProfile.shipBoard->seal();
    switchActive();
    if (controller) {
        controller->switchPlayer(Color::RED);
        controller->startAttacks();
    }
}

HitStatus Model::strike(Point pos) {
    checkGameStarted();
    if (pos.row < 0 || pos.row >= numRows || pos.col < 0 || pos.col >= numCols) {
        throw IllegalOperation("Requested strike position is out of bounds");
    }
    // cannot strike same location twice
    if (activeProfile->hitBoard->get(pos) != HitStatus::NONE) {
        throw IllegalOperation("Already struck this location");
    }
    // checks each point on each ship for a match
    auto& ships = inactiveProfile->shipBoard->seeShips();
    for (auto& ship : ships) {
        for (int off = 0; off < ship->size; off++) {
            int row = ship->start.row + (ship->horizontal ? 0 : off);
            int col = ship->start.col + (ship->horizontal ? off : 0);
            if (pos.row == row && pos.col == col) {
                // on hit: update attacker view, reduce ship health, switch players, report hit
                activeProfile->hitBoard->struck(pos, HitStatus::HIT);
                ship->hitLocs.push_back(pos);
                if (ship->hitLocs.size() == ship->size) {
                    inactiveProfile->ships--;
                    controller->sunkBattleship();
                }
                switchActive();
                return HitStatus::HIT;
            }
        }
    }
    // if nothing found, miss
    activeProfile->hitBoard->struck(pos, HitStatus::MISS);
    switchActive();
    return HitStatus::MISS;
}

void Model::setShip(Point start, int size, bool horizontal) {
    checkGameStarted();
    activeProfile->shipBoard->addShip(start, size, horizontal);
}

Color Model::isGameOver() const {
    if (redProfile.ships == 0) {
        return Color::BLUE;
    } else if (blueProfile.ships == 0) {
        return Color::RED;
    }
    return Color::NEITHER;
}

const std::vector<std::vector<HitStatus>>& Model::getHits(Color player) const {
    checkGameStarted();
    return player == Color::RED ? redProfile.hitBoard->get() : blueProfile.hitBoard->get();
}

const std::vector<std::unique_ptr<Ship>>& Model::getShips(Color player) const {
    checkGameStarted();
    return player == Color::RED ? redProfile.shipBoard->seeShips() : blueProfile.shipBoard->seeShips();
}

int Model::rows() const {
    checkGameStarted();
    return numRows;
}

int Model::cols() const {
    checkGameStarted();
    return numCols;
}

void Model::setListener(Controller* controller) {
    this->controller = controller;
}

Model::~Model() {}