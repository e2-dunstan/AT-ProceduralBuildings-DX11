#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include "DXUtil.h"

using namespace DirectX;

struct SimpleCubeVertex
{
	XMFLOAT3 pos;   // Position
	XMFLOAT3 color; // Color
};

struct ConstantBuffer
{
	XMFLOAT4X4 model;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};


class Renderer
{
public:
	Renderer();
	~Renderer();

	//Initialise DX
	bool InitDirect3D(HWND appWindow);
	void CreateRenderTarget();

	void BeginFrame();
	void Draw();
	void EndFrame();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	ID3D11RenderTargetView* GetRenderTargetView();
	IDXGISwapChain*	GetSwapChain();

protected:
	//DX Attributes
	ID3D11Device*			device = nullptr;
	ID3D11DeviceContext*	deviceContext = nullptr;
	IDXGISwapChain*			swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	D3D_DRIVER_TYPE			driverType;
	D3D_FEATURE_LEVEL		featureLevel;
	D3D11_VIEWPORT			viewport;

	//render objects closer to the camera in front of objects further from the camera
	ID3D11DepthStencilView* depthStencilView = nullptr;
	std::unique_ptr<ID3D11Buffer> constantBuffer;
	ConstantBuffer constantBufferData;
};

