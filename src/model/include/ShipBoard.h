#ifndef SHIP_BOARD_H
#define SHIP_BOARD_H

#include "../../data/Color.h"
#include "../../data/Point.h"
#include "../../data/HitStatus.h"
//#include "ShipNode.h"

/**
 * Interface for a player's personal data about where their own ships are, and if
 * they have been damaged by the opponents strikes or not. This corresponds to the lower
 * board on a traditional Battleship setup. Since Ships often occupy more than one cell
 * of the grid, each cell contains a segment of a Ship, called a ShipNode, which can be
 * used to inspect the HitStatus of either that node or the overarching Ship that it belongs to.
 * Wherever on the board that is not occupied by a ShipNode is null. There is no way to save
 * data about an opponent's missed strikes.
 */
class HitBoard {
    public:
    
    /**
     * Retrieves the owner of this ShipBoard.
     * 
     * @return Color of the owning player
     */
    virtual Color getOwner() const = 0;

    /**
     * Retrieves the ShipNode at the specified position. ShipNodes contain
     * data regarding what Ship it belongs to, and if it has been hit already or not.
     * If there is no ShipNode here, returns null
     * 
     * @param position the position get the ShipNode of
     * @return const ShipNode& reference to the ShipNode at this position, or null if there isn't one
     * @throws std::invalid_argument if the position does not exist
     */
    virtual const ShipNode& get(Point position) const = 0;

    /**
     * Sends a missile to the specified position on this ShipBoard
     * 
     * @param position the position to set a status at
     * @param status the status to set at this point (hit or miss)
     * @throws std::invalid_argument if the point does not exist
     */
    virtual HitStatus strike(Point position) = 0;

};

#endif