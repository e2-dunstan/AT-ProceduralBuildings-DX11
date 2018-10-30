#include "Renderer.h"
#include "Constants.h"

Renderer::Renderer()
{
}
Renderer::~Renderer()
{	
	swapChain->Release();
	device->Release();
	deviceContext->Release();
	renderTargetView->Release();
	depthStencilView->Release();
	depthStencilBuffer->Release();
	cbPerObjectBuffer->Release();
	wireframeState->Release();
	filledState->Release();
	transparency->Release();
	CCWcullMode->Release();
	CWcullMode->Release();
}

bool Renderer::InitDirect3D(HWND appWindow)
{
	//UINT createDeviceFlags = 0;
	//Describe our SwapChain Buffer
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Width = windowWidth;
	bufferDesc.Height = windowHeight;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Describe our SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = appWindow;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //alt-enter fullscreen, but won't resize the buffer

	//Create swap chain
	//result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG,
	//		NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
	//		&device, NULL, &deviceContext);

	HRESULT result = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,//D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device, 
		NULL,//&FeatureLevelsSupported,
		&deviceContext);

	if (FAILED(result))
	{
		OutputDebugString("FAILED \nRenderer.cpp InitDirect3D()");
		return false;
	}

	ID3D11Texture2D* backBufferTexture;
	//Get the buffer, store into back buffer texture
	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);

	result = device->CreateRenderTargetView(backBufferTexture, nullptr, &renderTargetView);
	backBufferTexture->Release();

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

	device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	//bind render target
	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	if (FAILED(result))
	{
		OutputDebugString("FAILED \nRenderer.cpp InitDirect3D()");
		return false;
	}
	
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

	D3D11_BUFFER_DESC matrixBufferDesc;
	ZeroMemory(&matrixBufferDesc, sizeof(D3D11_BUFFER_DESC));
	matrixBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	matrixBufferDesc.ByteWidth = sizeof(matrixBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = 0;
	matrixBufferDesc.MiscFlags = 0;
	HRESULT result = device->CreateBuffer(&matrixBufferDesc, NULL, &cbPerObjectBuffer);

	if (FAILED(result))
	{
		OutputDebugString("FAILED \nRenderer.cpp InitView()");
	}

	InitBlendStates();
	InitRenderStates();
}

void Renderer::InitRenderStates()
{
	//VLOG: SET MULTIPLE RASTERIZER STATES THEN APPLY ON DRAW

	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_NONE;
	device->CreateRasterizerState(&wireframeDesc, &wireframeState);

	D3D11_RASTERIZER_DESC filledDesc;
	ZeroMemory(&filledDesc, sizeof(D3D11_RASTERIZER_DESC));
	filledDesc.FillMode = D3D11_FILL_SOLID;
	filledDesc.CullMode = D3D11_CULL_BACK;
	device->CreateRasterizerState(&filledDesc, &filledState);

	D3D11_RASTERIZER_DESC noCullDesc;
	ZeroMemory(&noCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	noCullDesc.FillMode = D3D11_FILL_SOLID;
	noCullDesc.CullMode = D3D11_CULL_NONE;
	device->CreateRasterizerState(&noCullDesc, &noCullState);

	//Additional render states for cull modes
	filledDesc.FrontCounterClockwise = true;
	device->CreateRasterizerState(&filledDesc, &CCWcullMode);
	filledDesc.FrontCounterClockwise = false;
	device->CreateRasterizerState(&filledDesc, &CWcullMode);
}

void Renderer::InitBlendStates()
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
	rtbd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	device->CreateBlendState(&blendDesc, &transparency);

}

void Renderer::DrawBackground()
{
	//Sets background colour
	deviceContext->ClearRenderTargetView(renderTargetView, DirectX::Colors::MistyRose);
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Renderer::SetRasterizerState(int state)
{
	switch (state)
	{
	case 0:
		deviceContext->RSSetState(filledState);
		break;
	case 1:
		deviceContext->RSSetState(noCullState);
		break;
	default:
		deviceContext->RSSetState(wireframeState);
		break;
	}
}

void Renderer::SetBlendState(int state)
{
	float blendFactor[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	switch (state)
	{
	//transparent
	case 0:
		deviceContext->OMSetBlendState(transparency, blendFactor, 0xffffffff);
		break;
	//opaque
	case 1:
		deviceContext->OMSetBlendState(0, 0, 0xffffffff);
		break;
	default:
		deviceContext->OMSetBlendState(0, 0, 0xffffffff);
		break;
	}
}

void Renderer::DrawModel(ID3D11ShaderResourceView *textureShader, ID3D11SamplerState *samplerState, 
	XMMATRIX cameraView, XMMATRIX camProjection, int i, int indexCount)
{
	WVP = _modelTransforms[i] * cameraView * camProjection;
	matrixBuffer.WVP = XMMatrixTranspose(WVP);
	deviceContext->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &matrixBuffer, 0, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
	deviceContext->PSSetShaderResources(0, 1, &textureShader);
	deviceContext->PSSetSamplers(0, 1, &samplerState);
	deviceContext->DrawIndexed(indexCount, 0, 0);
}

void Renderer::EndFrame()
{
	swapChain->Present(0, 0);
}

void Renderer::SetModelTransforms(std::vector<XMMATRIX> modelTransforms)
{
	_modelTransforms = modelTransforms;
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

XMMATRIX Renderer::GetWorldMatrix()
{
	return World;
}
