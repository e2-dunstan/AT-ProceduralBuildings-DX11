#pragma once
#include <random>
#include "Model.h"
#include"OBJImporter.h"

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

class Interiors
{
public:
	Interiors(
		int bwidth, int bheight, int bdepth, 
		float wwidth, float wheight, float wdepth, int b_floor);
	~Interiors();

	void InitWalls();
	void CreateWalls(std::mt19937 seed);
	void CreateWallModels(Wall* w1, Wall* w2);
	//void CreateObjects();
	//void Divide(int rot);
	//int GetValidPosition(std::uniform_int_distribution<int> dist, int rot);

	std::vector<Model*> GetWalls();

private:
	int currentWidth;
	int currentDepth;
	int floor;

	//OBJImporter* objImporter;

	std::random_device generator;

	std::vector<Model*> walls;
	//Model* bedModel;

	int b_buildingWidth = 5;
	int b_buildingHeight = 2;
	int b_buildingDepth = 6;
	float b_wallWidth = 6;
	float b_wallHeight = 8;
	float b_wallDepth = 1;

	float doorWidth = 4;

	int xOffset = 0;
	int zOffset = 0;

	std::vector<int> previousX;
	std::vector<int> previousZ;

	Room* room1;
	Room* room2;
	Room* room3;

	//std::string bed = "Resources/bed.obj";
	//std::string table = "Resources/table.obj";
};