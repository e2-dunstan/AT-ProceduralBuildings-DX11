#include "Renderer.h"
#include "Constants.h"


struct cbPerObject
{
	XMMATRIX  WVP;
};
cbPerObject cbPerObj;

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

	renderTargetView->Release();
	swapChain->Release();
	deviceContext->Release();
	device->Release();
	depthStencilView->Release();
	depthStencilBuffer->Release();
	//constantBuffer->Release();
	cbPerObjectBuffer->Release();
}

bool Renderer::InitDirect3D(HWND appWindow)
{
	UINT createDeviceFlags = 0;

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = windowWidth;
	depthStencilDesc.Height = windowHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;


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


	HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL,
			NULL, NULL, D3D11_SDK_VERSION, &swapDesc, &swapChain,
			&device, NULL, &deviceContext);

	if (FAILED(result))
	{
		OutputDebugString("FAILED TO CREATE DEVICE AND SWAP CHAIN \nDXApp.cpp InitDirect3D()");
		return false;
	}

	ID3D11Texture2D* backBufferTexture;
	//Get the buffer, store into back buffer texture
	swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBufferTexture));
	device->CreateRenderTargetView(backBufferTexture, nullptr, &renderTargetView);
	backBufferTexture->Release();

	device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	//bind render target
	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
	
	return true;
}

void Renderer::InitView()
{	
	viewport.Width = (float)windowWidth;
	viewport.Height = (float)windowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	//rs = rasteriser stage
	deviceContext->RSSetViewports(1, &viewport);

	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;
	device->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);

	deviceContext->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	camPosition = XMVectorSet(0.0f, 3.0f, -8.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
	camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, (float)windowWidth / windowHeight, 1.0f, 1000.0f);
}

void Renderer::DrawScene()
{
	//Sets background colour
	deviceContext->ClearRenderTargetView(renderTargetView, DirectX::Colors::PaleVioletRed);
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Set the WVP matrix and send it to the constant buffer in effect file
	WVP = _cube1World * camView * camProjection;
	cbPerObj.WVP = XMMatrixTranspose(WVP);
	deviceContext->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);

	//Draw the first cube
	deviceContext->DrawIndexed(36, 0, 0);

	WVP = _cube2World * camView * camProjection;
	cbPerObj.WVP = XMMatrixTranspose(WVP);
	deviceContext->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);

	//Draw the second cube
	deviceContext->DrawIndexed(36, 0, 0);
}

void Renderer::EndFrame()
{
	swapChain->Present(0, 0);
}

void Renderer::SetCubeWorldTransforms(XMMATRIX cube1World, XMMATRIX cube2World)
{
	_cube1World = cube1World;
	_cube2World = cube2World;
}

ID3D11Device * Renderer::GetDevice()
{
	return device;
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
