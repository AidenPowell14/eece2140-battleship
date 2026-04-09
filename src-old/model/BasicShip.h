#ifndef BASIC_SHIP_H
#define BASIC_SHIP_H

#include "include/Ship.h"

class BasicShip : public Ship {
    private:

    const int totalSize;
    int totalHits = 0;
    ShipStatus shipStatus = ShipStatus::FLOAT;

    public:
    
    BasicShip(int size);

    int size() const override;

    int hits() const override;

    ShipStatus status() const override;

    ShipStatus takeHit() override;

    ~BasicShip();
};

#endif