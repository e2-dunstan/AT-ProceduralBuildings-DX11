#include "BuildingGenerator.h"
#include <random>

BuildingGenerator::~BuildingGenerator()
{
	models.clear();
	TwTerminate();
	ClearVectors();
}

//tweak bar callbacks
void TW_CALL Generate(void *clientData)
{
	BuildingGenerator* bg = static_cast<BuildingGenerator*>(clientData);
		
	bg->ClearVectors();
	bg->SetValuesChanged(true);
}
void TW_CALL Export(void *clientData)
{
	BuildingGenerator* bg = static_cast<BuildingGenerator*>(clientData);

	bg->SetCreateNewObj(true);
}

void BuildingGenerator::InitTweakBar(Renderer & renderer)
{
	TwInit(TW_DIRECT3D11, renderer.GetDevice());
	tweakBar = TwNewBar("Customise");
	TwWindowSize(1280, 720);
	int tweakBarSize[2] = { 200, 400 };
	TwSetParam(tweakBar, NULL, "size", TW_PARAM_INT32, 2, tweakBarSize);
	
	TwAddVarRW(tweakBar, "Building Width", TW_TYPE_INT32, &buildingWidth, "Group='Structure' min=1 max=20 step=1");
	TwAddVarRW(tweakBar, "Building Height", TW_TYPE_INT32, &buildingHeight, "Group='Structure' min=1 max=20 step=1");
	TwAddVarRW(tweakBar, "Building Depth", TW_TYPE_INT32, &buildingDepth, "Group='Structure' min=1 max=20 step=1");

	TwAddVarRW(tweakBar, "Wall Width", TW_TYPE_FLOAT, &wallWidth, "Group='Walls' min=1 max=10 step=1");
	TwAddVarRW(tweakBar, "Wall Height", TW_TYPE_FLOAT, &wallHeight, "Group='Walls' min=1 max=10 step=1");
	TwAddVarRW(tweakBar, "Wall Depth", TW_TYPE_FLOAT, &wallDepth, "Group='Walls' min=1 max=3 step=0.5");

	TwAddVarRW(tweakBar, "Windows on Width", TW_TYPE_INT32, &numWindowsOnWidth, "Group='Windows' min=0 max=20 step=1");
	TwAddVarRW(tweakBar, "Windows on Depth", TW_TYPE_INT32, &numWindowsOnDepth, "Group='Windows' min=0 max=20 step=1");
	TwAddVarRW(tweakBar, "Window Width", TW_TYPE_FLOAT, &windowWidth, "Group='Windows' min=1 max=5 step=1");
	TwAddVarRW(tweakBar, "Window Height", TW_TYPE_FLOAT, &windowHeight, "Group='Windows' min=1 max=5 step=1");
	TwAddVarRW(tweakBar, "Window Depth", TW_TYPE_FLOAT, &windowDepth, "Group='Windows' min=1 max=3 step=0.5");

	TwAddVarRW(tweakBar, "Door Width", TW_TYPE_FLOAT, &doorWidth, "Group='Door' min=1 max=6 step=1");
	TwAddVarRW(tweakBar, "Door Height", TW_TYPE_FLOAT, &doorHeight, "Group='Door' min=1 max=6 step=1");
	TwAddVarRW(tweakBar, "Door Depth", TW_TYPE_FLOAT, &doorDepth, "Group='Door' min=1 max=3 step=0.5");

	TwEnumVal roofTypeEV[] = { {PYRAMID, "Pyramid"}, {FLAT, "Flat"}, {SHED, "Shed"} };
	TwType roofType = TwDefineEnum("RoofType", roofTypeEV, 3);
	TwAddVarRW(tweakBar, "Roof Type", roofType, &roof, "Group='Roof'");
	TwAddVarRW(tweakBar, "Roof Overhang", TW_TYPE_FLOAT, &roofOverhang, "Group='Roof' min=0 max=10 step=1");
	TwAddVarRW(tweakBar, "Roof Height", TW_TYPE_FLOAT, &roofHeight, "Group='Roof' min=1 max=15 step=1");

	TwAddButton(tweakBar, "Generate", Generate, this, " label='Generate a new Building'");
	TwAddButton(tweakBar, "Export", Export, this, " label='Export as OBJ and MTL'");
}

void BuildingGenerator::Init()
{
	models.clear();
	
	models.push_back(new Model(Type::FLOOR,
		1000, 0, 1000,
		0, -(wallHeight + 0.2f) / 2, 0, 0));

	InitRoof();
	InitWalls();
	InitCorners();
	InitFloors();

	for (int floor = 0; floor < buildingHeight; floor++)
	{
		interiorFloors.push_back(new Interiors(buildingWidth, buildingHeight, buildingDepth, 
			wallWidth, wallHeight, wallDepth, floor));
		interiorFloors[floor]->InitWalls();
	}
	InitInteriors();

	ClearVectors();
}

