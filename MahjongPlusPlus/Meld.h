#pragma once
#include <array>
#include "Tile.h"
#include <stdexcept>
#include <string>
#include "GameTypes.h"

class Meld {
private:
	TileMarker marker;
public:
	Meld(TileMarker marker); 
	virtual int size() const = 0;
	virtual ~Meld()  = default;
	virtual const Tile& operator[](int index) const = 0;
	TileMarker getTileMarker() const;
	static constexpr int KAN_SIZE = 4;
	static constexpr int TRIPLET_SIZE = 3;
	virtual std::string getContents() const = 0;
	friend std::ostream& operator<<(std::ostream& os, const Tile& tile);
};

class Triplet : public Meld {
private:
	std::array<Tile, 3> tiles;
public:
	Triplet(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker);
	int size() const override;
	const Tile& operator[](int index) const override;
	virtual ~Triplet() = default; 
};

class Pon : public Triplet {
public:
	Pon(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker);
	~Pon() override = default;
	static bool isPon(const Tile& t1, const Tile& t2, const Tile& t3);
	virtual std::string getContents() const override;

	class notPon : public std::exception {
	public:
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
	virtual std::string getContents() const override;


	class notChi : public std::exception {
	public:
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
	int size() const override;
	const Tile& operator[](int index) const override;
	virtual ~Kan() = default;
	static bool isKan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4);
	virtual std::string getContents() const override;

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
	Shouminkan(const Tile& ExternalTile,std::unique_ptr<Pon> pon);
	~Shouminkan() = default;
};