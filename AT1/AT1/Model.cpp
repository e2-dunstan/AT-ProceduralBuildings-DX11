#include "Model.h"
#include <fstream>
#include <vector>


Model::Model()
{
	texture = new Texture();
}

Model::~Model()
{
	//triangleVertexBuffer->Release();
	squareVertexBuffer->Release();
	squareIndexBuffer->Release();
	//vertexShader->Release();
	//pixelShader->Release();
	//inputLayout->Release();
	if (texture)
	{
		delete texture;
		texture = nullptr;
	}
}

bool Model::InitModel(Renderer& renderer, char* textureFilename, HWND hwnd)
{
	//CreateShaders(renderer);
	CreateMesh(renderer);

	bool result = LoadTexture(renderer, textureFilename, hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}

//LOOK UP RASTERTEK TUTORIAL ON TEXTURES: CTRL F 'TARGA'

void Model::CreateMesh(Renderer & renderer)
{
	//define vertices
	Vertex vertices[]
	{
		// Front Face
		Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
		Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
		Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
		// Back Face
		Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
		Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
		Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
		Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),
		// Top Face
		Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
		Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
		Vertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f),
		Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),
		// Bottom Face
		Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
		Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		Vertex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f),
		Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f),
		// Left Face
		Vertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f),
		Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f),
		Vertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
		Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
		// Right Face
		Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
		Vertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f),
		Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f),
	}; //sizeof = total bytes/bits

	DWORD indices[] = {
		// Front Face
		0,  1,  2,
		0,  2,  3,
		// Back Face
		4,  5,  6,
		4,  6,  7,
		// Top Face
		8,  9, 10,
		8, 10, 11,
		// Bottom Face
		12, 13, 14,
		12, 14, 15,
		// Left Face
		16, 17, 18,
		16, 18, 19,
		// Right Face
		20, 21, 22,
		20, 22, 23
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
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 24;
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
	std::ifstream vsFile("ColourVertexShader.cso", std::ios::binary);
	std::ifstream psFile("ColourPixelShader.cso", std::ios::binary);

	std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	std::vector<char> psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
		
	renderer.GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	renderer.GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);
	renderer.GetDeviceContext()->VSSetShader(vertexShader, NULL, NULL);
	renderer.GetDeviceContext()->PSSetShader(pixelShader, NULL, NULL);

	//create input layout description
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//2 parameters. See Input data in shader
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		//use append element for each following parameter
	};
	UINT numElements = ARRAYSIZE(layout);
	renderer.GetDevice()->CreateInputLayout(layout, numElements, vsData.data(), vsData.size(), &inputLayout);
	renderer.GetDeviceContext()->IASetInputLayout(inputLayout);
	renderer.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

ID3D11ShaderResourceView * Model::GetTexture()
{
	return texture->GetTexture();
}

Texture * Model::GetTexturePointer()
{
	return texture;
}

bool Model::LoadTexture(Renderer & renderer, char * filename, HWND hwnd)
{
	bool result;
	// Create the texture object.
	texture = new Texture();
	if (!texture)
	{
		return false;
	}
	// Initialize the texture object.
	result = texture->Init(renderer.GetDevice(), renderer.GetDeviceContext(), filename, hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}


