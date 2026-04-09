#ifndef DATA_H
#define DATA_H

#include <memory>
#include <stdexcept>

struct Point {
    int row;
    int col;
};

enum Color {
    RED,
    BLUE
};

// inline Color otherColor(Color player) {
//     return player == Color::RED ? Color::BLUE : Color::RED;
// }

enum HitStatus {
    NONE,
    MISS,
    HIT
};

struct IllegalOperation : std::runtime_error {
    using std::runtime_error::runtime_error;
};

#endif