#pragma once
#include "Meld.h"
#include "Triplet.h"

class Kan : public Meld {
private:
	std::array<Tile, 4> tiles;
public:
	Kan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4, TileMarker marker);
	int size() const override;
	const Tile& operator[](int index) const override;
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
	virtual std::string getContents() const override;
	~Ankan() = default;
};

//open kan
class Daiminkan : public Kan {
public:
	Daiminkan(const Tile& externalTile, const Tile& tile2,
		const Tile& tile3, const Tile& tile4, TileMarker marker);
	virtual std::string getContents() const override;
	~Daiminkan() = default;
};


//added kan
class Shouminkan : public Kan {
public:
	Shouminkan(const Tile& ExternalTile, std::unique_ptr<Pon> pon);
	virtual std::string getContents() const override;
	~Shouminkan() = default;
};