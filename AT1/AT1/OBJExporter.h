#pragma once
#include "Model.h"
#include "Shapes.h"
#include <vector>
#include <fstream>

namespace OBJExporter
{
	void Create(std::vector<Shape::Vertex> vertices, std::vector<DWORD> indices);
}