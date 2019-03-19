#pragma once
#include <random>
#include "Model.h"

//struct InteriorWall
//{
//	InteriorWall(float x, float z, 
//		int r, int dr, int w)
//		: posX(x), posZ(z), 
//		rot(r), door(dr), width(w) {}
//	float posX;
//	float posZ;
//	int rot;
//	int door;
//	int width;
//};

struct Room
{
	Room(int x, int z, int w, int d)
		: originX(x), originZ(z),
		width(w), depth(d) {}
	int originX;
	int originZ;
	int width;
	int depth;
};
struct Wall
{
	Wall(int x, int z, int l, int d)
		: originX(x), originZ(z),
		length(l), doorLoc(d){}
	int originX;
	int originZ;
	int length;
	int doorLoc;
};

class InteriorWalls
{
public:
	InteriorWalls(
		int bwidth, int bheight, int bdepth, 
		float wwidth, float wheight, float wdepth, int b_floor);
	~InteriorWalls();

	void InitWalls();
	void CreateWalls();
	//void Divide(int rot);
	//int GetValidPosition(std::uniform_int_distribution<int> dist, int rot);

	std::vector<Model*> GetWalls();

private:
	int currentWidth;
	int currentDepth;
	int floor;

	std::default_random_engine generator;

	std::vector<Model*> walls;

	int b_buildingWidth = 5;
	int b_buildingHeight = 2;
	int b_buildingDepth = 6;
	float b_wallWidth = 6;
	float b_wallHeight = 8;
	float b_wallDepth = 1;

	int xOffset = 0;
	int zOffset = 0;

	std::vector<int> previousX;
	std::vector<int> previousZ;
};