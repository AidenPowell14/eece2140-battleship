#include "include/Controller.h"
#include "include/Model.h"
#include "include/ShipReader.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Program expects arguments for board size and ship files for both players.\n";
        return 1;
    }
    auto model = Model();
    Controller controller(model);
    model.setListener(&controller);
    try {
        controller.preface();
        model.start(std::stoi(argv[1]), std::stoi(argv[2]), ShipReader::read(argv[3]), ShipReader::read(argv[4]));
    } catch (const IllegalOperation& badArgs) {
        std::cout << "Failed to start game. " << badArgs.what() << ". Exiting...\n";
        return 1;
    }
    return 0;
}