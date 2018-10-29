#include "BuildingGenerator.h"
#include <random>

BuildingGenerator::~BuildingGenerator()
{
	models.clear();
	TwTerminate();
	ClearVectors();
}

void BuildingGenerator::InitTweakBar(Renderer & renderer)
{
	TwInit(TW_DIRECT3D11, renderer.GetDevice());
	tweakBar = TwNewBar("Customise");
	TwWindowSize(200, 400);
	int tweakBarSize[2] = { 200, 400 };
	TwSetParam(tweakBar, NULL, "size", TW_PARAM_INT32, 2, tweakBarSize);
	
	TwAddVarRW(tweakBar, "Building Width", TW_TYPE_INT32, &buildingWidth, "Group='Structure' min=1 max=20 step=1");
}

void BuildingGenerator::Init()
{
	models.push_back(new Model(Type::FLOOR,
		1000, 0, 1000,
		0, -(wallHeight + 0.2f) / 2, 0, 0));

	InitRoof();
	InitWalls();
	InitCorners();
	InitFloors();

	ClearVectors();
}

void BuildingGenerator::InitWalls()
{
	for (int h = 0; h < buildingHeight; h++)
	{
		float w_height = h * wallHeight;

		for (int w = 0; w < buildingWidth; w++)
		{
			//Wall 1
			walls.push_back(new Model(Type::WALL,
				wallWidth, wallHeight, wallDepth,
				(wallWidth * w) + (wallDepth / 2) + (wallWidth / 2),
				w_height,
				0,
				0));
			//Wall 2
			walls.push_back(new Model(Type::WALL,
				wallWidth, wallHeight, wallDepth,
				(wallWidth * w) + (wallDepth / 2) + (wallWidth / 2),
				w_height,
				(wallWidth * buildingDepth) + wallDepth,
				0));
		}
		for (int d = 0; d < (buildingDepth); d++)
		{
			//Wall 3
			walls.push_back(new Model(Type::WALL,
				wallWidth, wallHeight, wallDepth,
				0,
				w_height,
				(wallWidth * d) + (wallDepth / 2) + (wallWidth / 2),
				90));
			//Wall 4
			walls.push_back(new Model(Type::WALL,
				wallWidth, wallHeight, wallDepth,
				(wallWidth * buildingWidth) + wallDepth,
				w_height,
				(wallWidth * d) + (wallDepth / 2) + (wallWidth / 2),
				90));
		}
		// -- CREATE WINDOWS -- //
		InitWindowsAndDoor(w_height);
	}

	for (int w = 0; w < walls.size(); w++)
	{
		models.push_back(walls[w]);
	}
	for (int win = 0; win < windows.size(); win++)
	{
		//THIS IS TEMPERMENTAL
		if (windows[win]->GetPosition().x == door->GetPosition().x
			&& windows[win]->GetPosition().z == door->GetPosition().z
			&& windows[win]->GetPosition().y == 0)
		{
			models.push_back(door);
		}
		else
		{
			models.push_back(windows[win]);
		}
	}
}

void BuildingGenerator::InitWindowsAndDoor(float height)
{
	//invalid number of windows or no windows
	if (numWindowsOnWidth > buildingWidth
		|| numWindowsOnDepth > buildingDepth)
	{
		return;
	}
	float gapBetween;

	// -- CREATE DOOR -- //
	//Gets a random location on a wall
	if (height == 0)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> d(0, (numWindowsOnDepth * 2)); //define the range

		int width;
		int depth = d(eng);

		float rot = 0;

		if (depth == numWindowsOnDepth || depth == 0)
		{
			std::uniform_int_distribution<> w(1, (numWindowsOnWidth * 2));
			width = w(eng);
			gapBetween = (wallWidth * buildingWidth) / numWindowsOnWidth;
			if (width > numWindowsOnWidth)
				width -= numWindowsOnWidth;
			
			width = width * gapBetween + (wallDepth / 2) + (gapBetween / 2);

			if (depth == numWindowsOnDepth)
				depth = (wallWidth * numWindowsOnDepth) + wallDepth;

			rot = 0;
		}
		else
		{
			std::uniform_int_distribution<> w(0, 2);
			width = w(eng) * ((wallWidth * buildingWidth) + wallDepth);
			gapBetween = (wallWidth * buildingDepth) / numWindowsOnDepth;

			if (depth > numWindowsOnDepth)
				depth -= numWindowsOnDepth;
			depth = gapBetween * depth + (wallDepth / 2) + (gapBetween / 2);
			rot = 90;
		}

		door = new Model(Type::DOOR,
			doorWidth, doorHeight, doorDepth,
			width,
			0,
			depth,
			rot);
	}

	// -- WINDOWS -- //
	//For opposite walls
	for (int d = 0; d < 2; d++)
	{
		float gapBetween;
		if (numWindowsOnWidth != 0)
		{
			gapBetween = (wallWidth * buildingWidth) / numWindowsOnWidth;
			for (int i = 0; i < numWindowsOnWidth; i++)
			{
				windows.push_back(new Model(Type::WINDOW,
					windowWidth, windowHeight, windowDepth,
					gapBetween * i + (wallDepth / 2) + (gapBetween / 2),
					height,
					((wallWidth * buildingDepth) + wallDepth) * d,
					0));
			}
		}
		if (numWindowsOnDepth != 0)
		{
			gapBetween = (wallWidth * buildingDepth) / numWindowsOnDepth;
			for (int j = 0; j < numWindowsOnDepth; j++)
			{
				windows.push_back(new Model(Type::WINDOW,
					windowWidth, windowHeight, windowDepth,
					((wallWidth * buildingWidth) + wallDepth) * d,
					height,
					gapBetween * j + (wallDepth / 2) + (gapBetween / 2),
					90));
			}
		}
	}
}

