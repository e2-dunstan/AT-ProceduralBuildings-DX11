#pragma once
#include <random>

struct InteriorWall
{
	InteriorWall(int p, int r, int d)
		: pos(p), rot(r), door(d) {}
	int pos;
	int rot;
	int door;
};

class InteriorWalls
{
public:
	InteriorWalls(int x, int y);
	~InteriorWalls() = default;

	void InitWalls();
	void Divide(int w, int h);

	std::vector<InteriorWall> GetWalls();

private:
	int width;
	int height;

	std::default_random_engine generator;

	std::vector<InteriorWall> walls;
};