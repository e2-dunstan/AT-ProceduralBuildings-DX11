#pragma once
#include "DXApp.h"

class BuildingGenerator
{
public:
	BuildingGenerator() = default;
	~BuildingGenerator() = default;

	void Init();
	void InitWalls();
	void InitCorners();
	void InitFloors();

	void ClearVectors();

	std::vector<Model*> GetModels();

private:
	std::vector<Model*> models;

	std::vector<Model*> walls;
	std::vector<Model*> corners;
	std::vector<Model*> floors;

	//these will be user defined
	int buildingWidth = 6;
	int buildingHeight = 3;
	int buildingDepth = 6;
	float wallWidth = 5;
	float wallHeight = 5;
	float wallDepth = 1; //don't allow to be greater than wall width
};