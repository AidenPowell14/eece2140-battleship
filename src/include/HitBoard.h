#ifndef HIT_BOARD_H
#define HIT_BOARD_H

#include "data.h"
#include <memory>
#include <vector>

class HitBoard {
    private:

    std::vector<std::vector<HitStatus>> board;

    const Color owner;

    const int numRows;
    const int numCols;

    public:

    HitBoard(Color player, int rows, int cols);

    const std::vector<std::vector<HitStatus>>& get();

    HitStatus get(Point pos);

    void struck(Point pos, HitStatus status);

    ~HitBoard();
};

#endif