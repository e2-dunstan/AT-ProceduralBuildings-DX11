#pragma once
#include "Model.h"
#include <vector>

namespace Shape
{
	struct Vertex
	{
		Vertex() {}
		Vertex(float x, float y, float z,
			float u, float v,
			float nx, float ny, float nz)
			: pos(x, y, z), texture(u, v), normal(nx, ny, nz) {}

		XMFLOAT3 pos;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	std::vector<Vertex> CreateSquareVertices(float width, float height);
	std::vector<DWORD> CreateSquareIndices();
	std::vector<Vertex> CreateTVertices(float tWidth, float iWidth, float tHeight, float iHeight, float roomHeight);
	std::vector<DWORD> CreateTIndices();
	void CreateL(float topWidth, float baseWidth, float height, float baseHeight);
}