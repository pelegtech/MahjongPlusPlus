#pragma once
#include "Meld.h"


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
