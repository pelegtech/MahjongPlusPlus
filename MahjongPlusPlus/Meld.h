#pragma once
#include <array>
#include "Tile.h"
#include <stdexcept>
#include "Player.h"
enum class TileMarker {
	SELF,
	LEFT,
	MIDDLE,
	RIGHT
};


class Meld {
private:
	TileMarker marker;
public:
	Meld(TileMarker marker); 
	virtual ~Meld()  = default;
	virtual Tile operator[](int index) const = 0;
	TileMarker getTileMarker() const;
};

class Triplet : public Meld {
private:
	std::array<Tile, 3> tiles;
public:
	Triplet(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker);
	Tile operator[](int index) const override;
	virtual ~Triplet() = default; 
};

class Pon : public Triplet {
public:
	Pon(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker);
	~Pon() override = default;
	static bool isPon(const Tile& t1, const Tile& t2, const Tile& t3);

	class notPon : public std::exception {
		const char* what() const noexcept override {
			return "pon must only contain three identical tiles";
		}
	};
};

class Chi : public Triplet {
public:
	Chi(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker);
	~Chi() override = default;
	static bool isChi(const Tile& t1, const Tile& t2, const Tile& t3);


	class notChi : public std::exception {
		const char* what() const noexcept override {
			return "chi must  contain a sequence of three consecutive tiles";
		}
	};
};

class Kan : public Meld {
private:
	std::array<Tile, 4> tiles;
public:
	Kan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4, TileMarker marker);
	Tile operator[](int index) const override;
	virtual ~Kan() = default;
	static bool isKan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4);

	class notKan : public std::exception {
		const char* what() const noexcept override {
			return "kan must contain four identical tiles";
		}
	};
};

//closed kan
class Ankan : public Kan {
public:
	Ankan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4);
	~Ankan() = default;
};

//open kan
class Daiminkan : public Kan {
public:
	Daiminkan(const Tile& externalTile, const Tile& tile2, const Tile& tile3, const Tile& tile4, TileMarker marker);
	~Daiminkan() = default;
};
 

//added kan
class Shouminkan : public Kan {
public:
	Shouminkan(const Tile& ExternalTile,const Pon& pon);
	~Shouminkan() = default;
};