#pragma once
#include <string>

class Tile {
private:
    std::string name;

public:
    Tile(std::string tileName);

    std::string GetName();
};