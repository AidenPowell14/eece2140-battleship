#ifndef SHIP_NODE_H
#define SHIP_NODE_H

#include <vector>
#include "../data/ShipStatus.h"

class ShipNode {
    private:

    ShipStatus status;
    const ShipNode& head;

    public:
    
    ShipNode(ShipNode& head);

};

class Ship {
    private:

    const ShipNode head;
    const std::vector<ShipNode>& nodes;

    int size;
    int hits;

    public:

    Ship(const std::vector<ShipNode>& nodes);

    int hits();

    int size();

    const std::vector<ShipNode>& getNodes();

    const ShipNode

};

#endif