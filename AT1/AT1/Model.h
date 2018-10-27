#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "Shapes.h"


enum Type
{
	WALL, FLOOR, CORNER, WINDOW, DOOR
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
	void SetTextureString(std::string texStr);
	std::string GetTextureString();

	XMFLOAT3 GetPosition();
	void SetPosition(XMFLOAT3 pos);
	float GetRotation();
	Type GetType();

	std::vector<Vertex> & GetVertices();
	std::vector<DWORD> & GetIndices();

private:
	const long double PI = 3.141592653589793238L;

	Type type;
	float w = 1;
	float h = 1;
	float d = 1;
	float r = 0;
	//Position position;
	XMFLOAT3 position;
	
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11Buffer* matrixBuffer = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;

	Texture* texture = nullptr;
	std::string textureStr;

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;

	//ID3D11DepthStencilState* depthState = nullptr;
	//ID3D11BlendState* blendState = nullptr;
};