#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#pragma once
#include "Renderer.h"
#include <stdio.h>

using namespace DirectX;

class Texture
{
public:
	Texture();
	Texture(const Texture&);
	~Texture();

	bool Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename, HWND hwnd);
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, 
		ID3D11ShaderResourceView* texture);

	bool InitShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd,
		WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture);
	void RenderShader(ID3D11DeviceContext*, int);

	ID3D11ShaderResourceView* GetTexture();
	bool LoadTarga(char* filename, int& height, int& width);

	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

private:
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* layout = nullptr;
	ID3D11Buffer* matrixBuffer = nullptr;
	ID3D11SamplerState* sampleState = nullptr;

	unsigned char* targaData = nullptr;
	ID3D11Texture2D* texture = nullptr;
	ID3D11ShaderResourceView* textureView = nullptr;
};

#endif