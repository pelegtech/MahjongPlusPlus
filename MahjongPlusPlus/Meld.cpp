#include "Meld.h"

Meld::Meld(TileMarker marker, MeldType type): marker(marker), type(type){}

TileMarker Meld::getTileMarker() const{
	return marker;
}

std::ostream& operator<<(std::ostream& os, const Meld& meld) {
	os << meld.getContents();
	return os;
}




