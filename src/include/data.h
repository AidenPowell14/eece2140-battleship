#ifndef DATA_H
#define DATA_H

#include "ShipBoard.h"
#include "HitBoard.h"
#include <memory>

struct Point {
    int row;
    int col;
};

bool betweenRow(Point test, int a, int b) {
    return (test.row > a && test.row < b) || (test.row < a && test.row > b);
}

bool betweenCol(Point test, int a, int b) {
    return (test.col > a && test.col < b) || (test.col < a && test.col > b);
}

enum Color {
    RED,
    BLUE
};

struct Profile {
    Color player;
    std::unique_ptr<ShipBoard> shipBoard;
    std::unique_ptr<HitBoard> hitBoard;
};

enum HitStatus {
    NONE,
    MISS,
    HIT
};

#endif