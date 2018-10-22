#pragma once
#include "DXUtil.h"
#include "Shapes.h"

class OBJExporter
{
public:
	OBJExporter() = default;
	~OBJExporter() = default;

	void Create();
	void SetVertices(std::vector<Vertex> newVertices);
	void SetIndices(std::vector<DWORD> newIndices);

private:
	std::vector<Vertex> allVertices;
	std::vector<DWORD> allIndices;
};
