#ifndef BASIC_HIT_BOARD_H
#define BASIC_HIT_BOARD_H

#include "include/HitBoard.h"
#include <vector>

class BasicHitBoard : public HitBoard {
    private:

    Color owner;

    int rows;
    int cols;
    std::vector<std::vector<HitStatus>> board;

    public:
    BasicHitBoard(Color owner, int rows, int cols);

    Color getOwner() const override;

    HitStatus get(Point position) const override;

    void struck(Point position, HitStatus status) override;

    ~BasicHitBoard();
};

#endif