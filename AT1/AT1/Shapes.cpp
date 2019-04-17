#include "Shapes.h"

std::vector<Vertex> Shape::CreateSquareVertices(float width, float height, float depth)
{
	//To account for centre point
	width *= 0.5f;
	height *= 0.5f;
	depth *= 0.5f;

	std::vector<Vertex> vertices
	{
		// Front Face
		Vertex(-width, -height, -depth,			0.0f, 1.0f,			0.0f, 0.0f, -1.0f),
		Vertex(-width,  height, -depth,			0.0f, 0.0f,			0.0f, 0.0f, -1.0f),
		Vertex(width,  height, -depth,			1.0f, 0.0f,			0.0f, 0.0f, -1.0f),
		Vertex(width, -height, -depth,			1.0f, 1.0f,			0.0f, 0.0f, -1.0f),
		// Back Face
		Vertex(-width, -height, depth,			1.0f, 1.0f,			0.0f, 0.0f, 1.0f),
		Vertex(width, -height, depth,			0.0f, 1.0f,			0.0f, 0.0f, 1.0f),
		Vertex(width,  height, depth,			0.0f, 0.0f,			0.0f, 0.0f, 1.0f),
		Vertex(-width,  height, depth,			1.0f, 0.0f,			0.0f, 0.0f, 1.0f),
		// Top Face
		Vertex(-width, height, -depth,			0.0f, 1.0f,			0.0f, 1.0f, 0.0f),	//2
		Vertex(-width, height,  depth,			0.0f, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, height,  depth,			1.0f, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, height, -depth,			1.0f, 1.0f,			0.0f, 1.0f, 0.0f),	//3
		// Bottom Face
		Vertex(-width, -height, -depth,			1.0f, 1.0f,			0.0f, -1.0f, 0.0f),	//1
		Vertex(width, -height, -depth,			0.0f, 1.0f,			0.0f, -1.0f, 0.0f),	//4
		Vertex(width, -height,  depth,			0.0f, 0.0f,			0.0f, -1.0f, 0.0f),
		Vertex(-width, -height,  depth,			1.0f, 0.0f,			0.0f, -1.0f, 0.0f),	//5
		// Left Face
		Vertex(-width, -height,  depth,			0.0f, 1.0f,			-1.0f, 0.0f, 0.0f),	//5
		Vertex(-width,  height,  depth,			0.0f, 0.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width,  height, -depth,			1.0f, 0.0f,			-1.0f, 0.0f, 0.0f),	//2
		Vertex(-width, -height, -depth,			1.0f, 1.0f,			-1.0f, 0.0f, 0.0f),	//1
		// Right Face
		Vertex(width, -height, -depth,			0.0f, 1.0f,			1.0f, 0.0f, 0.0f),	//4
		Vertex(width,  height, -depth,			0.0f, 0.0f,			1.0f, 0.0f, 0.0f),	//3
		Vertex(width,  height,  depth,			1.0f, 0.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width, -height,  depth,			1.0f, 1.0f,			1.0f, 0.0f, 0.0f),
	};

	return vertices;
}
std::vector<Vertex> Shape::CreateLargeSquareVertices(float width, float height, float depth)
{
	//To account for centre point
	width *= 0.5f;
	height *= 0.5f;
	depth *= 0.5f;

	std::vector<Vertex> vertices
	{
		// Front Face
		Vertex(-width, -height, -depth,			0.0f, 1.0f,			0.0f, 0.0f, -1.0f),
		Vertex(-width,  height, -depth,			0.0f, 0.0f,			0.0f, 0.0f, -1.0f),
		Vertex(width,  height, -depth,			10.0f, 0.0f,		0.0f, 0.0f, -1.0f),
		Vertex(width, -height, -depth,			10.0f, 1.0f,		0.0f, 0.0f, -1.0f),
		// Back Face
		Vertex(-width, -height, depth,			10.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(width, -height, depth,			0.0f, 1.0f,			0.0f, 0.0f, 1.0f),
		Vertex(width,  height, depth,			0.0f, 0.0f,			0.0f, 0.0f, 1.0f),
		Vertex(-width,  height, depth,			10.0f, 0.0f,		0.0f, 0.0f, 1.0f),
		// Top Face
		Vertex(-width, height, -depth,			0.0f, 10.0f,		0.0f, 1.0f, 0.0f),
		Vertex(-width, height,  depth,			0.0f, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, height,  depth,			10.0f, 0.0f,		0.0f, 1.0f, 0.0f),
		Vertex(width, height, -depth,			10.0f, 10.0f,		0.0f, 1.0f, 0.0f),
		// Bottom Face
		Vertex(-width, -height, -depth,			10.0f, 10.0f,		0.0f, -1.0f, 0.0f),
		Vertex(width, -height, -depth,			0.0f, 10.0f,		0.0f, -1.0f, 0.0f),
		Vertex(width, -height,  depth,			0.0f, 0.0f,			0.0f, -1.0f, 0.0f),
		Vertex(-width, -height,  depth,			10.0f, 0.0f,		0.0f, -1.0f, 0.0f),
		// Left Face
		Vertex(-width, -height,  depth,			0.0f, 1.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width,  height,  depth,			0.0f, 0.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width,  height, -depth,			10.0f, 0.0f,		-1.0f, 0.0f, 0.0f),
		Vertex(-width, -height, -depth,			10.0f, 1.0f,		-1.0f, 0.0f, 0.0f),
		// Right Face
		Vertex(width, -height, -depth,			0.0f, 1.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width,  height, -depth,			0.0f, 0.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width,  height,  depth,			10.0f, 0.0f,		1.0f, 0.0f, 0.0f),
		Vertex(width, -height,  depth,			10.0f, 1.0f,		1.0f, 0.0f, 0.0f),
	};

	return vertices;
}

std::vector<Vertex> Shape::CreateFloorVertices(float width, float height, float depth)
{
	width *= 0.5f;
	depth *= 0.5f;

	std::vector<Vertex> vertices
	{
		Vertex(-width, height, -depth,			0.0f, depth/2,			0.0f, 1.0f, 0.0f),
		Vertex(-width, height,  depth,			0.0f, 0.0f,				0.0f, 1.0f, 0.0f),
		Vertex(width, height,  depth,			width/2, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, height, -depth,			width/2, depth/2,		0.0f, 1.0f, 0.0f),
	};

	return vertices;
}

std::vector<Vertex> Shape::CreateCornerVertices(float width, float height)
{
	width *= 0.5f;
	height *= 0.5f;

	std::vector<Vertex> vertices
	{
		// Front Face
		Vertex(-width, -height, -width,			0.0f, 1.0f,			0.0f, 0.0f, -1.0f),
		Vertex(-width, height, -width,			0.0f, 0.0f,			0.0f, 0.0f, -1.0f),
		Vertex(width, height, -width,			1.0f, 0.0f,			0.0f, 0.0f, -1.0f),
		Vertex(width, -height, -width,			1.0f, 1.0f,			0.0f, 0.0f, -1.0f),
		// Back Face
		Vertex(-width, -height, width,			1.0f, 1.0f,			0.0f, 0.0f, 1.0f),
		Vertex(width, -height, width,			0.0f, 1.0f,			0.0f, 0.0f, 1.0f),
		Vertex(width, height, width,			0.0f, 0.0f,			0.0f, 0.0f, 1.0f),
		Vertex(-width, height, width,			1.0f, 0.0f,			0.0f, 0.0f, 1.0f),
		// Top Face
		Vertex(-width, height, -width,			0.0f, 1.0f,			0.0f, 1.0f, 0.0f),	//2
		Vertex(-width, height, width,			0.0f, 0.0f,			0.0f, 1.0f, 0.0f),	//8
		Vertex(width, height, width,			1.0f, 0.0f,			0.0f, 1.0f, 0.0f),	//7
		Vertex(width, height, -width,			1.0f, 1.0f,			0.0f, 1.0f, 0.0f),	//3
		// Bottom Face
		Vertex(-width, -height, -width,			1.0f, 1.0f,			0.0f, -1.0f, 0.0f),	//1
		Vertex(width, -height, -width,			0.0f, 1.0f,			0.0f, -1.0f, 0.0f),	//4
		Vertex(width, -height, width,			0.0f, 0.0f,			0.0f, -1.0f, 0.0f),	//6
		Vertex(-width, -height, width,			1.0f, 0.0f,			0.0f, -1.0f, 0.0f),	//5
		// Left Face
		Vertex(-width, -height, width,			0.0f, 1.0f,			-1.0f, 0.0f, 0.0f),	//5
		Vertex(-width, height, width,			0.0f, 0.0f,			-1.0f, 0.0f, 0.0f),	//8
		Vertex(-width, height, -width,			1.0f, 0.0f,			-1.0f, 0.0f, 0.0f),	//2
		Vertex(-width, -height, -width,			1.0f, 1.0f,			-1.0f, 0.0f, 0.0f),	//1
		// Right Face
		Vertex(width, -height, -width,			0.0f, 1.0f,			1.0f, 0.0f, 0.0f),	//4
		Vertex(width, height, -width,			0.0f, 0.0f,			1.0f, 0.0f, 0.0f),	//3
		Vertex(width, height, width,			1.0f, 0.0f,			1.0f, 0.0f, 0.0f),	//7
		Vertex(width, -height, width,			1.0f, 1.0f,			1.0f, 0.0f, 0.0f),	//6
	};

	return vertices;
}

std::vector<Vertex> Shape::CreatePyramidVertices(float width, float height, float depth)
{
	width *= 0.5f;
	height *= 0.5f;
	depth *= 0.5f;

	std::vector<Vertex> vertices
	{
		// Front Face
		Vertex(-width, -height, -depth,			0.0f, 5.0f,			0.0f, 0.0f, -1.0f),
		Vertex(0,  height, 0,					5.0f, 5.0f,			0.0f, 0.0f, -1.0f),
		Vertex(width, -height, -depth,			5.0f, 0.0f,			0.0f, 0.0f, -1.0f),
		// Back Face
		Vertex(-width, -height, depth,			5.0f, 5.0f,			0.0f, 0.0f, 1.0f),
		Vertex(0,  height, 0,					0.0f, 5.0f,			0.0f, 0.0f, 1.0f),
		Vertex(width, -height, depth,			0.0f, 0.0f,			0.0f, 0.0f, 1.0f),
		// Bottom Face
		Vertex(-width, -height, -depth,			5.0f, 5.0f,			0.0f, -1.0f, 0.0f),	//1
		Vertex(width, -height, -depth,			0.0f, 5.0f,			0.0f, -1.0f, 0.0f),	//3
		Vertex(width, -height, depth,			0.0f, 0.0f,			0.0f, -1.0f, 0.0f),	//6
		Vertex(-width, -height, depth,			5.0f, 0.0f,			0.0f, -1.0f, 0.0f),	//4
		// Left Face
		Vertex(-width, -height, depth,			0.0f, 5.0f,			-1.0f, 0.0f, 0.0f),	//4
		Vertex(0,  height, 0,					0.0f, 0.0f,			-1.0f, 0.0f, 0.0f),	//2
		Vertex(-width, -height, -depth,			5.0f, 0.0f,			-1.0f, 0.0f, 0.0f),	//1
		// Right Face
		Vertex(width, -height, -depth,			0.0f, 5.0f,			1.0f, 0.0f, 0.0f),	//3
		Vertex(0,  height, 0,					0.0f, 0.0f,			1.0f, 0.0f, 0.0f),	//2
		Vertex(width, -height, depth,			5.0f, 0.0f,			1.0f, 0.0f, 0.0f),	//6
	};

	return vertices;
}

std::vector<Vertex> Shape::CreateShedVertices(float width, float height, float depth)
{
	width *= 0.5f;
	height *= 0.5f;
	depth *= 0.5f;

	std::vector<Vertex> vertices
	{
		// Front Face
		Vertex(-width, -height, -depth,			0.0f, 1.0f,			0.0f, 0.0f, -1.0f),
		Vertex(-width,  height, -depth,			0.0f, 0.0f,			0.0f, 0.0f, -1.0f),
		Vertex(width,  height, -depth,			1.0f, 0.0f,			0.0f, 0.0f, -1.0f),
		Vertex(width, -height, -depth,			1.0f, 1.0f,			0.0f, 0.0f, -1.0f),
		// Top Face
		Vertex(-width, height, -depth,			0.0f, 1.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, height,  -depth,			0.0f, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, -height,  depth,			1.0f, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(-width, -height, depth,			1.0f, 1.0f,			0.0f, 1.0f, 0.0f),
		// Bottom Face
		Vertex(-width, -height, -depth,			1.0f, 1.0f,			0.0f, -1.0f, 0.0f),
		Vertex(width, -height, -depth,			0.0f, 1.0f,			0.0f, -1.0f, 0.0f),
		Vertex(width, -height,  depth,			0.0f, 0.0f,			0.0f, -1.0f, 0.0f),
		Vertex(-width, -height,  depth,			1.0f, 0.0f,			0.0f, -1.0f, 0.0f),
		// Left Face
		Vertex(-width, -height,  -depth,		0.0f, 1.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width,  -height,  depth,		0.0f, 0.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width,  height, -depth,			1.0f, 0.0f,			-1.0f, 0.0f, 0.0f),
		// Right Face
		Vertex(width, -height, -depth,			0.0f, 1.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width,  height, -depth,			0.0f, 0.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width,  -height,  depth,			1.0f, 0.0f,			1.0f, 0.0f, 0.0f),
	};

	return vertices;
}

//Maths wrong somewhere
/*
std::vector<Vertex> Shape::CreateWindowVertices(float width, float height, float depth)
{
	//To account for centre point
	width *= 0.5f;
	height *= 0.5f;
	depth *= 0.5f;

	float paneWidth = 0.2f;
	float U1 = 3 * (paneWidth / (2 * width));
	float U2 = 3 * (((2 * width) - paneWidth) / (2 * width));
	float U3 = 3;
	float V1 = 3 * (paneWidth / (2 * height));
	float V2 = 3 * (((2 * height) - paneWidth) / (2 * height));
	float V3 = 3;

	std::vector<Vertex> vertices
	{
		// Front Face
		Vertex(-width, -height, -depth,									0.0f, V3,			0.0f, 0.0f, -1.0f), //0
		Vertex(-width + paneWidth, -height, -depth,						U1, V3,				0.0f, 0.0f, -1.0f),	//1
		Vertex(width - paneWidth, -height, -depth,						U2, V3,				0.0f, 0.0f, -1.0f),	//2
		Vertex(width, -height, -depth,									U3, V3,				0.0f, 0.0f, -1.0f),	//3
		Vertex(-width,  height, -depth,									0.0f, 0.0f,			0.0f, 0.0f, -1.0f), //4
		Vertex(-width + paneWidth, height, -depth,						U1, 0.0f,			0.0f, 0.0f, -1.0f),	//5
		Vertex(width - paneWidth, height, -depth,						U2, 0.0f,			0.0f, 0.0f, -1.0f),	//6
		Vertex(width,  height, -depth,									U3, 0.0f,			0.0f, 0.0f, -1.0f),	//7
		Vertex(-width + paneWidth, height - paneWidth, -depth,			U1, V1,				0.0f, 0.0f, -1.0f),	//8
		Vertex(width - paneWidth, height - paneWidth, -depth,			U2, V1,				0.0f, 0.0f, -1.0f),	//9
		Vertex(-width + paneWidth, -height + paneWidth, -depth,			U1, V2,				0.0f, 0.0f, -1.0f),	//10
		Vertex(width - paneWidth, -height + paneWidth, -depth,			U2, V2,				0.0f, 0.0f, -1.0f),	//11
		// Back Face
		Vertex(-width, -height, depth,									0.0f, V3,			0.0f, 0.0f, 1.0f),  //12
		Vertex(-width + paneWidth, height, depth,						U1, V3,				0.0f, 0.0f, 1.0f),	//13
		Vertex(width - paneWidth, height, depth,						U2, V3,				0.0f, 0.0f, 1.0f),	//14
		Vertex(width, -height, depth,									U3, V3,				0.0f, 0.0f, 1.0f),	//15
		Vertex(-width,  height, depth,									0.0f, 0.0f,			0.0f, 0.0f, 1.0f),	//16
		Vertex(-width + paneWidth, height, depth,						U1, 0.0f,			0.0f, 0.0f, 1.0f),	//17
		Vertex(width - paneWidth, height, depth,						U2, 0.0f,			0.0f, 0.0f, 1.0f),	//18
		Vertex(width,  height, depth,									U3, 0.0f,			0.0f, 0.0f, 1.0f),	//19
		Vertex(-width + paneWidth, height - paneWidth, depth,			U1, V1,				0.0f, 0.0f, 1.0f),	//20
		Vertex(width - paneWidth, height - paneWidth, depth,			U2, V1,				0.0f, 0.0f, 1.0f),	//21
		Vertex(-width + paneWidth, -height + paneWidth, depth,			U1, V2,				0.0f, 0.0f, 1.0f),	//22
		Vertex(width - paneWidth, -height + paneWidth, depth,			U2, V2,				0.0f, 0.0f, 1.0f),	//23
		// Left Face
		Vertex(-width, -height,  depth,									0.0f, 1.0f,			-1.0f, 0.0f, 0.0f),	//24
		Vertex(-width,  height,  depth,									0.0f, 0.0f,			-1.0f, 0.0f, 0.0f),	//25
		Vertex(-width,  height, -depth,									1.0f, 0.0f,			-1.0f, 0.0f, 0.0f),	//26
		Vertex(-width, -height, -depth,									1.0f, 1.0f,			-1.0f, 0.0f, 0.0f),	//27
		// Right Face
		Vertex(width, -height, -depth,									0.0f, 1.0f,			1.0f, 0.0f, 0.0f),	//28
		Vertex(width,  height, -depth,									0.0f, 0.0f,			1.0f, 0.0f, 0.0f),	//29
		Vertex(width,  height,  depth,									1.0f, 0.0f,			1.0f, 0.0f, 0.0f),	//30
		Vertex(width, -height,  depth,									1.0f, 1.0f,			1.0f, 0.0f, 0.0f),	//31
		// Top Face
		Vertex(-width, height, -depth,									0.0f, 1.0f,			0.0f, 1.0f, 0.0f),	//32
		Vertex(-width, height,  depth,									0.0f, 0.0f,			0.0f, 1.0f, 0.0f),	//33
		Vertex(width, height,  depth,									1.0f, 0.0f,			0.0f, 1.0f, 0.0f),	//34
		Vertex(width, height, -depth,									1.0f, 1.0f,			0.0f, 1.0f, 0.0f),	//35
		// Bottom Face																							
		Vertex(-width, -height, -depth,									1.0f, 1.0f,			0.0f, -1.0f, 0.0f),	//36
		Vertex(width, -height, -depth,									0.0f, 1.0f,			0.0f, -1.0f, 0.0f),	//37
		Vertex(width, -height,  depth,									0.0f, 0.0f,			0.0f, -1.0f, 0.0f),	//38
		Vertex(-width, -height,  depth,									1.0f, 0.0f,			0.0f, -1.0f, 0.0f),	//39
		// Inner Front Face
		Vertex(-width + paneWidth, -height + paneWidth, -0.2f,			U1, V2,				0.0f, 0.0f, -1.0f), //40
		Vertex(width - paneWidth, -height + paneWidth, -0.2f,			U2, V2,				0.0f, 0.0f, -1.0f),	//41
		Vertex(-width + paneWidth, height - paneWidth, -0.2f,			U1, V1,				0.0f, 0.0f, -1.0f),	//42
		Vertex(width - paneWidth, height - paneWidth, -0.2f,			U2, V1,				0.0f, 0.0f, -1.0f),	//43
		// Inner Back Face
		Vertex(-width + paneWidth, -height + paneWidth, 0.2f,			U1, V2,				0.0f, 0.0f, 1.0f),	//44
		Vertex(width - paneWidth, -height + paneWidth, 0.2f,			U2, V2,				0.0f, 0.0f, 1.0f),	//45
		Vertex(-width + paneWidth, height - paneWidth, 0.2f,			U1, V1,				0.0f, 0.0f, 1.0f),	//46
		Vertex(width - paneWidth, height - paneWidth, 0.2f,				U2, V1,				0.0f, 0.0f, 1.0f),	//47
		// Inner Left Front Face
		Vertex(-width + paneWidth, -height + paneWidth, 0.2f,			U1, V2,				1.0f, 0.0f, 0.0f),	//48
		Vertex(-width + paneWidth,  height - paneWidth, 0.2f,			U1, V1,				1.0f, 0.0f, 0.0f),	//49
		Vertex(-width + paneWidth,  -height + paneWidth, depth,			U2, V1,				1.0f, 0.0f, 0.0f),	//50
		Vertex(-width + paneWidth, height - paneWidth, depth,			U2, V2,				1.0f, 0.0f, 0.0f),	//51
		// Inner Right Front Face
		Vertex(width - paneWidth, -height + paneWidth, 0.2f,			U1, V2,				-1.0f, 0.0f, 0.0f),	//52
		Vertex(width - paneWidth,  height - paneWidth, 0.2f,			U1, V1,				-1.0f, 0.0f, 0.0f),	//53
		Vertex(width - paneWidth,  -height + paneWidth, depth,			U2, V1,				-1.0f, 0.0f, 0.0f),	//54
		Vertex(width - paneWidth, height - paneWidth, depth,			U2, V2,				-1.0f, 0.0f, 0.0f),	//55
		// Inner Left Back Face
		Vertex(-width + paneWidth, -height + paneWidth, -0.2f,			U1, V2,				1.0f, 0.0f, 0.0f),	//56
		Vertex(-width + paneWidth,  height - paneWidth, -0.2f,			U1, V1,				1.0f, 0.0f, 0.0f),	//57
		Vertex(-width + paneWidth,  -height + paneWidth, -depth,		U2, V1,				1.0f, 0.0f, 0.0f),	//58
		Vertex(-width + paneWidth, height - paneWidth, -depth,			U2, V2,				1.0f, 0.0f, 0.0f),	//59
		// Inner Right Back Face
		Vertex(width - paneWidth, -height + paneWidth, -0.2f,			U1, V2,				-1.0f, 0.0f, 0.0f),	//60
		Vertex(width - paneWidth,  height - paneWidth, -0.2f,			U1, V1,				-1.0f, 0.0f, 0.0f),	//61
		Vertex(width - paneWidth,  -height + paneWidth, -depth,			U2, V1,				-1.0f, 0.0f, 0.0f),	//62
		Vertex(width - paneWidth, height - paneWidth, -depth,			U2, V2,				-1.0f, 0.0f, 0.0f),	//63
		// Inner Front Top Face
		Vertex(-width + paneWidth, height - paneWidth, 0.2f,			U1, V2,				0.0f, 1.0f, 0.0f),	//64
		Vertex(-width + paneWidth, height - paneWidth,  depth,			U1, V1,				0.0f, 1.0f, 0.0f),	//65
		Vertex(width - paneWidth, height - paneWidth,  depth,			U2, V1,				0.0f, 1.0f, 0.0f),	//66
		Vertex(width - paneWidth, height - paneWidth, 0.2f,				U2, V2,				0.0f, 1.0f, 0.0f),	//67
		// Inner Front Bottom Face
		Vertex(-width + paneWidth, -height + paneWidth, 0.2f,			U1, V2,				0.0f, -1.0f, 0.0f),	//68
		Vertex(-width + paneWidth, -height + paneWidth,  depth,			U1, V1,				0.0f, -1.0f, 0.0f),	//69
		Vertex(width - paneWidth, -height + paneWidth,  depth,			U2, V1,				0.0f, -1.0f, 0.0f),	//70
		Vertex(width - paneWidth, -height + paneWidth, 0.2f,			U2, V2,				0.0f, -1.0f, 0.0f),	//71
		// Inner Back Top Face
		Vertex(-width + paneWidth, height - paneWidth, -0.2f,			U1, V2,				0.0f, 1.0f, 0.0f),	//72
		Vertex(-width + paneWidth, height - paneWidth,  -depth,			U1, V1,				0.0f, 1.0f, 0.0f),	//73
		Vertex(width - paneWidth, height - paneWidth,  -depth,			U2, V1,				0.0f, 1.0f, 0.0f),	//74
		Vertex(width - paneWidth, height - paneWidth, -0.2f,			U2, V2,				0.0f, 1.0f, 0.0f),	//75
		// Inner Back Bottom Face
		Vertex(-width + paneWidth, -height + paneWidth, -0.2f,			U1, V2,				0.0f, -1.0f, 0.0f),	//76
		Vertex(-width + paneWidth, -height + paneWidth,  -depth,		U1, V1,				0.0f, -1.0f, 0.0f),	//77
		Vertex(width - paneWidth, -height + paneWidth,  -depth,			U2, V1,				0.0f, -1.0f, 0.0f),	//78
		Vertex(width - paneWidth, -height + paneWidth, -0.2f,			U2, V2,				0.0f, -1.0f, 0.0f),	//79
	};

	return vertices;
}*/

std::vector<DWORD> Shape::CreateQuadIndices()
{
	std::vector<DWORD> indices = {
		// Front Face
		0,  1,  2,
		0,  2,  3,
		// Back Face
		4,  5,  6,
		4,  6,  7,
		// Top Face
		8,  9, 10,
		8, 10, 11,
		// Bottom Face
		12, 13, 14,
		12, 14, 15,
		// Left Face
		16, 17, 18,
		16, 18, 19,
		// Right Face
		20, 21, 22,
		20, 22, 23
	};
	return indices;
}

std::vector<DWORD> Shape::CreatePlaneIndices()
{
	std::vector<DWORD> indices = {
		0, 1, 2,
		0, 2, 3
	};
	return indices;
}

std::vector<DWORD> Shape::CreatePyramidIndices()
{
	std::vector<DWORD> indices = {
		// Front Face
		0,  1,  2,
		// Back Face
		5,  4,  3,
		// Bottom Face
		6,  7,  8,
		6,  8,  9,
		// Left Face
		10, 11, 12,
		// Right Face
		13, 14, 15,
	};
	return indices;
}

std::vector<DWORD> Shape::CreateShedIndices()
{
	std::vector<DWORD> indices = {
		// Front Face
		0,  1,  2,
		0,  2,  3,
		// Top Face
		6,  5,  4,
		7,  6,  4,
		// Bottom Face
		8,  9,  10,
		8,  10, 11,
		// Left Face
		12, 13, 14,
		// Right Face
		15, 16, 17,
	};
	return indices;
}

//maths wrong somewhere
/*
std::vector<DWORD> Shape::CreateWindowIndices()
{
	std::vector<DWORD> indices = {
		// Front Face
		4, 1, 0,
		4, 5, 1,
		6, 3, 2,
		6, 7, 3,
		5, 6, 8,
		8, 6, 9,
		10, 2, 1,
		10, 11, 2,
		// Back Face
		16, 13, 12,
		16, 17, 13,
		18, 15, 14,
		18, 19, 15,
		17, 18, 20,
		20, 18, 21,
		22, 14, 13,
		22, 23, 14,
		// Left Face
		24, 25, 26,
		24, 26, 27,
		// Right Face
		28, 29, 30,
		28, 30, 31,
		// Top Face
		32, 33, 34,
		32, 34, 35,
		// Bottom Face
		36, 37, 38,
		36, 38, 39,
		// Inner Front Face
		40, 42, 41,
		42, 43, 41,
		// Inner Back Face
		44, 46, 45,
		46, 47, 45,
		// Inner Left Front Face
		50, 49, 48,
		50, 48, 51,
		// Inner Right Front Face
		52, 53, 54,
		53, 54, 55,
		// Inner Left Back Face
		56, 57, 58,
		57, 58, 59,
		// Inner Right Back Face
		60, 61, 62,
		61, 62, 63,
		// Inner Front Top Face
		64, 65, 66,
		65, 66, 67,
		// Inner Front Bottom Face
		68, 69, 70,
		69, 70, 71,
		// Inner Back Top Face
		72, 73, 74,
		73, 74, 75,
		// Inner Back Bottom Face
		76, 77, 78,
		77, 78, 79
	};
	return indices;
}*/



//Doesn't work
/*std::vector<Shape::Vertex> Shape::CreateTVertices(float tWidth, float iWidth, float tHeight, float iHeight, float roomHeight)
{
	float totalWidth = 1;//(2 * tWidth) + iWidth;
	float _tWidth = tWidth / ((2 * tWidth) + iWidth);
	float _iWidth = iWidth / ((2 * tWidth) + iWidth);
	float totalHeight = 1;//tHeight + iHeight;
	float _tHeight = tHeight / (tHeight + iHeight);
	float _iHeight = iHeight / (tHeight + iHeight);

	//UVs will be broken for this one
	std::vector<Vertex> vertices
	{
		// 'A' Face
		Vertex(0.0f, roomHeight, 0.0f,							1.0f, 0.0f,		0.0f, 0.0f, 1.0f),
		Vertex(totalWidth, roomHeight, 0.0f,					0.0f, 0.0f,		0.0f, 0.0f, 1.0f),
		Vertex(0.0f, 0.0f, 0.0f,								1.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(totalWidth, 0.0f,  0.0f,							0.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		// 'BL' Face																  
		Vertex(0.0f, 0.0f, 0.0f,								0.0f, 0.0f,		1.0f, 0.0f, 0.0f),
		Vertex(0.0f, 0.0f, _tHeight,							1.0f, 0.0f,		1.0f, 0.0f, 0.0f),
		Vertex(0.0f, roomHeight, 0.0f,							0.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex(0.0f, roomHeight, _tHeight,						1.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		// 'BR' Face																  
		Vertex(totalWidth, 0.0f, 0.0f,							1.0f, 0.0f,		1.0f, 0.0f, 0.0f),
		Vertex(totalWidth, 0.0f, _tHeight,						0.0f, 0.0f,		1.0f, 0.0f, 0.0f),
		Vertex(totalWidth, roomHeight, 0.0f,					1.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex(totalWidth, roomHeight, _tHeight,				0.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		// Top Face																	  
		Vertex(0.0f, roomHeight, 0.0f,							0.0f, 0.0f,		0.0f, 1.0f, 0.0f),
		Vertex(totalWidth, roomHeight,  0.0f,					3.0f, 0.0f,		0.0f, 1.0f, 0.0f),
		Vertex(0.0f, roomHeight, _tHeight,						0.0f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(_tWidth, roomHeight, _tHeight,					1.0f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(_iWidth * _tWidth, roomHeight, _tHeight,			2.0f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(totalWidth, roomHeight, _tHeight,				3.0f, 1.0f,		0.0f, 1.0f, 0.0f),
		Vertex(_iWidth * _tWidth, roomHeight, totalHeight,		1.0f, 2.0f,		0.0f, 1.0f, 0.0f),
		Vertex(totalWidth, roomHeight, totalHeight,				2.0f, 2.0f,		0.0f, 1.0f, 0.0f),
		// Bottom Face																  
		Vertex(0.0f, 0.0f, 0.0f,								0.0f, 0.0f,		0.0f, -1.0f, 0.0f),
		Vertex(totalWidth, 0.0f,  0.0f,							3.0f, 0.0f,		0.0f, -1.0f, 0.0f),
		Vertex(0.0f, 0.0f, _tHeight,							0.0f, 1.0f,		0.0f, -1.0f, 0.0f),
		Vertex(_tWidth, 0.0f, _tHeight,							1.0f, 1.0f,		0.0f, -1.0f, 0.0f),
		Vertex(_tWidth + _iWidth, 0.0f, _tHeight,				2.0f, 1.0f,		0.0f, -1.0f, 0.0f),
		Vertex(totalWidth, 0.0f, _tHeight,						3.0f, 1.0f,		0.0f, -1.0f, 0.0f),
		Vertex(_tWidth + _iWidth, 0.0f, totalHeight,			1.0f, 2.0f,		0.0f, -1.0f, 0.0f),
		Vertex(totalWidth , 0.0f, totalHeight,					2.0f, 2.0f,		0.0f, -1.0f, 0.0f),
		// 'CL' Face																  
		Vertex(0.0f, 0.0f,  _tHeight,							0.0f, 0.0f,		0.0f, 0.0f, 1.0f),
		Vertex(0.0f, roomHeight,  _tHeight,						0.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		Vertex(_tWidth, 0.0f,  _tHeight,						1.0f, 0.0f,		0.0f, 0.0f, 1.0f),
		Vertex(_tWidth, roomHeight,  _tHeight,					1.0f, 1.0f,		0.0f, 0.0f, 1.0f),
		// 'CR' Face															 	  
		Vertex(totalWidth, 0.0f,  _tHeight,						1.0f, 0.0f,		0.0f, 0.0f, -1.0f),
		Vertex(totalWidth, roomHeight, _tHeight,				1.0f, 1.0f,		0.0f, 0.0f, -1.0f),
		Vertex(_tWidth + _iWidth, 0.0f,  _tHeight,				0.0f, 0.0f,		0.0f, 0.0f, -1.0f),
		Vertex(_tWidth + _iWidth, roomHeight,  _tHeight,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f),
		// 'DL' Face															 		  
		Vertex(_tWidth, 0.0f,  _tHeight,						0.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		Vertex(_tWidth, 0.0f,  totalHeight,						0.0f, 0.0f,		1.0f, 0.0f, 0.0f),
		Vertex(_tWidth, roomHeight, _tHeight,					1.0f, 0.0f,		1.0f, 0.0f, 0.0f),
		Vertex(_tWidth, roomHeight, totalHeight,				1.0f, 1.0f,		1.0f, 0.0f, 0.0f),
		// 'DR' Face																  
		Vertex(_tWidth + _iWidth, 0.0f,  _tHeight,				0.0f, 1.0f,		-1.0f, 0.0f, 0.0f),
		Vertex(_tWidth + _iWidth, 0.0f,  totalHeight,			0.0f, 0.0f,		-1.0f, 0.0f, 0.0f),
		Vertex(_tWidth + _iWidth, roomHeight, _tHeight,			1.0f, 0.0f,		-1.0f, 0.0f, 0.0f),
		Vertex(_tWidth + _iWidth, roomHeight, totalHeight,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f),
		// 'E' Face																	  
		Vertex(_tWidth, roomHeight, totalHeight,				0.0f, 1.0f,		0.0f, 0.0f, -1.0f),
		Vertex(_tWidth + _iWidth, roomHeight, totalHeight,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f),
		Vertex(_tWidth, 0.0f, totalHeight,						0.0f, 0.0f,		0.0f, 0.0f, -1.0f),
		Vertex(_tWidth + _iWidth, 0.0f, totalHeight,			1.0f, 0.0f,		0.0f, 0.0f, -1.0f),
	};

	return vertices;
}

std::vector<DWORD> Shape::CreateTIndices()
{
	std::vector<DWORD> indices = {
		//ANTI CLOCKWISE
		// 'A' Face
		0,  1,  2,
		1,  3,  2,
		// 'BL' Face
		7,  6,  4,
		7,  4,  5,
		// 'BR' Face
		11, 10, 8,
		11, 8, 9,
		// Top Face
		12, 17, 13,
		12, 14, 17,
		15, 19, 16,
		15, 18, 19,
		// Bottom Face
		20, 21, 25,
		20, 25, 22,
		23, 24, 27,
		23, 27, 26,
		// 'CL' Face
		28, 30, 29,
		29, 30, 31,
		// 'CR' Face
		32, 33, 35,
		32, 35, 34,
		// 'DL' Face
		36, 37, 38,
		37, 39, 38,
		// 'DR' Face
		40, 41, 42,
		41, 43, 42,
		// 'E' Face
		44, 46, 45,
		45, 46, 47,
	};
	return indices;
}*/