#include "BasicShip.h"
#include <stdexcept>

BasicShip::BasicShip(int size) : totalSize(size) {}

int BasicShip::size() const {
    return totalSize;
}

int BasicShip::hits() const {
    return totalHits;
}

ShipStatus BasicShip::status() const {
    return shipStatus;
}

ShipStatus BasicShip::takeHit() {
    if (shipStatus == ShipStatus::SUNK) {
        throw std::invalid_argument("Ship has already been sunk");
    }
    totalHits++;
    if (totalHits >= totalSize) {
        shipStatus = ShipStatus::SUNK;
    }
    return shipStatus;
}

BasicShip::~BasicShip() {}