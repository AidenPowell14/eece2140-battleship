#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "data.h"
#include <string>

class Model;

class Controller {
    private:

    Color activePlayer;
    Model& model;

    bool gameOver = false;
    Color winner = Color::NEITHER;
    bool sunk = false;

    void showAll() const;

    void endGame();
    void wait() const;

    const std::string print(Color player) const;
    const std::string print(HitStatus status) const;

    std::string horizontalEdge() const;

    public:

    Controller(Model& model);

    void preface() const;

    void switchPlayer(Color player);

    void startAttacks();

    void displayError(std::string message) const;

    void promptPlaceShip(int size);

    void sunkBattleship();

    ~Controller();
};

#endif