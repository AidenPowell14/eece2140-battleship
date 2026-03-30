#ifndef HIT_BOARD_H
#define HIT_BOARD_H

#include "../../data/Color.h"
#include "../../data/HitStatus.h"
#include "../../data/Point.h"

/**
 * Interface for a player's personal data about where they have fired at previously,
 * and whether those strikes have been successful or not. This corresponds to the upper
 * board on a traditional Battleship setup. Points on this board can contain a HitStatus 
 * if they have been struck, or null if they haven't been yet. Non-null points cannot be
 * struck again.
 */
class HitBoard {
    public:
    
    /**
     * Retrieves the owner of this HitBoard.
     * 
     * @return Color of the owning player
     */
    virtual Color getOwner() const = 0;

    /**
     * Retrieves the current status of a position on the opponent's field.
     * If this player has fired a missile to this position, this will return 
     * whether that strike resulted in a hit or a miss. Otherwise, if no missile
     * has been fired here, return null.
     * 
     * @param position the position to check the status of 
     * @return HitStatus whether this point has been struck, and if so, if it was a hit or miss
     * @throws std::invalid_argument if the position does not exist
     */
    virtual HitStatus get(Point position) const = 0;

    /**
     * Updates the specified position with the specified status.
     * Intended for updating a player's HitBoard following a strike on the opposing player.
     * 
     * @param position the position to set a status at
     * @param status the status to set at this point (hit or miss)
     * @throws std::invalid_argument if the point does not exist
     */
    virtual void struck(Point position, HitStatus status) = 0;

    virtual ~HitBoard() = default;
};

#endif