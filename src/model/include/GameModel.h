#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <vector>
#include "Ship.h"
#include "../../data/Color.h"
#include "../../data/HitStatus.h"
//#include "ShipBoardBuilder.h"
#include "HitBoard.h"
//#include "ShipBoard.h"
//#include "TurnListener.h"

#define MAX_SHIP_RATIO 0.5

/**
 * Comprehensive model interface for the game of Battleship. Core logic involves
 * player interaction with a HitBoard, representing all attempted hits,
 * and a ShipBoard, representing all of their own ships and their current statuses.
 * Starting the game entails one-time ship placement (handled by the ShipBoardBuilder)
 * followed by a series of back and forth attempts to guess the positions of the other player's
 * ships. The game ends when one player has all of its ships completely sunk.
 */
class GameModel {
    public:

    /**
     * Starts the game with the specified configuration of the board and ships.
     * The returned ShipBoardBuilder kicks off ship placement on the ShipBoard.
     * Once the placement phase is complete, subsequent turns will be handled outside of this method.
     * For each player, the sum of all of their ship's sizes must be at most MAX_SHIP_RATIO of the total area of 
     * the board. This ensures the player will be able to comfortably place all of their ships
     * 
     * @param rows the number of rows to play with
     * @param cols the number of columns to play with
     * @param redShips a list of ships for the red player to play with
     * @param blueShips a list of ships for the blue player to play with
     * @return ShipBoardBuilder builder object to conduct ship placement through
     * @throws std::invalid_argument if the board can't be created, or there are too many
     * or too few (namely zero) ships to play with
     */
    virtual ShipBoardBuilder start(int rows, int cols, std::vector<Ship> redShips, std::vector<Ship> blueShips) = 0;

    /**
     *  Returns the active player who should be making a move.
     * 
     * @return Color of active player
     */
    virtual Color getActivePlayer() const = 0;

    /**
     * Checks if the game is over or not. The game is over when
     * either player has all of their ships sunk.
     * 
     * @return true the game is over
     * @return false the game is not over
     */
    virtual bool isGameOver() const = 0;

    /**
     * Sends a missile toward the non-active player at the specified point.
     * The outcome of the strike is contained in the return type. All strikes,
     * whether a hit or a miss, will update the attacking player's HitBoard.
     * In the case of a hit, the victim's ShipBoard will also be updated with the 
     * damage on their ship. If a strike hits a ship's last unsunk segment, 
     * that battleship is sunk, and the Controller is notified accordingly.
     * A player cannot strike the same position twice.
     * 
     * @param position the position to strike
     * @return HitStatus the status of the strike (hit or miss)
     * @throws std::invalid_argument if the position does not exist,
     * or this position has been struck before
     */
    virtual HitStatus strike(Point position) = 0;

    /**
     * Retrieves the HitBoard for the specified player.
     * The HitBoard contains all the player's information about 
     * their own strikes on the opposing player. Effectively, this 
     * will be a grid of hits, misses, or null.
     * 
     * @param player the player whose HitBoard should be retrieved
     * @return const HitBoard& reference to that player's HitBoard
     */
    virtual const HitBoard& getHits(Color player) = 0;

    /**
     * @brief Retrieves the ShipBoard for the specified player.
     * The ShipBoard contains all the player's information about
     * their own Ships and their status as floating or sinking.
     * Since Ships often occupy more than a single grid cell,
     * this board will contain many one-celled segments of ships.
     * 
     * @param player  the player whose ShipBoard should be retrieved
     * @return const ShipBoard& reference to that player's ShipBoard
     */
    virtual const ShipBoard& getShips(Color player) = 0;

    /**
     * Sets a listener to this model that can receive publications about player actions, 
     * namely the start of a new player's turn and if a player's ship has been sunk
     * ("You sunk my battleship!").
     *
     * @param controller the controller to subscribe to this model
     */
    virtual void setListener(TurnListener* controller) = 0;
};

#endif