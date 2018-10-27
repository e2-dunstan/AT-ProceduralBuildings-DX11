#pragma once
#include "DXApp.h"

class BuildingGenerator
{
public:
	BuildingGenerator() = default;
	~BuildingGenerator();

	void Init();
	void InitWalls();
	void InitWindowsAndDoor(float height);
	void InitCorners();
	void InitFloors();
	void InitRoof();

	void ClearVectors();

	std::vector<Model*> GetModels();

private:
	std::vector<Model*> models;

	std::vector<Model*> walls;
	std::vector<Model*> windows;
	std::vector<Model*> corners;
	std::vector<Model*> floors;
	Model* door;

	//these will be user defined
	int buildingWidth = 5;
	int buildingHeight = 3;
	int buildingDepth = 6;
	float wallWidth = 6;
	float wallHeight = 8;
	float wallDepth = 1; //don't allow to be greater than wall width

	int numWindowsOnWidth = 3;
	int numWindowsOnDepth = 4;
	float windowWidth = 3;
	float windowHeight = 4;
	float windowDepth = 2;

	float doorWidth = 2;
	float doorHeight = 5;
	float doorDepth = 2;

	int roofType = 1;
	float roofOverhang = 4;
	float roofHeight = 2;
};