void BuildingGenerator::InitCorners()
{
	float c_height = wallHeight * (buildingHeight / 2);
	//If building height is even
	if (buildingHeight % 2 == 0)
	{
		c_height -= wallHeight / 2;
	}

	//0,0
	corners.push_back(new Model(Type::CORNER, 
		wallDepth, wallHeight * buildingHeight, wallDepth,
		0,
		c_height,
		0, 
		0));
	//1,0
	corners.push_back(new Model(Type::CORNER, 
		wallDepth, wallHeight * buildingHeight, wallDepth,
		(wallWidth * buildingWidth) + wallDepth,
		c_height,
		0, 
		0));
	//0,1
	corners.push_back(new Model(Type::CORNER, 
		wallDepth, wallHeight * buildingHeight, wallDepth,
		0, 
		c_height,
		(wallWidth * buildingDepth) + wallDepth,
		0));
	//1,1
	corners.push_back(new Model(Type::CORNER, wallDepth, wallHeight * buildingHeight, wallDepth,
		(wallWidth * buildingWidth) + wallDepth,
		c_height,
		(wallWidth * buildingDepth) + wallDepth,
		0));

	for (int c = 0; c < corners.size(); c++)
	{
		models.push_back(corners[c]);
	}
}

void BuildingGenerator::InitFloors()
{
	float floorWidth = buildingWidth * wallWidth;
	float floorDepth = buildingDepth * wallWidth;

	for (int f = 0; f < buildingHeight; f++)
	{
		floors.push_back(new Model(Type::FLOOR, floorWidth, 0, floorDepth,
			(floorWidth / 2) + (wallDepth / 2),
			(wallHeight * f) - (wallHeight / 2),
			(floorDepth / 2) + (wallDepth / 2),
			0));
	}

	for (int f = 0; f < floors.size(); f++)
	{
		models.push_back(floors[f]);
	}
}

void BuildingGenerator::InitRoof()
{
	switch (roofType)
	{
	case 0: //pyramid
		models.push_back(new Model(Type::ROOF_PYRAMID,
			(buildingWidth * wallWidth) + (wallDepth * 2) + roofOverhang,
			roofHeight,
			(buildingDepth * wallWidth) + (wallDepth * 2) + roofOverhang,
			((wallWidth * buildingWidth) + wallDepth) / 2,
			(wallHeight * buildingHeight) + wallDepth,
			((wallWidth * buildingDepth) + wallDepth) / 2,
			0));
		break;
	case 1: //flat
		models.push_back(new Model(Type::ROOF_FLAT,
			(buildingWidth * wallWidth) + (wallDepth * 2) + roofOverhang, 
			roofHeight, 
			(buildingDepth * wallWidth) + (wallDepth * 2) + roofOverhang,
			((wallWidth * buildingWidth) + wallDepth)/2,
			(wallHeight * buildingHeight) - (wallHeight / 2),
			((wallWidth * buildingDepth) + wallDepth) / 2,
			0));
		break;
	case 2: //shed
		models.push_back(new Model(Type::ROOF_SHED,
			(buildingWidth * wallWidth) + (wallDepth * 2) + roofOverhang,
			roofHeight,
			(buildingDepth * wallWidth) + (wallDepth * 2) + roofOverhang,
			((wallWidth * buildingWidth) + wallDepth) / 2,
			(wallHeight * buildingHeight) + wallDepth,
			((wallWidth * buildingDepth) + wallDepth) / 2,
			0));
		break;
	}
}

void BuildingGenerator::ClearVectors()
{
	walls.clear();
	windows.clear();
	corners.clear();
	floors.clear();
	door = nullptr;
}

std::vector<Model*> BuildingGenerator::GetModels()
{
	return models;
}
