#ifndef SHIP_H
#define SHIP_H

#include "../../data/ShipStatus.h"
#include "../../data/Point.h"

/**
 * Interface for any type of ship for Battleship.
 * All ships have a size, which determines how they occupy the board
 * and how many hits it can take before sinking. 
 * 
 * 
 * pointer to its head. All ships are assumed to be contiguous, rigid lines; 
 * they are either completely vertical or completely horizontal, though this
 * is not enforced in this object (see ShipBoardBuilder, the sole authority on
 * placing Ships).
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

    
    virtual ShipStatus status() const = 0;




    /**
     * Get the current status of the ship, i.e. if it is floating or has been sunk.
     * Sank ships cannot be hit again.
     * 
     * @return ShipStatus the current status of the ship
     */
    virtual ShipStatus status() const = 0;

    // /**
    //  * Returns the position of this segment of the ship.
    //  * Most ships span multiple cells; this method only 
    //  * returns the cell that this node occupies.
    //  * 
    //  * @return the position of this ship node or null if unplaced
    //  */
    // virtual Point at() const = 0;

    /**
     * Returns the head of this ship.
     * This is only really necessary information
     * when first placing the ships on the board during setup.
     * The head's position will always be in either the same row
     * or column as this ship.
     * If this is the head of the ship, returns itself.
     * 
     * @return Ship const reference to head of this ship
     */
    virtual const Ship& head() const = 0;

    // /**
    //  * Returns if this whole ship is horizontal or not,
    //  * used to determine this ship's orientation.
    //  * If this ship is of size 1, this is arbitrary.
    //  * 
    //  * @return true the ship is horizontal
    //  * @return false the ship is vertical.
    //  */
    // virtual bool horizontal() const = 0;

    virtual ~Ship() = default;
};

#endif
