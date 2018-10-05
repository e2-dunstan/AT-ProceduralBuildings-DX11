#include "Model.h"
#include <fstream>
#include <vector>

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z,
		float r, float g, float b, float a)
		: pos(x, y, z), colour(r, g, b, a) {}

	XMFLOAT3 pos;
	XMFLOAT4 colour;
};

Model::Model()
{
}

Model::~Model()
{
	//triangleVertexBuffer->Release();

	squareVertexBuffer->Release();
	squareIndexBuffer->Release();
	vertexShader->Release();
	pixelShader->Release();
	inputLayout->Release();
}

bool Model::InitModel(Renderer& renderer)
{
	CreateMesh(renderer);
	CreateShaders(renderer);
	CreateRenderStates(renderer);
	return true;
}

void Model::CreateMesh(Renderer & renderer)
{
	//define vertices
	Vertex vertices[]
	{
		Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(-1.0f, +1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
		Vertex(+1.0f, +1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
		Vertex(+1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
		Vertex(-1.0f, -1.0f, +1.0f, 0.0f, 1.0f, 1.0f, 1.0f),
		Vertex(-1.0f, +1.0f, +1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
		Vertex(+1.0f, +1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
		Vertex(+1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
	}; //sizeof = total bytes/bits

	DWORD indices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,
		// back face
		4, 6, 5,
		4, 7, 6,
		// left face
		4, 5, 1,
		4, 1, 0,
		// right face
		3, 2, 6,
		3, 6, 7,
		// top face
		1, 5, 6,
		1, 6, 2,
		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 12 * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	//create vertex buffer
	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices) * 8,
		D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = vertices;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;

	renderer.GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &squareVertexBuffer);
	renderer.GetDevice()->CreateBuffer(&indexBufferDesc, &iinitData, &squareIndexBuffer);
}

void Model::CreateShaders(Renderer & renderer)
{
	std::ifstream vsFile("TriangleVertexShader.cso", std::ios::binary);
	std::ifstream psFile("TrianglePixelShader.cso", std::ios::binary);

	std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	std::vector<char> psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };

	renderer.GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	renderer.GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);

	//create input layout description
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//2 parameters. See Input data in shader
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		//use append element for each following parameter
	};
	renderer.GetDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &inputLayout);
}

void Model::CreateRenderStates(Renderer & renderer)
{
	auto rasteriserDesc = CD3D11_RASTERIZER_DESC(
		D3D11_FILL_SOLID, D3D11_CULL_NONE, false,
		0, 0, 0, 0, false, false, false);
	renderer.GetDevice()->CreateRasterizerState(&rasteriserDesc, &rasteriserState);

	auto blendDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
	renderer.GetDevice()->CreateBlendState(&blendDesc, &blendState);

	auto depthDesc = CD3D11_DEPTH_STENCIL_DESC(
		FALSE, D3D11_DEPTH_WRITE_MASK_ZERO, D3D11_COMPARISON_LESS,
		FALSE, D3D11_DEFAULT_STENCIL_READ_MASK, D3D11_DEFAULT_STENCIL_WRITE_MASK,
		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS,
		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS);
	renderer.GetDevice()->CreateDepthStencilState(&depthDesc, &depthState);
}

void Model::Draw(Renderer& renderer)
{
	auto deviceContext = renderer.GetDeviceContext();
	//bind triangle shaders
	deviceContext->IASetInputLayout(inputLayout);
	deviceContext->VSSetShader(vertexShader, nullptr, 0);
	deviceContext->PSSetShader(pixelShader, nullptr, 0);

	//bind vertex buffer
	UINT stride = sizeof(Vertex);	//size between each vertex
	UINT offset = 0;
	//IA = input assembler. See DX graphics pipeline
	deviceContext->IASetVertexBuffers(0, 1, &squareVertexBuffer, &stride, &offset);	//look at function requirements for help
	deviceContext->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//draw
	deviceContext->DrawIndexed(6, 0, 0);
}
