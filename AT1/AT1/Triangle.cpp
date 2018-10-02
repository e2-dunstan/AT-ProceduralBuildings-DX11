#include "Triangle.h"
#include <fstream>
#include <vector>

struct Vertex
{
	//each float 4 bytes, 32 bits
	float x, y;
	float r, g, b;
};

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
	vertexBuffer->Release();
	vertexShader->Release();
	pixelShader->Release();
	inputLayout->Release();
}

bool Triangle::InitTriangle(Renderer& renderer)
{
	CreateMesh(renderer);
	CreateShaders(renderer);
	return true;
}

void Triangle::Draw(Renderer& renderer)
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
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);	//look at function requirements for help

	//draw
	deviceContext->Draw(3, 0);
}

void Triangle::CreateMesh(Renderer & renderer)
{
	//define vertices
	Vertex vertices[]
	{
		{-1, -1, 1, 0, 0},	//red at bottom left
		{0, 1, 0, 1, 0},	//green at top middle
		{1, -1, 0, 0, 1},	//blue at bottom right
	}; //sizeof = total bytes/bits

	//create vertex buffer
	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices),
		D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = vertices;

	renderer.GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
}

void Triangle::CreateShaders(Renderer & renderer)
{
	std::ifstream vsFile("TriangleVertexShader.cso", std::ios::binary);
	std::ifstream psFile("TrianglePixelShader.cso", std::ios::binary);

	std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	std::vector<char> psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };

	renderer.GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	renderer.GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);

	//create input layouts
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//2 parameters. See Input data in shader
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		//use append element for each following parameter
	};
	renderer.GetDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &inputLayout);

}
