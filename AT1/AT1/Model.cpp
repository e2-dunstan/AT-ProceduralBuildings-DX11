#include "Model.h"
#include <fstream>
#include <vector>


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
	CreateShaders(renderer);
	CreateMesh(renderer);
	CreateRenderStates(renderer);
	return true;
}

void Model::CreateMesh(Renderer & renderer)
{
	//define vertices
	Vertex vertices[]
	{
		//x, y, z, r, g, b, a
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

	//--CREATE BUFFERS--//

	//Create index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 12 * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	renderer.GetDevice()->CreateBuffer(&indexBufferDesc, &iinitData, &squareIndexBuffer);
	renderer.GetDeviceContext()->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//Create vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 8;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices;
	renderer.GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &squareVertexBuffer);

	//bind vertex buffer
	UINT stride = sizeof(Vertex);	//size between each vertex
	UINT offset = 0;
	renderer.GetDeviceContext()->IASetVertexBuffers(0, 1, &squareVertexBuffer, &stride, &offset);	//look at function requirements for help
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
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		//use append element for each following parameter
	};
	UINT numElements = ARRAYSIZE(layout);
	renderer.GetDevice()->CreateInputLayout(layout, numElements, vsData.data(), vsData.size(), &inputLayout);
	renderer.GetDeviceContext()->IASetInputLayout(inputLayout);
	renderer.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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
