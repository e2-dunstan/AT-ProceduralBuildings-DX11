#pragma once
#include "Renderer.h"

class Triangle
{
public:
	Triangle();
	~Triangle();

	bool InitTriangle(Renderer& renderer);
	void Draw(Renderer& renderer);
	void CreateMesh(Renderer& renderer);
	void CreateShaders(Renderer& renderer);
	void CreateRenderStates(Renderer& renderer);

private:

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
	ID3D11RasterizerState* rasteriserState = nullptr;
	ID3D11DepthStencilState* depthState = nullptr;
	ID3D11BlendState* blendState = nullptr;
};