#include "InteriorWalls.h"
#include <time.h>


InteriorWalls::InteriorWalls(int bwidth, int bheight, int bdepth, float wwidth, float wheight, float wdepth, int b_floor)
{
	b_buildingWidth = bwidth;
	b_buildingHeight = bheight;
	b_buildingDepth = bdepth;
	b_wallWidth = wwidth;
	b_wallHeight = wheight;
	b_wallDepth = wdepth;
	floor = b_floor;
}

InteriorWalls::~InteriorWalls()
{
	walls.clear();
	previousX.clear();
	previousZ.clear();
}

void InteriorWalls::InitWalls()
{
	generator.seed(time(0));

	std::uniform_int_distribution<int> numOfWallsDistribution(1, 3);
	int numOfWalls = 2;//numOfWallsDistribution(generator);

	for (int i = 0; i < numOfWalls; i++)
	{
		if (i % 2 == 0)
			Divide(0);
		else
			Divide(90);
	}
}

void InteriorWalls::Divide(int rot)
{
	int w = currentWidth;
	int d = currentDepth;
	bool rotated = false;
	if (rot != 0)
	{
		rotated = true;
		w = currentDepth;
		d = currentWidth;
	}

	std::uniform_int_distribution<int> widthDistribution(1, w);
	std::uniform_int_distribution<int> doorDistribution(1, d - 1);

	int wallPos = GetValidPosition(widthDistribution, rot);
	if (wallPos == -1)
		return;

	int doorPos = doorDistribution(generator);

	int sec1_width = b_wallWidth * (doorPos - 2);
	int sec2_width = b_wallWidth * ((rotated ? b_buildingWidth : b_buildingDepth) - doorPos);
	float sec1_x = (sec1_width + b_wallDepth) / 2;
	float sec2_x = sec1_x + (sec1_width / 2) + b_wallWidth + (sec2_width / 2);

	if (sec1_width > 0)
	{
		walls.push_back(new Model(Type::INTERIOR_WALL,
			sec1_width, b_wallHeight, b_wallDepth,
			sec1_x,
			b_wallHeight * floor,
			wallPos * b_wallWidth,
			rot));
	}
	if (sec2_width > 0)
	{
		walls.push_back(new Model(Type::INTERIOR_WALL,
			sec2_width, b_wallHeight, b_wallDepth,
			sec2_x,
			b_wallHeight * floor,
			wallPos * b_wallWidth,
			rot));
	}

	if (rot == 0)
	{
		previousX.push_back(wallPos);
		if (currentWidth - wallPos > wallPos)
		{
			currentWidth -= wallPos;
			xOffset = wallPos * b_wallWidth;
		}
		else
		{
			currentWidth = wallPos;
		}
	}
	else
	{
		previousZ.push_back(wallPos);
		if (currentDepth - wallPos > wallPos)
		{
			currentDepth -= wallPos;
			zOffset = wallPos * b_wallWidth;
		}
		else
		{
			currentDepth = wallPos;
		}
	}





	/*int sec_z = wallPos * buildingGenWallWidth;

	int sec1_width = buildingGenWallWidth * (doorPos - 2);
	int sec2_width = buildingGenWallWidth * ((rotated ? buildingGenWidth : buildingGenDepth) - doorPos);
	float sec1_x = (rotated ? xOffset : zOffset) + (sec1_width + buildingGenWallDepth) / 2;
	float sec2_x = (rotated ? xOffset : zOffset) + sec1_x + (sec1_width / 2) + buildingGenWallWidth + (sec2_width / 2);

	if (sec2_width > 0)
	{
	walls.push_back(new Model(Type::INTERIOR_WALL,
	sec2_x, sec_z, //x, z
	rot, doorPos,
	sec2_width));
	}

	if (rot == 0)
	{
		previousX.push_back(wallPos);
		if (currentWidth - wallPos > wallPos)
		{
			currentWidth -= wallPos;
			xOffset = sec_z;
		}
		else
		{
			currentWidth = wallPos;
		}
	}
	else
	{
		previousZ.push_back(wallPos);
		if (currentDepth - wallPos > wallPos)
		{
			currentDepth -= wallPos;
			zOffset = sec_z;
		}
		else
		{
			currentDepth = wallPos;
		}
	}*/
}

int InteriorWalls::GetValidPosition(std::uniform_int_distribution<int> dist, int rot)
{
	int wallPos = dist(generator);

	bool invalid = true;
	int numOfAttempts = 0;

	while (invalid)
	{
		if ((rot == 0 && std::find(previousX.begin(), previousX.end(), wallPos) != previousX.end())
			|| (rot == 1 && std::find(previousZ.begin(), previousZ.end(), wallPos) != previousZ.end()))
		{
			wallPos = dist(generator);
			numOfAttempts++;
		}
		else
		{
			return wallPos;
			invalid = false;
		}

		if (numOfAttempts >= 10)
		{
			return -1;
		}
	}
}



std::vector<Model*> InteriorWalls::GetWalls()
{
	return walls;
}

