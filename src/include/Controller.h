#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "data.h"
#include <string>

class Controller {

    public:

    void switchPlayer(Color player);

    void displayError(std::string message);

    void promptPlaceShip(Color player, int size);
};

#endif