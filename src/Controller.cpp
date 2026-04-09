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
    auto board = std::vector(model.rows(), std::vector<char>(model.cols(), 'O'));
    for (auto& ship : model.getShipPoints(activePlayer)) {
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
    for (int col = 0; col < model.cols()+1; col++) {
        if (col == 0|| col == model.cols () ) {
            
            std::cout << "+";
        }
        else{
            std::cout << "-----";

        }
        

    }
    std::cout << "\n";
    int lettergrid = 65;
    for (int col = 0; col < model.cols()+1; col++) {
        if (col == 0) {
            
            std::cout << "| " << "    ";
        }    
        else {
            std::cout << col << "  ";


        }
        
        
    } 
     std::cout << "| ";
    
    std::cout << "\n";
    for (auto row : board) {
        std::cout << "| " << static_cast<char>(lettergrid++) << "   ";


        for (auto cell : row) {
            std::cout << cell << "  ";
        }
        std::cout << "| \n";
    }
    for (int col = 0; col < model.cols()+1; col++) {
        if (col == 0|| col == model.cols () ) {
            
            std::cout << "+";
        }
        else{
            std::cout << "-----";

        }
        

    }
    std::cout << "\n";
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
    std::cout << "*******Explain the rules here\n";
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
        showHits();
        std::cout << "Enter location to strike: ";
        int row;
        int col;
        bool valid = false;
        do {
            try {
                if (!(std::cin >> row >> col)) {
                    throw IllegalOperation("Command arguments must be integers within board dimensions");
                }
                HitStatus status = model.strike(Point {row - 1, col - 1});
                showHits();
                std::cout << "Striking (" << row << ", " << col << ") resulted in a " << print(status) << ".\n";
                if (sunk) {
                    std::cout << print(activePlayer) << " has sunk " << print((activePlayer == Color::RED ? Color::BLUE : Color::RED)) << "'s battleship!\n";
                    sunk = false;
                }
                valid = true;
                if (winner) {
                    continue;
                }
                std::cin.ignore();
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
    //showHits();
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
    showShips();
    std::cout << "Enter location and orientation for a " << size << "-long ship: ";
    bool valid = false;
    int row;
    int col;
    char orientation;
    do {
        try {
            if (!(std::cin >> row >> col)) {
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
            model.setShip(Point {row - 1, col - 1}, size, horizontal);
            showShips();
            std::cout << "Ship was successfully placed " << (horizontal ? "horizontally" : "vertically") << " at (" << row << ", " << col << ").\n";
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