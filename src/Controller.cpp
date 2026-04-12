#include "include/Controller.h"
#include "include/Model.h"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>

void Controller::endGame() {
    std::cout << "The " << print(winner) << " player has won! Restart the program to play again.\n";
}

void Controller::wait() const {
    std::cout << "Press ENTER to continue.\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string Controller::horizontalEdge() const { 
    std::string edge = "+---";
    for (int col = 0; col < model.cols(); col++) {
        edge += "---";
    }
    edge += "-+\n";
    return edge;
}

void Controller::showAll() const {
    // clear screen;
    std::cout << "\033[2J\033[1;1H";
    // upper edge
    std::cout << horizontalEdge() << "|    ";
    // ship header
    for (int col = 1; col <= model.cols(); col++) {
        std::cout << col << (col < 10 ? "  " : " ");
    }
    std::cout << "|\n";
    // ship rows
    int letterGrid = 65;
    for (std::vector<HitStatus> row : model.getHits(activePlayer)) {
        std::cout << "| " << static_cast<char>(letterGrid++) << "  ";
        for (HitStatus status : row) {
            std::string mark;
            if (status == HitStatus::NONE) {
                mark = "O";
            } else if (status == HitStatus::MISS) {
                mark = "X";
            } else {
                mark = "*";
            }
            std::cout << mark << "  ";
        }
        std::cout << "|\n";
    }
    // middle edge
    std::cout << horizontalEdge() + "|    ";
    // hit header
    for (int col = 1; col <= model.cols(); col++) {
        std::cout << col << (col < 10 ? "  " : " ");
    }
    std::cout << "|\n";
    // hit rows
    auto board = std::vector(model.rows(), std::vector<char>(model.cols(), 'O'));
    for (auto& ship : model.getShips(activePlayer)) {
        // sets '*' for each hit cell of each ship
        for (Point point : ship->hitLocs) {
            board[point.row][point.col] = '*';
        }
        // sets 'X' for the rest of each ship
        for (int off = 0; off < ship->size; off++) {
            int row = ship->start.row + (ship->horizontal ? 0 : off);
            int col = ship->start.col + (ship->horizontal ? off : 0);
            if (board[row][col] == 'O') {
                board[row][col] = 'X';
            }
        }        
    }
    letterGrid = 65;
    for (auto row : board) {
        std::cout << "| " << static_cast<char>(letterGrid++) << "  ";
        for (auto cell : row) {
            std::cout << cell << "  ";
        }
        std::cout << "|\n";
    }
    // bottom edge
    std::cout << horizontalEdge();
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

void Controller::preface() const {
    std::cout << "\033[2J\033[1;1H";
    std::cout << "==== 2 PLAYER BATTLESHIP ====\n";
    std::cout << "* Turns are taken sequentially, with a confirmation message\n  for each player to ensure a fair device handoff between turns.\n";
    std::cout << "* Ship placement takes three space-separated arguments:\n  a letter row, integer column, and 'H' or 'V' for horizontal or veritcal orientation.\n"
    << "  Ships will \"grow\" to the right or below the specified point.\n";
    std::cout << "* Attacks only accept a letter row and integer column. Unstruck ships\n  will be represented with 'X', struck ships as '*', and empty spaces as 'O'.\n"; 
    wait();
}

void Controller::switchPlayer(Color player) {
    activePlayer = player;
    std::cout << "\033[2J\033[1;1H"; // clears screen
    std::cout << "It is now " << print(player) << "'s turn.\n";
    wait();
}

void Controller::startAttacks() {
    while (!winner) {
        showAll();
        std::cout << "Enter location to strike: ";
        char strRow;
        int col;
        bool valid = false;
        do {
            try {
                if (!(std::cin >> strRow)) {
                    throw IllegalOperation("First command argument must be a letter within board dimensions");
                }
                if (!(std::cin >> col)) {
                    throw IllegalOperation("Second command argument must be an integer within board dimensions");
                }
                int row = std::tolower(strRow) - 'a' + 1;
                HitStatus status = model.strike(Point {row - 1, col - 1});
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                
                showAll();
                std::cout << "Striking " << static_cast<char>(std::toupper(row + 64)) << col << " resulted in a " << print(status) << ".\n";
                if (sunk) {
                    std::cout << print(activePlayer) << " has sunk " << print((activePlayer == Color::RED ? Color::BLUE : Color::RED)) << "'s battleship!\n";
                    sunk = false;
                }
                valid = true;
                if (winner) {
                    continue;
                }
                wait();
            } catch (const IllegalOperation& badStrike) {
                displayError(badStrike.what());
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Try again: ";      
            }
        } while (!valid);
        if (!winner) {
            switchPlayer(activePlayer == Color::RED ? Color::BLUE : Color::RED);
        }
    }
    endGame();
    // program exits starting here
}

void Controller::displayError(std::string message) const {
    std::cout << message << ".\n";
}


void Controller::sunkBattleship() {
    sunk = true;
    winner = model.isGameOver();
}

void Controller::promptPlaceShip(int size) {
    showAll();
    std::cout << "Enter location and orientation for a " << size << "-long ship: ";
    bool valid = false;
    char strRow;
    int col;
    char orientation;
    do {
        try {
            if (!(std::cin >> strRow)) {
                throw IllegalOperation("First command argument must be a letter within board dimensions");
            }
            if (!(std::cin >> col)) {
                throw IllegalOperation("Second command argument must be an integer within board dimensions");
            }
            if (!(std::cin >> orientation)) {
                throw IllegalOperation("Third position command must be 'h' or 'v'");
            } 
            int row = std::tolower(strRow) - 'a' + 1;
            bool horizontal;
            if (!(std::tolower(orientation) - 'h')) {
                horizontal = true;
            } else if (!(std::tolower(orientation) - 'v')) {
                horizontal = false;
            } else {
                throw IllegalOperation("Third position command must be 'h' or 'v'");
            }
            model.setShip(Point {row - 1, col - 1}, size, horizontal);
            showAll();
            std::cout << "Ship was successfully placed " << (horizontal ? "horizontally" : "vertically") << " at " << static_cast<char>(std::toupper(row + 64)) << col << ".\n";
            valid = true;
            std::cin.ignore();
            wait();
        } catch (const IllegalOperation& badMove) {
            displayError(badMove.what());
            std::cout << "Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!valid);
}

Controller::~Controller() {}