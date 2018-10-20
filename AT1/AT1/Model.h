#pragma once
#include <vector>
#include "Renderer.h"
#include "Texture.h"
#include "Shapes.h"

enum Type
{
	WALL, FLOOR, CORNER
};

struct Position
{
	float x;
	float y;
	float z;
};

class Model
{
public: 
	Model(Type modelType, int width, int height, int depth,
			float posX, float posY, float posZ, float rotation);
	~Model();

	bool InitModel(Renderer& renderer, char* textureFilename, HWND hwnd);
	void CreateMesh(Renderer& renderer);
	void CreateShaders(Renderer& renderer);

	void UpdateBuffers(Renderer& renderer);

	ID3D11ShaderResourceView* GetTexture();
	Texture* GetTexturePointer();
	bool LoadTexture(Renderer& renderer, char* filename, HWND hwnd);

	Position GetPosition();
	float GetRotation();
	Type GetType();

private:
	const long double PI = 3.141592653589793238L;

	Type type;
	int w = 1;
	int h = 1;
	int d = 1;
	float r = 0;
	Position position;

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11Buffer* matrixBuffer = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;

	Texture* texture = nullptr;

	//ID3D11DepthStencilState* depthState = nullptr;
	//ID3D11BlendState* blendState = nullptr;
};