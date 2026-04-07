#include "BasicShipBoardBuilder.h"
#include "BasicShipNode.h"
#include "BasicShipBoard.h"
#include <stdexcept>

bool BasicShipBoardBuilder::redSealed = false;
bool BasicShipBoardBuilder::blueSealed = false;

BasicShipBoardBuilder::BasicShipBoardBuilder(Color startingPlayer, 
        int rows, int cols, 
        ShipBoard* redBoard, ShipBoard* blueBoard, 
        std::vector<Ship> redShips, std::vector<Ship> blueShips) :
        redBoard(rows, std::vector<ShipNode*>(cols, nullptr)), 
        blueBoard(rows, std::vector<ShipNode*>(cols, nullptr)),
        rows(rows), cols(cols),
        activePlayer(startingPlayer),
        redShips(redShips), blueShips(blueShips) {
    if (redShips.empty() || blueShips.empty()) {
        throw std::invalid_argument("Both players must have at least one ship");
    }
}

void BasicShipBoardBuilder::setShip(Color player, Ship& ship, Point position, bool horizontal) {
    if (redSealed && blueSealed) {
        throw std::invalid_argument("Both boards have already been set");
    }

    std::vector<std::vector<ShipNode*>>* board = player == Color::RED ? &redBoard : &blueBoard;

    // check for ships pushing out of bounds or crossing with other ships
    for (int off = 0; off < ship.size(); off++) {
        int row = position.row + horizontal ? 0 : off;
        int col = position.col + horizontal ? off : 0;
        if (row < 0 || row >= this->rows || col < 0 || col >= this->cols) {
            throw std::invalid_argument("Placing ship here results in out of bounds placement");
        }
        ShipNode* checkedCell = horizontal ? (*board)[position.row][position.col + off] : (*board)[position.row + off][position.col];
        if (checkedCell != nullptr) {
            throw std::invalid_argument("Placing ship here results in intersecting ships");
        }
    }

    // place ShipNodes cell by cell
    for (int off = 0; off < ship.size(); off++) {
        int row = position.row + horizontal ? 0 : off;
        int col = position.col + horizontal ? off : 0;

        (*board)[row][col] = &BasicShipNode(ship);
    }
    player == Color::RED ? redPlaced++ : bluePlaced++;
}

ShipBoard* BasicShipBoardBuilder::submit(Color player) {
    if (player == Color::RED) {
        if (redPlaced < 1) {
            throw std::invalid_argument("Red cannot play without placing any ships");
        }
        redSealed = true;
        activePlayer = Color::BLUE;
        return &BasicShipBoard(redBoard, rows, cols, player);
    } else {
        if (bluePlaced < 1) {
            throw std::invalid_argument("Blue cannot play without placing any ships");
        }
        blueSealed = true;
        activePlayer = Color::RED;
        return &BasicShipBoard(blueBoard, rows, cols, player);
    }
}

// const Ship& BasicShipBoardBuilder::removeShip(Color player, Point position) {

// }

const std::vector<Ship> BasicShipBoardBuilder::getShips(Color player) const {
    return player == Color::RED ? redShips : blueShips;
}