#include "Cube.h"
#include <fstream>
#include <vector>

Cube::Cube()
{
}

Cube::~Cube()
{
	vertexShader->Release();
	pixelShader->Release();
}

void Cube::CreateShaders(Renderer & renderer)
{
	std::ifstream vsFile("SimpleVertexShader.cso", std::ios::binary);
	std::ifstream psFile("SimplePixelShader.cso", std::ios::binary);

	std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	std::vector<char> psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };

	renderer.GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	renderer.GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);

	//create input layouts
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//2 parameters. See Input data in shader
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//use append element for each following parameter
	};
	renderer.GetDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &inputLayout);
}
