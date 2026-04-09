#ifndef SHIP_READER_H
#define SHIP_READER_H

#include <vector>
#include <string>

class ShipReader {
    private:

    public:
    
    ShipReader() = delete; // prevents instantiation

    static const std::vector<int> read(std::string filename);
};

#endif