#ifndef COLOR_H
#define COLOR_H

/**
 * Simple enum representing the player designations in Battleship.
 */
enum Color {
    RED,
    BLUE
};

class ColorOther {
    public:
    static const Color other(Color player) {
        return player == Color::RED ? Color::BLUE : Color::RED;
    }
};

#endif