#ifndef BUILD_LISTENER_H
#define BUILD_LISTENER_H

#include "../data/Point.h"

/**
 * Interface for a listening controller that responds to user interactions
 * regarding the initial placement of ships. All ships have a "head" from which
 * all manipulations originate (see more in ShipBoardBuilder.h). Published requests 
 * to manipulate a ship (i.e. place/rotate/remove it) may take any point as an 
 * argument, but the action itself should be relative to the head.
 * By the nature of the controller-view relationship, exception behavior such as 
 * out-of-bounds positions do not throw exceptions; there are other channels for 
 * conveying the error to the view.
 */
class BuildListener {
    public:
    /**
     * Request to place a ship's head at the specified location.
     * The default orientation (horizontal/veritcal) is specific
     * to implementation.
     * 
     * @param pos the position to place the head
     */
    virtual void setShip(Point pos) = 0;

    /**
     * Request to rotate the ship that contains the specified position.
     * This rotation is a pivot around the head of the ship.
     * If no ship is at this position, do nothing.
     * 
     * @param pos the position to find a ship within
     */
    virtual void rotateFor(Point pos) = 0;

    /**
     * Request to remove the ship that contains the specified position.
     * All connected nodes (i.e. the entire ship) will be removed if approved.
     * If no ship is at this position, do nothing.
     * 
     * @param pos the position to find a ship within
     */
    virtual void remove(Point pos) = 0;

    virtual ~BuildListener() = default;
};

#endif