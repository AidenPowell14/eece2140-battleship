#ifndef SHIP_VIEW_H
#define SHIP_VIEW_H

#include <string>
#include "View.h"
#include "BuildListener.h"
#include "../model/include/Ship.h"

/**
 * Interface for display component of the View responsible for 
 * a single player's own ship board. Namely, this includes being
 * able to see the grid, the ships, and the status of each grid/ship.
 * Via pub/sub, this class is also responsible for publishing selection
 * information to the controller. For example, if a player wishes to place 
 * a new ship at A5, they will select/click on the A5 tile; this needs to be
 * relayed to the controller.
 */
class ShipView : public View {
    public:

    /**
     * Displays a message to the user, prompting them to place a ship down.
     * 
     * @param ship a constant reference to the ship to place
     */
    virtual void promptPlace(const Ship& ship) = 0;

    /**
     * Registers an BuildListener listener for this object to 
     * publish selection information to.
     * 
     * @param controller a pointer to the controller to publish to
     * @throws std::invalid_argument if controller is null
     */
    virtual void setListener(BuildListener* controller) = 0;
};

#endif