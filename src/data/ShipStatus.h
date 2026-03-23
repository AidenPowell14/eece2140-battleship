#ifndef SHIP_STATUS_H
#define SHIP_STATUS_H

/**
 * Enum representing the two possible statuses of a ship in Battleship.
 * It can either be floating, or sank. Ships are sank by successfully
 * being struck at every node.
 */
enum ShipStatus {
    FLOATING,
    SANK
};

#endif