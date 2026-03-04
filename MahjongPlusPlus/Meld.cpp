#include "Meld.h"

Meld::Meld(TileMarker marker): marker(marker){}

TileMarker Meld::getTileMarker() const{
	return marker;
}

std::ostream& operator<<(std::ostream& os, const Meld& meld) {
	os << meld.getContents();
	return os;
}




