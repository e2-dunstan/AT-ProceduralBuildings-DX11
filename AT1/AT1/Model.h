#pragma once
#include "Renderer.h"
#include "Texture.h"

class Model
{
public:
	Model();
	~Model();

	bool InitModel(Renderer& renderer, char* textureFilename, HWND hwnd);
	void CreateMesh(Renderer& renderer);
	void CreateShaders(Renderer& renderer);

	ID3D11ShaderResourceView* GetTexture();
	Texture* GetTexturePointer();
	bool LoadTexture(Renderer& renderer, char* filename, HWND hwnd);

	struct Vertex
	{
		Vertex() {}
		Vertex(float x, float y, float z,
			float u, float v, 
			float nx, float ny, float nz)
			: pos(x, y, z), texture(u, v), normal(nx, ny, nz) {}

		XMFLOAT3 pos;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

private:
	//ID3D11Buffer* triangleVertexBuffer = nullptr;
	ID3D11Buffer* squareVertexBuffer = nullptr;
	ID3D11Buffer* squareIndexBuffer = nullptr;
	ID3D11Buffer* matrixBuffer = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;

	Texture* texture = nullptr;

	//ID3D11DepthStencilState* depthState = nullptr;
	//ID3D11BlendState* blendState = nullptr;
};