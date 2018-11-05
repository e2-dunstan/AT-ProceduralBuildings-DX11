#pragma once
#include "DXUtil.h"
#include "Model.h"

class OBJExporter
{
public:
	OBJExporter() = default;
	~OBJExporter() = default;

	void Create();
	void SetModels(std::vector<Model*> models);
	void SetTransforms(std::vector<XMMATRIX> _transforms);

private:
	void SetVertices(std::vector<Vertex> newVertices, int i);
	void SetIndices(std::vector<DWORD> newIndices);
	void ClearVertices();
	void ClearIndices();

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;
	std::vector<Model*> models;
	std::vector<XMMATRIX> transforms;
	std::vector<std::string> textures;
};