void BuildingGenerator::InitWalls()
{
	float height = ((buildingHeight - 1) * wallHeight) / 2;
	//wall 1
	walls.push_back(new Model(Type::WALL,
		wallWidth * buildingWidth , wallHeight * buildingHeight, wallDepth,
		(wallWidth * (buildingWidth / 2)) + (wallDepth / 2) + (wallWidth / 2),
		height,
		0,
		0));
	//wall 2
	walls.push_back(new Model(Type::WALL,
		wallWidth * buildingWidth, wallHeight * buildingHeight, wallDepth,
		(wallWidth * (buildingWidth / 2)) + (wallDepth / 2) + (wallWidth / 2),
		height,
		(wallWidth * buildingDepth) + wallDepth,
		0));
	//wall 3
	walls.push_back(new Model(Type::WALL,
		wallWidth * buildingDepth, wallHeight * buildingHeight, wallDepth,
		0,
		height,
		(wallWidth * (buildingDepth / 2)) + (wallDepth / 2),// + (wallWidth / 2),
		90));
	//wall 4
	walls.push_back(new Model(Type::WALL,
		wallWidth * buildingDepth, wallHeight * buildingHeight, wallDepth,
		(wallWidth * buildingWidth) + wallDepth,
		height,
		(wallWidth * (buildingDepth / 2)) + (wallDepth / 2),// + (wallWidth / 2),
		90));

	for (int h = 0; h < buildingHeight; h++)
	{
		float w_height = h * wallHeight;

		/*for (int w = 0; w < buildingWidth; w++)
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
		}*/
		// -- CREATE WINDOWS -- //
		InitWindowsAndDoor(w_height);
	}

	for (int w = 0; w < walls.size(); w++)
	{
		models.push_back(walls[w]);
	}
	if (windows.size() == 0)
	{
		models.push_back(door);
	}
	else
	{
		for (int win = 0; win < windows.size(); win++)
		{
			float x = std::abs(windows[win]->GetPosition().x - (door->GetPosition().x / 2));
			float z = std::abs(windows[win]->GetPosition().z - (door->GetPosition().z / 2));
			//THIS IS TEMPERMENTAL
			if (std::abs(windows[win]->GetPosition().x - door->GetPosition().x) < 1
				&& std::abs(windows[win]->GetPosition().z - door->GetPosition().z) < 1
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
}

void BuildingGenerator::InitInteriors()
{
	//for each floor
	for (int i = 0; i < interiorFloors.size(); i++)
	{
		for (int j = 0; j < interiorFloors[i]->GetWalls().size(); j++)
		{
			models.push_back(interiorFloors[i]->GetWalls()[j]);
		}
		for (int k = 0; k < interiorFloors[i]->GetObjects().size(); k++)
		{
			models.push_back(interiorFloors[i]->GetObjects()[k]);
		}
	}
}

void BuildingGenerator::InitWindowsAndDoor(float height)
{
	//invalid number of windows or no windows
	if (numWindowsOnWidth > buildingWidth
		|| numWindowsOnDepth > buildingDepth)
	{
		door = new Model(Type::DOOR,
			doorWidth, doorHeight, doorDepth,
			(wallDepth / 2) + (wallWidth / 2),
			(doorHeight / 2) - (wallHeight / 2),
			0,
			0);
		return;
	}
	//float gapBetween;

	// -- CREATE DOOR -- //
	//Previously would randomise a position on the bottom floor however this proved to be buggy
	/*Gets a random location on a wall
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
	}*/

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
			//j = 1 to allow for door to slot in
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
	if (numWindowsOnWidth == 0)
	{
		door = new Model(Type::DOOR,
			doorWidth, doorHeight, doorDepth,
			wallDepth / 2,
			(doorHeight / 2) - (wallHeight / 2),
			0,
			0);
	}
	else
	{
		windows[0] = new Model(Type::DOOR,
			doorWidth, doorHeight, doorDepth,
			(wallDepth / 2) + (((wallWidth * buildingWidth) / numWindowsOnWidth) / 2),
			(doorHeight / 2) - (wallHeight / 2),
			0,
			0);

		door = windows[0];
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
	float roofYPos = (wallHeight * buildingHeight) - (wallHeight / 2) + (roofHeight / 2);

	switch (roof)
	{
	case PYRAMID:
		models.push_back(new Model(Type::ROOF_PYRAMID,
			(buildingWidth * wallWidth) + (wallDepth * 2) + roofOverhang,
			roofHeight,
			(buildingDepth * wallWidth) + (wallDepth * 2) + roofOverhang,
			((wallWidth * buildingWidth) + wallDepth) / 2,
			roofYPos,
			((wallWidth * buildingDepth) + wallDepth) / 2,
			0));
		break;
	case FLAT:
		models.push_back(new Model(Type::ROOF_FLAT,
			(buildingWidth * wallWidth) + (wallDepth * 2) + roofOverhang, 
			roofHeight, 
			(buildingDepth * wallWidth) + (wallDepth * 2) + roofOverhang,
			((wallWidth * buildingWidth) + wallDepth) / 2,
			roofYPos,
			((wallWidth * buildingDepth) + wallDepth) / 2,
			0));
		break;
	case SHED:
		models.push_back(new Model(Type::ROOF_SHED,
			(buildingWidth * wallWidth) + (wallDepth * 2) + roofOverhang,
			roofHeight,
			(buildingDepth * wallWidth) + (wallDepth * 2) + roofOverhang,
			((wallWidth * buildingWidth) + wallDepth) / 2,
			roofYPos,
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
	interiorFloors.clear();
	door = nullptr;
}

void BuildingGenerator::DrawTweakBar()
{
	TwDraw();
}

bool BuildingGenerator::TweakBarEventWin(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return TwEventWin(hwnd, msg, wParam, lParam);
}

void BuildingGenerator::TerminateTweakBar()
{
	TwTerminate();
}

std::vector<Model*> BuildingGenerator::GetModels()
{
	return models;
}

void BuildingGenerator::SetValuesChanged(bool changed)
{
	valuesChanged = changed;
}

bool BuildingGenerator::ValuesChanged()
{
	return valuesChanged;
}

void BuildingGenerator::SetCreateNewObj(bool create)
{
	createNewObj = create;
}

bool BuildingGenerator::CreateNewObj()
{
	return createNewObj;
}
