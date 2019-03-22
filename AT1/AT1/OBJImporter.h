#pragma once
#include "Model.h"

class OBJImporter
{
public:
	OBJImporter() = default;
	~OBJImporter() = default;

	void ReadOBJ(std::string filename);

	std::vector<Vertex> GetVertices();
	std::vector<DWORD> GetIndices();

private:

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;
};