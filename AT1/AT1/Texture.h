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
	bool InitShader(ID3D11Device* device);

	ID3D11ShaderResourceView* GetTexture();
	ID3D11SamplerState* GetSamplerState();

	bool LoadTarga(char* filename, int& height, int& width);

	//struct MatrixBufferType
	//{
	//	XMMATRIX world;
	//	XMMATRIX view;
	//	XMMATRIX projection;
	//};
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

private:
	
	ID3D11SamplerState* sampleState = nullptr;
	unsigned char* targaData = nullptr;
	ID3D11Texture2D* texture = nullptr;
	ID3D11ShaderResourceView* textureView = nullptr;
};

#endif