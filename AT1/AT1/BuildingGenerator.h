#pragma once
#include "DXApp.h"

class BuildingGenerator
{
public:
	BuildingGenerator() = default;
	~BuildingGenerator() = default;

	void Init();
	void InitWalls();
	void InitWindowsAndDoor(float height);
	void InitCorners();
	void InitFloors();
	//void InitDoor();

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
	int buildingDepth = 5;
	float wallWidth = 5;
	float wallHeight = 5;
	float wallDepth = 1; //don't allow to be greater than wall width

	int numWindowsOnWidth = 4;
	int numWindowsOnDepth = 3;
	float windowWidth = 3;
	float windowHeight = 3;
	float windowDepth = 2;

	float doorWidth = 2;
	float doorHeight = 5;
	float doorDepth = 2;
};