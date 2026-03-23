#ifndef TEXT_CONTROLLER_H
#define TEXT_CONTROLLER_H

#include "include/Controller.h"
#include "../data/Point.h"
#include "../data/Color.h"

class TextController : public Controller {
    private: 
    
    public: 

    // BuildListener
    void setShip(Point pos) override;
    void rotateFor(Point pos) override;
    void remove(Point pos) override;

    // PlayListener
    void selectPoint(Point pos) override;
    void confirmStrike() override;

    // TurnListener
    void newActivePlayer(Color player) override;

};

#endif