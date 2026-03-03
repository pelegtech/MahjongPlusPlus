#include "Tile.h"

Tile::Tile(std::string tileName) {
    name = tileName;
}

std::string Tile::GetName() {
    return name;
}