#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../view/include/BuildListener.h"
#include "../../view/include/PlayListener.h"
#include "../../model/include/TurnListener.h"

class Controller : public BuildListener, public PlayListener, public TurnListener {

    
};

#endif