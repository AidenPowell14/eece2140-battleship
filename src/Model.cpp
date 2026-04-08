#include "include/Model.h"
#include <iostream>

bool Model::checkStartConditions(int rows, int cols, std::vector<int> redShips, std::vector<int> blueShips) {
    // check for invalid board size
    if (rows < 0 || cols < 0) {
        publishError("Board must have positive dimensions");
        return false;
    }
    // check for empty ship list
    if (redShips.empty() || blueShips.empty()) {
        publishError("Cannot play without any ships");
        return false;
    }
    int redSum = 0;
    int blueSum = 0;
    for (int length : redShips) {
        // check for ship longer than board
        if (length > rows || length > cols) {
            publishError("Cannot play with ships larger than board");
            return false;
        }
        redSum += length;
    }
    for (int length : blueShips) {
        // check for ship longer than board
        if (length > rows || length > cols) {
            publishError("Cannot play with ships larger than board");
            return false;
        }
        blueSum += length;
    }
    // check total area occupied isn't greater than MAX_OCCUPIED_AREA
    if ((double) redSum / (rows * cols) > MAX_OCCUPIED_AREA || (double) blueSum / (rows * cols) > MAX_OCCUPIED_AREA) {
        publishError("Cannot comfortably fit this many ships on board of this size");
        return false;
    }
    return true;
}

bool Model::checkGameStarted() {
    if (!started) {
        publishError("Game has not started!");
        return false;
    }
    return true;
}

void Model::publishError(std::string message) {
    if (controller) {
        controller->displayError(message);
    }
}

bool Model::start(int rows, int cols, std::vector<int> redShips, std::vector<int> blueShips) {
    if (!checkStartConditions(rows, cols, redShips, blueShips)) {
        return false;
    }
    numRows = rows;
    numCols = cols;
    // red goes first
    activeProfile = &redProfile;
    inactiveProfile = &blueProfile;
    if (controller) {
        controller->switchPlayer(Color::RED);
    }
    // request controller callback to place all ships
    for (int length : redShips) {
        if (controller) {
            controller->promptPlaceShip(Color::RED, length);
        }
    }
    // give controller a chance to flush display
    if (controller) {
        controller->switchPlayer(Color::BLUE);
    }
    for (int length : blueShips) {
        if (controller) {
            controller->promptPlaceShip(Color::BLUE, length);
        }
    }
}



bool Model::setShip(Point start, int size, bool horizontal) {
    activeProfile->shipBoard->addShip(start, size, horizontal);
}

void Model::setListener(Controller* controller) {
    this->controller = controller;
}