#pragma once
#include "DXUtil.h"
#include "Light.h"

using namespace DirectX;

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool InitDirect3D(HWND appWindow);
	void InitView();
	void InitRenderStates();
	void InitBlendStates();

	void DrawBackground();
	void SetRasterizerState(int state);
	void SetBlendState(int state);
	void DrawModel(ID3D11ShaderResourceView *textureShader, 
		ID3D11SamplerState *samplerState, XMMATRIX cameraView, XMMATRIX camProjection,
		int i, int indexCount);
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

	struct CBPerObject
	{
		XMMATRIX  WVP;
		XMMATRIX World;
	};
	CBPerObject cbPerObject;

	struct CBPerFrame
	{
		Light light;
	};
	CBPerFrame cbPerFrame;

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
	ConstantBuffer constantBufferData;

	ID3D11RasterizerState* wireframeState = nullptr;
	ID3D11RasterizerState* filledState = nullptr;
	ID3D11RasterizerState* noCullState = nullptr;

	ID3D11BlendState* transparency;
	ID3D11RasterizerState* CCWcullMode;
	ID3D11RasterizerState* CWcullMode;

	ID3D11Buffer* cbPerObjectBuffer = nullptr;
	ID3D11Buffer* cbPerFrameBuffer = nullptr;

	std::vector<XMMATRIX> _modelTransforms;

	XMMATRIX WVP;
	XMMATRIX World;

	LightClass lightClass;
};

