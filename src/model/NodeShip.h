#ifndef NODE_SHIP_H
#define NODE_SHIP_H

#include "include/Ship.h"

/**
 * Implementation of Ships in Battleship using nodes to occupy 
 * multiple cell entries in the ShipBoard.
 */
class NodeShip : public Ship {
    private:

    int size;
    int hitsTaken;
    ShipStatus status;
    Ship* head;

    public:
    
    /**
     * Construct a new NodeShip object by specifying its size.
     * This is intended for creating the first 
     * 
     * @param size 
     */
    NodeShip(int size);
    NodeShip(Ship& head);

    int size() const override;
    int hits() const override;
    ShipStatus status() const override;
    //Point at() const override;
    Ship& head() const override;
    //bool horizontal() const override;
};

#endif