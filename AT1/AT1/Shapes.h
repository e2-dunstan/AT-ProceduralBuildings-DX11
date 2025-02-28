#pragma once
#include "DXUtil.h"

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float u, float v,
		float nx, float ny, float nz)
		: pos(x, y, z), texture(u, v), normal(nx, ny, nz) {}

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 texture;
	DirectX::XMFLOAT3 normal;
};

namespace Shape
{
	std::vector<Vertex> CreateSquareVertices(float width, float height, float depth);
	std::vector<Vertex> CreateLargeSquareVertices(float width, float height, float depth);
	std::vector<Vertex> CreateFloorVertices(float width, float height, float depth);
	std::vector<Vertex> CreateCornerVertices(float width, float height); //depth = width
	std::vector<Vertex> CreatePyramidVertices(float width, float height, float depth);
	std::vector<Vertex> CreateShedVertices(float width, float height, float depth);
	//std::vector<Vertex> CreateWindowVertices(float width, float height, float depth);
	//std::vector<Vertex> CreateDoorVertices(float width, float height, float depth);

	std::vector<DWORD> CreateQuadIndices();
	std::vector<DWORD> CreatePlaneIndices();
	std::vector<DWORD> CreatePyramidIndices();
	std::vector<DWORD> CreateShedIndices();
	//std::vector<DWORD> CreateWindowIndices();

	//std::vector<Vertex> CreateTVertices(float tWidth, float iWidth, float tHeight, float iHeight, float roomHeight);
	//std::vector<DWORD> CreateTIndices();
}