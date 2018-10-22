#pragma once
#include "DXApp.h"
//#include "Shapes.h"

namespace OBJExporter
{
	void Create();

	static std::vector<Shape::Vertex> allVertices;
	static std::vector<DWORD> allIndices;
}