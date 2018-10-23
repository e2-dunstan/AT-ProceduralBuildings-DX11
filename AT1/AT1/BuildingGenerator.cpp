#include "BuildingGenerator.h"

void BuildingGenerator::Init()
{
	InitWalls();
	InitCorners();
	InitFloors();

	ClearVectors();
}

void BuildingGenerator::InitWalls()
{
	buildingDepth += 2;
	for (int f = 1; f <= buildingHeight; f++)
	{
		float height = f * wallHeight;
		for (int d = 0; d < buildingDepth; d++)
		{
			if (d == 0)
			{
				float depth = (d + 0.5f) * wallWidth;
				for (int w = 0; w < buildingWidth; w++)
				{
					walls.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
						w * wallWidth, height, depth, 90.0f * 0));
				}
			}
			else if (d == (buildingDepth - 1))
			{
				float depth = ((d - 0.5f) * wallWidth) + (wallDepth * 2);
				for (int w = 0; w < buildingWidth; w++)
				{
					walls.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
						w * wallWidth, height, depth, 90.0f * 2));
				}
			}
			else
			{
				float depth = (d* wallWidth) + wallDepth;
				walls.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
					-(wallWidth / 2) - wallDepth, height, depth, 90.0f * 1));
				walls.push_back(new Model(Type::WALL, wallWidth, wallHeight, wallDepth,
					(buildingWidth * wallWidth) - (wallWidth / 2) + wallDepth, height, depth, 90.0f * 3));
			}
		}
	}

	for (int w = 0; w < walls.size(); w++)
	{
		models.push_back(walls[w]);
	}
}

void BuildingGenerator::InitCorners()
{
	//0,0
	corners.push_back(new Model(Type::CORNER, wallDepth, wallHeight * buildingHeight, wallDepth,
		-(wallWidth / 2) - wallDepth,
		(wallHeight * (buildingHeight + 1)) / 2,
		0.5f * wallWidth, 
		0));
	//1,0
	corners.push_back(new Model(Type::CORNER, wallDepth, wallHeight * buildingHeight, wallDepth,
		(wallWidth * buildingWidth) - (wallWidth / 2) + wallDepth, 
		(wallHeight * (buildingHeight + 1)) / 2, 
		0.5f * wallWidth, 
		0));
	//0,1
	corners.push_back(new Model(Type::CORNER, wallDepth, wallHeight * buildingHeight, wallDepth,
		-(wallWidth / 2) - wallDepth, (wallHeight * (buildingHeight + 1)) / 2, (wallWidth * (buildingDepth - 1)) - (wallDepth / 2), 
		0));
	//1,1
	corners.push_back(new Model(Type::CORNER, wallDepth, wallHeight * buildingHeight, wallDepth,
		(wallWidth * buildingWidth) - (wallWidth / 2) + wallDepth, 
		(wallHeight * (buildingHeight + 1)) / 2, 
		(wallWidth * (buildingDepth - 1)) - (wallDepth / 2), 
		0));

	for (int c = 0; c < corners.size(); c++)
	{
		models.push_back(corners[c]);
	}
}

void BuildingGenerator::InitFloors()
{
	float floorWidth = buildingWidth * wallWidth;
	float floorDepth = buildingDepth * wallDepth;

	for (int f = 0; f < buildingHeight; f++)
	{
		floors.push_back(new Model(Type::FLOOR, floorWidth, 0, floorDepth,
			wallDepth + (floorWidth /2 ),
			wallHeight * buildingHeight,
			wallDepth + (floorDepth / 2), 
			0));
	}

	for (int f = 0; f < floors.size(); f++)
	{
		models.push_back(floors[f]);
	}
}

void BuildingGenerator::ClearVectors()
{
	walls.clear();
	corners.clear();
	floors.clear();
}

std::vector<Model*> BuildingGenerator::GetModels()
{
	return models;
}
