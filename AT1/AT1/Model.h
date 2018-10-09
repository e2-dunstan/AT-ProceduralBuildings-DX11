#pragma once
#include "Renderer.h"
#include "Texture.h"

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float u, float v)
		: pos(x, y, z), tCoord(u, v) {}

	XMFLOAT3 pos;
	XMFLOAT2 tCoord;
};

class Model
{
public:
	Model();
	~Model();

	bool InitModel(Renderer& renderer);
	void CreateMesh(Renderer& renderer);
	void CreateShaders(Renderer& renderer);

private:

	//ID3D11Buffer* triangleVertexBuffer = nullptr;
	ID3D11Buffer* squareVertexBuffer = nullptr;
	ID3D11Buffer* squareIndexBuffer = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;

	//ID3D11DepthStencilState* depthState = nullptr;
	//ID3D11BlendState* blendState = nullptr;
};