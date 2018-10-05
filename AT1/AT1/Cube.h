#pragma once
#include "Renderer.h"

class Cube
{
public:
	Cube();
	~Cube();

	void CreateShaders(Renderer& renderer);

private:
	ID3D11VertexShader * vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
};