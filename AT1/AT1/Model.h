#pragma once
#include "Renderer.h"

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float r, float g, float b, float a)
		: pos(x, y, z), colour(r, g, b, a) {}

	XMFLOAT3 pos;
	XMFLOAT4 colour;
};

class Model
{
public:
	Model();
	~Model();

	bool InitModel(Renderer& renderer);
	void CreateMesh(Renderer& renderer);
	void CreateShaders(Renderer& renderer);
	void CreateRenderStates(Renderer& renderer);

private:

	//ID3D11Buffer* triangleVertexBuffer = nullptr;
	ID3D11Buffer* squareVertexBuffer = nullptr;
	ID3D11Buffer* squareIndexBuffer = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
	ID3D11RasterizerState* rasteriserState = nullptr;
	ID3D11DepthStencilState* depthState = nullptr;
	ID3D11BlendState* blendState = nullptr;
};