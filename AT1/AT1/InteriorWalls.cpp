#include "InteriorWalls.h"

InteriorWalls::InteriorWalls(int x, int y)
{
	width = x;
	height = y;
}

void InteriorWalls::InitWalls()
{
	std::uniform_int_distribution<int> numOfWallsDistribution(1, 5);
	int numOfWalls = numOfWallsDistribution(generator);

	for (int i = 0; i < numOfWalls; i++)
	{
		Divide(width, height);
	}
}

void InteriorWalls::Divide(int w, int h)
{
	std::uniform_int_distribution<int> widthDistribution(1, w);
	std::uniform_int_distribution<int> doorDistribution(1, h);

	int newWallPos = widthDistribution(generator);
	int doorPos = doorDistribution(generator);

	walls.push_back(InteriorWall(newWallPos, 0, doorPos));

	//incorrect below here
	if ((h - newWallPos) < newWallPos)
	{
		std::uniform_int_distribution<int> heightDistribution(1, newWallPos);
		newWallPos = heightDistribution(generator);
	}
	else
	{
		std::uniform_int_distribution<int> heightDistribution(1, h - newWallPos);
		std::uniform_int_distribution<int> doorDistribution(1, h);
		newWallPos = heightDistribution(generator);
	}
	
	walls.push_back(InteriorWall(newWallPos, 0, doorPos));



}

std::vector<InteriorWall> InteriorWalls::GetWalls()
{
	return walls;
}
