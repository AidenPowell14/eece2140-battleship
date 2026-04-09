#include "include/Controller.h"
#include "include/Model.h"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>

void Controller::endGame(Color winner) {

}

void Controller::showHits() const {
    std::cout << "\033[2J\033[1;1H";
    for (std::vector<HitStatus> row : model.getHits(activePlayer)) {
        for (HitStatus status : row) {
            std::string mark;
            if (status == HitStatus::NONE) {
                mark = "O";
            } else if (status == HitStatus::MISS) {
                mark = "X";
            } else {
                mark = "*";
            }
            std::cout << mark << " ";
        }
        std::cout << std::endl;
    }
}

void Controller::showShips() const {
    std::cout << "\033[2J\033[1;1H";
    std::cout << "shipboard\n";
    auto board = std::vector(model.rows(), std::string(2 * model.cols() - 1, 'O'));
    for (std::vector<Point> shipPoints : model.getShipPoints(activePlayer)) {
        for (Point point : shipPoints) {
            board[point.row][point.col * 2] = 'X';
        }
    }
    for (std::string row : board) {
        std::cout << row << std::endl;
    }
}

const std::string Controller::print(Color player) const {
    return player == Color::RED ? "RED" : "BLUE";
}

const std::string Controller::print(HitStatus status) const {
    if (status == HitStatus::HIT) {
        return "HIT";
    } else if (status == HitStatus::MISS) {
        return "MISS";
    } else {
        return "UNSTRUCK";
    }
}

Controller::Controller(Model& model) : model(model) {}

void Controller::switchPlayer(Color player) {
    activePlayer = player;
    std::cout << "\033[2J\033[1;1H"; // clears screen
    std::cout << "It is now " << print(player) << "'s turn. Press ENTER if you are the " << print(player) << " player.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //std::cout << "\033[2J\033[1;1H";
}

void Controller::takeTurn() {
    showHits();
    std::cout << "Enter location to strike: ";
    int row;
    int col;
    bool valid = false;
    do {
        try {
            if (!(std::cin >> row && std::cin >> col)) {
                throw IllegalOperation("Command arguments must be integers within board dimensions");
            }
            std::cin.ignore();
            HitStatus status = model.strike(Point {row, col});
            std::cout << "Striking (" << row << ", " << col << ") resulted in a " << print(status) << ".\n";
            valid = true;
        } catch (const IllegalOperation& badStrike) {
            displayError(badStrike.what());
            std::cout << "Try again: ";      
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!valid);
    // program returns here
}

void Controller::displayError(std::string message) const {
    std::cout << message << ".\n";
}


void Controller::sunkBattleship() {
    std::cout << activePlayer << "has sunk " << (activePlayer == Color::RED ? Color::BLUE : Color::RED) << "'s battleship!\n";
    Color winner;
    if (model.isGameOver(&winner)) {
        endGame(winner);
    }
}

void Controller::promptPlaceShip(int size) {
    showShips();
    std::cout << "Enter location and orientation for a " << size << "-long ship: ";
    bool valid = false;
    int row;
    int col;
    char orientation;
    do {
        try {
            if (!(std::cin >> row && std::cin >> col)) {
                throw IllegalOperation("First and second command arguments must be integers within board dimensions");
            }
            if (!(std::cin >> orientation)) {
                throw IllegalOperation("Third position command must be 'h' or 'v'");
            } 
            bool horizontal;
            if (!(std::tolower(orientation) - 104)) {
                horizontal = true;
            } else if (!(std::tolower(orientation) - 118)) {
                horizontal = false;
            } else {
                throw IllegalOperation("Third position command must be 'h' or 'v'");
            }
            std::cin.ignore();
            model.setShip(Point {row - 1, col - 1}, size, horizontal);
            valid = true;
        } catch (const IllegalOperation& badMove) {
            displayError(badMove.what());
            std::cout << "Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!valid);
}

Controller::~Controller() {}