#ifndef BASIC_SHIP_NODE_H
#define BASIC_SHIP_NODE_H

#include "include/ShipNode.h"
#include "include/Ship.h"

class BasicShipNode : public ShipNode {
    private:

    Ship& ship;
    ShipStatus status  = ShipStatus::FLOAT;

    public:

    BasicShipNode(Ship& ship);

    const Ship& getShip() const override;

    ShipStatus strike() override;
};

#endif