#include "BasicShipNode.h"

BasicShipNode::BasicShipNode(Ship& ship) : ship(ship) {}

const Ship& BasicShipNode::getShip() const {
    return ship;
}

ShipStatus BasicShipNode::strike() {
    if (status == ShipStatus::FLOAT) {
        status = ShipStatus::SUNK;
        return ship.takeHit();
    }
    return ship.status();
}

BasicShipNode::~BasicShipNode() {}