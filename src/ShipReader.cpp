#include "include/ShipReader.h"
#include "include/data.h"
#include <fstream>
#include <iostream>

const std::vector<int> ShipReader::read(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw IllegalOperation("Unable to open file");
    }
    std::vector<int> ships;
    std::string size;
    while (file >> size) {
        try {
            ships.push_back(std::stoi(size));
        } catch (const std::invalid_argument& badNum) {
            throw IllegalOperation("Ship file includes some non-integers");
        }
    }
    file.close();
    return ships;
}