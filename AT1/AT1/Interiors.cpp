#include "Interiors.h"
#include <time.h>


Interiors::Interiors(int bwidth, int bheight, int bdepth, float wwidth, float wheight, float wdepth, int b_floor)
{
	b_buildingWidth = bwidth;
	currentWidth = b_buildingWidth;
	b_buildingHeight = bheight;
	b_buildingDepth = bdepth;
	currentDepth = b_buildingDepth;
	b_wallWidth = wwidth;
	b_wallHeight = wheight;
	b_wallDepth = wdepth;
	floor = b_floor;
}

Interiors::~Interiors()
{
	walls.clear();
	previousX.clear();
	previousZ.clear();

	if (room1)
	{
		delete room1;
		room1 = nullptr;
	}
	if (room2)
	{
		delete room2;
		room2 = nullptr;
	}
	if (room3)
	{
		delete room3;
		room3 = nullptr;
	}
	if (bedModel)
	{
		delete bedModel;
		bedModel = nullptr;
	}
	if (sofaModel)
	{
		delete sofaModel;
		sofaModel = nullptr;
	}
	if (toiletModel)
	{
		delete toiletModel;
		toiletModel = nullptr;
	}
	//if (objImporter)
	//{
	//	delete objImporter;
	//	objImporter = nullptr;
	//}
}

void Interiors::InitWalls()
{
	//objImporter = new OBJImporter();
	//Using this produced the same random number for each floor.
	//generator.seed(time(0));

	std::mt19937 seed(generator());

	CreateWalls(seed);

	/*std::uniform_int_distribution<int> numOfWallsDistribution(1, 3);
	int numOfWalls = 2;//numOfWallsDistribution(generator);

	for (int i = 0; i < numOfWalls; i++)
	{
		if (i % 2 == 0)
			Divide(0);
		else
			Divide(90);
	}*/
}

// ---------------------
// |      room 1       |
// |                   |
// |-------------  ----|
// |       |           |
// | room 2|           |
// |           room 3  |
// |       |           |
// ---------------------
void Interiors::CreateWalls(std::mt19937 seed)
{
	//Current room dimensions
	currentWidth = b_buildingWidth * b_wallWidth;
	currentDepth = b_buildingDepth * b_wallWidth;

	//Generate room 1
	std::uniform_int_distribution<std::mt19937::result_type> randZ(currentDepth / 3, currentDepth - (b_wallWidth * 2));
	int z = randZ(seed);
	room1 = new Room(0, z, currentWidth, currentDepth - z);

	//Generate room 2
	currentDepth = z;
	std::uniform_int_distribution<std::mt19937::result_type> randX(b_wallWidth * 2, currentWidth - (b_wallWidth * 2));
	int x = randX(seed);
	room2 = new Room(x, 0, currentWidth - x, currentDepth);

	//Generate room 3
	currentWidth = x;
	room3 = new Room(0, 0, currentWidth, currentDepth);

	Wall* wall1 = new Wall(room1->width / 2, room1->originZ, room1->width, 0);
	Wall* wall2 = new Wall(room2->originX, room2->depth / 2, room2->depth, 0);

	//Randomise doorway locations
	std::uniform_int_distribution<std::mt19937::result_type> randDoor1(1, wall1->length - b_wallWidth);
	std::uniform_int_distribution<std::mt19937::result_type> randDoor2(1, wall2->length - b_wallWidth);
	wall1->doorLoc = randDoor1(seed);
	wall2->doorLoc = randDoor2(seed);

	CreateWallModels(wall1, wall2);
	CreateObjects(seed);
}

