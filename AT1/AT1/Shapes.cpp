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
		Vertex(-width, height, -depth,			0.0f, 1.0f,			0.0f, 1.0f, 0.0f),
		Vertex(-width, height,  depth,			0.0f, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, height,  depth,			1.0f, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, height, -depth,			1.0f, 1.0f,			0.0f, 1.0f, 0.0f),
		// Bottom Face
		Vertex(-width, -height, -depth,			1.0f, 1.0f,			0.0f, -1.0f, 0.0f),
		Vertex(width, -height, -depth,			0.0f, 1.0f,			0.0f, -1.0f, 0.0f),
		Vertex(width, -height,  depth,			0.0f, 0.0f,			0.0f, -1.0f, 0.0f),
		Vertex(-width, -height,  depth,			1.0f, 0.0f,			0.0f, -1.0f, 0.0f),
		// Left Face
		Vertex(-width, -height,  depth,			0.0f, 1.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width,  height,  depth,			0.0f, 0.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width,  height, -depth,			1.0f, 0.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width, -height, -depth,			1.0f, 1.0f,			-1.0f, 0.0f, 0.0f),
		// Right Face
		Vertex(width, -height, -depth,			0.0f, 1.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width,  height, -depth,			0.0f, 0.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width,  height,  depth,			1.0f, 0.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width, -height,  depth,			1.0f, 1.0f,			1.0f, 0.0f, 0.0f),
	};

	return vertices;
}

std::vector<Vertex> Shape::CreateFloorVertices(float width, float height, float depth)
{
	width *= 0.5f;
	depth *= 0.5f;

	std::vector<Vertex> vertices
	{
		Vertex(-width, height, -depth,			0.0f, 10.0f,			0.0f, 1.0f, 0.0f),
		Vertex(-width, height,  depth,			0.0f, 0.0f,				0.0f, 1.0f, 0.0f),
		Vertex(width, height,  depth,			10.0f, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, height, -depth,			10.0f, 10.0f,			0.0f, 1.0f, 0.0f),
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
		Vertex(-width,  height, -width,			0.0f, 0.0f,			0.0f, 0.0f, -1.0f),
		Vertex(width,  height, -width,			1.0f, 0.0f,			0.0f, 0.0f, -1.0f),
		Vertex(width, -height, -width,			1.0f, 1.0f,			0.0f, 0.0f, -1.0f),
		// Back Face
		Vertex(-width, -height, width,			1.0f, 1.0f,			0.0f, 0.0f, 1.0f),
		Vertex(width, -height, width,			0.0f, 1.0f,			0.0f, 0.0f, 1.0f),
		Vertex(width,  height, width,			0.0f, 0.0f,			0.0f, 0.0f, 1.0f),
		Vertex(-width,  height, width,			1.0f, 0.0f,			0.0f, 0.0f, 1.0f),
		// Top Face
		Vertex(-width, height, -width,			0.0f, 1.0f,			0.0f, 1.0f, 0.0f),
		Vertex(-width, height,  width,			0.0f, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, height,  width,			1.0f, 0.0f,			0.0f, 1.0f, 0.0f),
		Vertex(width, height, -width,			1.0f, 1.0f,			0.0f, 1.0f, 0.0f),
		// Bottom Face
		Vertex(-width, -height, -width,			1.0f, 1.0f,			0.0f, -1.0f, 0.0f),
		Vertex(width, -height, -width,			0.0f, 1.0f,			0.0f, -1.0f, 0.0f),
		Vertex(width, -height,  width,			0.0f, 0.0f,			0.0f, -1.0f, 0.0f),
		Vertex(-width, -height,  width,			1.0f, 0.0f,			0.0f, -1.0f, 0.0f),
		// Left Face
		Vertex(-width, -height,  width,			0.0f, 1.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width,  height,  width,			0.0f, 0.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width,  height, -width,			1.0f, 0.0f,			-1.0f, 0.0f, 0.0f),
		Vertex(-width, -height, -width,			1.0f, 1.0f,			-1.0f, 0.0f, 0.0f),
		// Right Face
		Vertex(width, -height, -width,			0.0f, 1.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width,  height, -width,			0.0f, 0.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width,  height,  width,			1.0f, 0.0f,			1.0f, 0.0f, 0.0f),
		Vertex(width, -height,  width,			1.0f, 1.0f,			1.0f, 0.0f, 0.0f),
	};

	return vertices;
}

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