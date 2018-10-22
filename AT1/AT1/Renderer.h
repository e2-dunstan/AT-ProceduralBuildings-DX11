#pragma once
#include "DXUtil.h"

using namespace DirectX;

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool InitDirect3D(HWND appWindow);
	void InitView();
	void InitRenderStates();

	void DrawBackground();
	void DrawModel(ID3D11ShaderResourceView *textureShader, 
		ID3D11SamplerState *samplerState, XMMATRIX cameraView, XMMATRIX camProjection,
		int i);
	void EndFrame();

	struct SimpleCubeVertex
	{
		XMFLOAT3 pos;   // Position
		XMFLOAT3 color; // Color
	};

	struct ConstantBuffer
	{
		XMMATRIX model;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct MatrixBufferType
	{
		XMMATRIX  WVP;
	};
	MatrixBufferType matrixBuffer;

	void SetModelTransforms(std::vector<XMMATRIX> modelTransforms);

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	ID3D11RenderTargetView* GetRenderTargetView();
	IDXGISwapChain*	GetSwapChain();

	XMMATRIX GetWorldMatrix();

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
	ID3D11Texture2D* depthStencilBuffer = nullptr;
	//ID3D11Buffer* constantBuffer;
	ConstantBuffer constantBufferData;

	ID3D11RasterizerState* wireframeState = nullptr;
	ID3D11RasterizerState* filledState = nullptr;

	ID3D11Buffer* cbPerObjectBuffer = nullptr;

	std::vector<XMMATRIX> _modelTransforms;

	XMMATRIX WVP;
	XMMATRIX World;

	//XMMATRIX camView;
	//XMMATRIX camProjection;
	//
	//XMVECTOR camPosition;
	//XMVECTOR camTarget;
	//XMVECTOR camUp;
};

