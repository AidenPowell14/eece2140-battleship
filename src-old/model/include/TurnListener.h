#ifndef TURN_LISTENER_H
#define TURN_LISTENER_H

#include "../../data/Color.h"

/**
 * Controller interface for messaages from the GameModel. The model
 * may publish to the controller about if a new player should start their
 * turn, or when a player successfully destroys one of their opponent's ships.
 */
class TurnListener {
    public:

    /**
     * Notify the controller that a new player has started their turn. 
     * A turn consists of a position prompt, and a reported
     * outcome from striking that position.
     * 
     * @param player the player whose turn it now is
     */
    virtual void newActivePlayer(Color player) = 0;

    /**
     * Notify the controller that the specified player has lost a 
     * complete battleship: "you sunk my battleship!" This information 
     * should be relayed to opposite (striking) player.
     * 
     * @param player the player who lost a ship
     */
    virtual void battleShipSunk(Color player) = 0;

    virtual ~TurnListener() = default;
};

#endif