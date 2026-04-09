#ifndef SHIP_H
#define SHIP_H

#include "../../data/ShipStatus.h"
#include "../../data/Point.h"

/**
 * Interface for any type of ship for Battleship.
 * All ships have a size, which determines how many hits it can take before sinking. 
 * Since most ships occupy more than a single cell of the ShipBoard, Ships themselves
 * do not actually go on the board; Ships are owned by their constituent ShipNodes,
 * which each represent a unicellular segment of a Ship. Because of this, Ships
 * do not need to maintain state regarding individual cells (e.g. if a particular node
 * has been hit or not), only overarching state of the whole ship.
 */
class Ship {
    public:

    /**
     * Gets the total size of this ship.
     * 
     * @return int size of the ship
     */
    virtual int size() const = 0;

    /**
     * Get the total number of hits for this ship.
     * The difference between the size and the number of 
     * hits on this ship indicates its remaining "health".
     * 
     * @return int number of hits taken
     */
    virtual int hits() const = 0;

    /**
     * Gets the current status of this ship, i.e. whether 
     * it has been sunk or still floating. A ship is sunk 
     * when it has been hit a number of times equal to its
     * size. These hits should be to different cells, but that
     * need not be enforced here.
     *
     * @return ShipStatus the current status of this ship
     */
    virtual ShipStatus status() const = 0;

    /**
     * Signals to this Ship to take one hit of damage,
     * getting it closer to being sunk. The Ship's status is
     * also returned here in case taking a hit would sink it.
     * 
     * @return ShipStatus the status of this ship after taking a hit
     */
    virtual ShipStatus takeHit() = 0;

    virtual ~Ship() = default;
};

#endif
