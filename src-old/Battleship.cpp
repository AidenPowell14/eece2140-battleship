#include "model/BasicGameModel.h"
#include "model/BasicShip.h"
#include <iostream>

int main() {
    BasicGameModel model = BasicGameModel();

    std::vector<Ship*> redShips;
    std::vector<Ship*> blueShips;
    auto ship5 = BasicShip(5);
    auto ship3 = BasicShip(3);
    redShips.push_back(&ship5);
    blueShips.push_back(&ship3);

    auto builder = model.start(10, 10, redShips, blueShips);
    builder->setShip(Color::RED, ship5, Point{1, 1}, false);

    for (int i = 0; i < model.getShips(Color::RED).rows(); i++) {
        for (int j = 0; j < model.getShips(Color::RED).cols(); j++) {
            std::cout << (1 == 0) << std::endl;
            std::cout << ((model.getShips(Color::RED).get(Point{i, j})) == nullptr) << std::endl;
        }
    }

}