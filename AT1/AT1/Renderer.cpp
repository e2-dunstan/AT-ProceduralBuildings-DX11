#include "Renderer.h"
#include "Constants.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
	//Clean up D3D
	if (deviceContext)
	{
		deviceContext->ClearState();
	}
	Memory::SafeRelease(renderTargetView);
	Memory::SafeRelease(swapChain);
	Memory::SafeRelease(deviceContext);
	Memory::SafeRelease(device);
}

bool Renderer::InitDirect3D(HWND appWindow)
{
	UINT createDeviceFlags = 0;

	//#ifdef _DEBUG
	//	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	//#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		//GPU or integrated for sliding transforms
		D3D_DRIVER_TYPE_HARDWARE,
		//Emulated if don't have above. Rarely used.
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		//Will most likely only need 11
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	//Swap chains: front buffer and back buffer
	//Swaps between the two to e.g. smooth out animation
	//This handles how they swap out
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;	//double buffer. 0 is single buffer
	swapDesc.BufferDesc.Width = windowWidth;
	swapDesc.BufferDesc.Height = windowHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;	//8 bits for each
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;	//60 FPS
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = appWindow;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //fast and efficient
	swapDesc.Windowed = true;
	swapDesc.SampleDesc.Count = 1;	//anti-aliasing for geometry, lowers performance
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //alt-enter fullscreen, but won't resize the buffer

															 //sets driver type
	HRESULT result;
	for (int i = 0; i < numDriverTypes; i++)
	{
		result = D3D11CreateDeviceAndSwapChain(NULL, driverTypes[i], NULL, createDeviceFlags,
			featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &swapDesc, &swapChain,
			&device, &featureLevel, &deviceContext);
		
		if (SUCCEEDED(result))
		{
			driverType = driverTypes[i];
			break;
		}
		//m_pDevice is related to shaders
	}
	if (FAILED(result))
	{
		OutputDebugString("FAILED TO CREATE DEVICE AND SWAP CHAIN \nDXApp.cpp InitDirect3D()");
		return false;
	}

	//Create render target view (camera?)
	ID3D11Texture2D* m_pBackBufferTex = 0;
	//Get the buffer, store into back buffer texture
	swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pBackBufferTex));
	device->CreateRenderTargetView(m_pBackBufferTex, nullptr, &renderTargetView);

	//Bind render target view
	deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);	//nullptr is depth stencil view for shadow maps. Will implement later

																				//Viewport creation
	viewport.Width = static_cast<float>(windowWidth);
	viewport.Height = static_cast<float>(windowHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Bind viewport
	deviceContext->RSSetViewports(1, &viewport);

	return true;
}

ID3D11DeviceContext * Renderer::GetDeviceContext()
{
	return deviceContext;
}

ID3D11RenderTargetView * Renderer::GetRenderTargetView()
{
	return renderTargetView;
}

IDXGISwapChain * Renderer::GetSwapChain()
{
	return swapChain;
}
