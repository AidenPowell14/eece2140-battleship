#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "data.h"
//#include "Model.h"
#include <string>

class Model;

class Controller {
    private:

    Color activePlayer;
    Model& model;

    bool gameOver = false;
    Color winner = Color::NEITHER;
    bool sunk = false;

    void showHits() const;
    void showShips() const;

    void endGame();
    void wait() const;

    const std::string print(Color player) const;
    const std::string print(HitStatus status) const;

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