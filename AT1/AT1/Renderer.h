#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include "DXUtil.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	//Initialise DX
	bool InitDirect3D(HWND appWindow);
	void CreateRenderTarget();

	void BeginFrame();
	void EndFrame();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	ID3D11RenderTargetView* GetRenderTargetView();
	IDXGISwapChain*	GetSwapChain();

protected:
	//DX Attributes
	ID3D11Device *			device = nullptr;
	ID3D11DeviceContext*	deviceContext = nullptr;
	IDXGISwapChain*			swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	D3D_DRIVER_TYPE			driverType;
	D3D_FEATURE_LEVEL		featureLevel;
	D3D11_VIEWPORT			viewport;
};

