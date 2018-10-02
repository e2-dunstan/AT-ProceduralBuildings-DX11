#pragma once
#include "Renderer.h"

class Triangle
{
public:
	Triangle();
	~Triangle();

	bool InitTriangle(Renderer& renderer);
	void Draw(Renderer& renderer);

private:
	void CreateMesh(Renderer& renderer);
	void CreateShaders(Renderer& renderer);

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
};