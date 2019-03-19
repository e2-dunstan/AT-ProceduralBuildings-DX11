#pragma once
#include "Model.h"

class OBJImporter
{
public:
	OBJImporter() = default;
	~OBJImporter() = default;

	void ReadOBJs(std::string filename);

private:

	std::vector<Vertex*> vertices;
	std::vector<DWORD> indices;
};