#pragma once
#include "Model.h"
#include <vector>
#include <fstream>

namespace OBJExporter
{
	void Create(std::vector<Model::Vertex> vertices, std::vector<DWORD> indices);
}