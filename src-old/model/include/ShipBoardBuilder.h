#ifndef SHIP_BUILDER_H
#define SHIP_BUILDER_H

#include "../../data/Color.h"
#include "../../data/Point.h"
#include "Ship.h"
#include "ShipBoard.h"
#include <vector>

/**
 * Interface for a one-time-use builder class used to configure each player's 
 * ShipBoards. This builder should only ever be used during the start of the game, 
 * and will become nonfunctional after both boards have been created. Submitting boards
 * makes them henceforth immutable.
 */
class ShipBoardBuilder {
    public:

    /**
     * Places the specified ship at the position on the player's ShipBoard.
     * The entered position refers to the leftmost or topmost point of the 
     * ship, depending on the orientation specified.
     * It will be in this method that many ShipNodes are instantiated from a 
     * single Ship's data.
     *
     * @param player the owner of the ShipBoard being placed to
     * @param ship the ship to place
     * @param position the leftmost or topmost point to place to
     * @param horizontal if the ship should be placed horizontally or not
     * @throws std::invalid_argument if the point does not exist, or the ship does
     * not fit in bounds for the given position
     */
    virtual void setShip(Color player, Ship& ship, Point position, bool horizontal) = 0;

    /**
     * Confirms that the ShipBoard is complete for the designated player.
     * Once this method is called, the ShipBoard is completely fixed 
     * in its positions, only able to update the state of each ShipNode within.
     *
     * @param player the player to seal the ShipBoard of
     */
    virtual void submit(Color player) = 0;

    /**
     * Removes the ship that occupies this position, and collects them for replacement.
     * Intended only as an "undo" button during initial placement. The inputted point 
     * may be any point that is contained in a full Ship, so it is this method's 
     * responsibility to remove all relevant ShipNodes.
     * 
     * @param player the owner of the board to remove from
     * @param position the position to remove from
     * @throws std::invalid_argument if the position does not exist
     */
    //virtual void removeShip(Color player, Point position) = 0;

    /**
     * Return a list of all of a player's ships that they must place.
     * This list is immutable, and does not reflect the ships not yet placed.
     * 
     * @param player the player to check the inventory of 
     * @return std::vector<Ship> all of that player's ships in play
     */
    virtual const std::vector<Ship*>& getShips(Color player) const = 0;

    virtual ~ShipBoardBuilder() = default;

};

#endif