#ifndef SHIP_NODE_H
#define SHIP_NODE_H

#include "Ship.h"
#include "../../data/ShipStatus.h"

/**
 * Interface for a segment of a Ship, which only occupies a single tile in on
 * a player's ShipBoard grid. ShipNodes are aware of their owning Ships, but not
 * the other way around. All action (i.e. strikes over the course of the game)
 * must interface with ShipNodes, not Ships, since those are what exist on the board.
 */
class ShipNode {
    public:
    
    /**
     * Retrives the ship that this node is a member of.
     * 
     * @return const Ship& reference to the parent Ship
     */
    virtual const Ship& getShip() const = 0;

    /**
     * Lands a missile on this ShipNode, becoming a "sunk" node.
     * Additionally, checks if sinking this node would result in 
     * the sinking of the entire ship, and as such returns the status 
     * of the entire ship.
     * Though the scenario should not arise, striking the same node twice
     * should not have any duplicated effect on the overarching Ship.
     * 
     * @return ShipStatus the status of the entire Ship that includes this node.
     */
    virtual ShipStatus strike() = 0;

    virtual ~ShipNode() = default;
};

#endif