void Interiors::CreateWallModels(Wall* w1, Wall* w2)
{
	if (w1->doorLoc > 0)
		walls.push_back(new Model(Type::INTERIOR_WALL,
			w1->doorLoc, b_wallHeight - 0.1f, b_wallDepth,
			(int)((w1->doorLoc / 2) + (b_wallDepth / 2)),
			floor * b_wallHeight - 0.4f,
			w1->originZ + b_wallDepth,
			0));
	if (w1->length - w1->doorLoc - doorWidth > 0)
		walls.push_back(new Model(Type::INTERIOR_WALL,
			w1->length - w1->doorLoc - doorWidth, b_wallHeight - 0.1f, b_wallDepth,
			(b_buildingWidth * b_wallWidth) - ((w1->length - w1->doorLoc - doorWidth - b_wallDepth) / 2),
			floor * b_wallHeight - 0.4f,
			w1->originZ + b_wallDepth,
			0));

	if (w2->doorLoc > 0)
		walls.push_back(new Model(Type::INTERIOR_WALL,
			b_wallDepth, b_wallHeight - 0.1f, w2->doorLoc,
			w2->originX + b_wallDepth,
			floor * b_wallHeight - 0.4f,
			(int)((w2->doorLoc / 2) + (b_wallDepth / 2)),
			0));
	if (w2->length - w2->doorLoc - doorWidth > 0)
		walls.push_back(new Model(Type::INTERIOR_WALL,
			b_wallDepth, b_wallHeight - 0.1f, w2->length - w2->doorLoc - doorWidth,
			w2->originX + b_wallDepth,
			floor * b_wallHeight - 0.4f,
			w2->length - (int)((w2->length - w2->doorLoc - doorWidth - b_wallDepth) / 2),
			0));
}

void Interiors::CreateObjects(std::mt19937 seed)
{
	float dims = 3;
	
	std::uniform_int_distribution<std::mt19937::result_type> randX_1(room1->originX + dims, room1->originX + room1->width - dims);
	std::uniform_int_distribution<std::mt19937::result_type> randZ_1(room1->originZ + dims, room1->originZ + room1->depth - dims);

	sofaModel = new Model(Type::OBJECT,
		dims, dims, dims,
		randX_1(seed),
		(floor * b_wallHeight) + (dims / 2) - (b_wallHeight / 2) + 0.01f,
		randZ_1(seed),
		0);

	std::uniform_int_distribution<std::mt19937::result_type> randX_2(room2->originX + dims, room2->originX + room2->width - dims);
	std::uniform_int_distribution<std::mt19937::result_type> randZ_2(room2->originZ + dims, room2->originZ + room2->depth - dims);

	toiletModel = new Model(Type::OBJECT,
		dims, dims, dims,
		randX_2(seed),
		(floor * b_wallHeight) + (dims / 2) - (b_wallHeight / 2) + 0.01f,
		randZ_2(seed),
		0);

	std::uniform_int_distribution<std::mt19937::result_type> randX_3(room3->originX + dims, room3->originX + room3->width - dims);
	std::uniform_int_distribution<std::mt19937::result_type> randZ_3(room3->originZ + dims, room3->originZ + room3->depth - dims);

	bedModel = new Model(Type::OBJECT,
		dims, dims, dims,
		randX_3(seed),
		(floor * b_wallHeight) + (dims / 2) - (b_wallHeight / 2) + 0.01f,
		randZ_3(seed),
		0);


	//objImporter->ReadOBJ(table);
	//bedModel->SetVertices(objImporter->GetVertices());
	//bedModel->SetIndices(objImporter->GetIndices());
}


/*void Interiors::Divide(int rot)
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
	}
}

int Interiors::GetValidPosition(std::uniform_int_distribution<int> dist, int rot)
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
}*/

std::vector<Model*> Interiors::GetWalls()
{
	return walls;
}

std::vector<Model*> Interiors::GetObjects()
{
	std::vector<Model*> objs;

	objs.push_back(bedModel);
	objs[0]->SetTextureString(bedTexture);

	objs.push_back(sofaModel);
	objs[1]->SetTextureString(sofaTexture);

	objs.push_back(toiletModel);
	objs[2]->SetTextureString(toiletTexture);

	return objs;
}

