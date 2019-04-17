#include "Model.h"
#include <fstream>

Model::Model(Type modelType, int width, int height, int depth,
	float posX, float posY, float posZ, float rotation)
{
	texture = new Texture();

	type = modelType;
	w = width;
	h = height;
	d = depth;
	position.x = posX;
	position.y = posY;
	position.z = posZ;

	//Convert to radians
	r = (rotation / 180) * PI;
}

Model::~Model()
{
	vertexBuffer->Release();
	indexBuffer->Release();
	vertexShader->Release();
	pixelShader->Release();
	inputLayout->Release();
	if (texture)
	{
		delete texture;
		texture = nullptr;
	}
}

bool Model::InitModel(Renderer& renderer, char* textureFilename, HWND hwnd)
{
	CreateShaders(renderer);
	CreateMesh(renderer);

	bool result = LoadTexture(renderer, textureFilename, hwnd);
	if (!result)
	{
		return false;
	}
	return true;
}

void Model::CreateMesh(Renderer & renderer)
{
	//--DEFINE VERTICES--//

	switch (type)
	{
	case Type::WALL:
	{
		vertices = Shape::CreateSquareVertices(w, h, d);
		indices = Shape::CreateQuadIndices();
		break;
	}
	case Type::WINDOW:
	{
		vertices = Shape::CreateSquareVertices(w, h, d);
		indices = Shape::CreateQuadIndices();
		break;
	}
	case Type::DOOR:
	{
		vertices = Shape::CreateSquareVertices(w, h, d);
		indices = Shape::CreateQuadIndices();
		break;
	}
	case Type::FLOOR:
	{
		vertices = Shape::CreateFloorVertices(w, h, d);
		indices = Shape::CreatePlaneIndices();
		break;
	}
	case Type::CORNER:
	{
		vertices = Shape::CreateCornerVertices(w, h);
		indices = Shape::CreateQuadIndices();
		break;
	}
	case Type::ROOF_FLAT:
	{
		vertices = Shape::CreateLargeSquareVertices(w, h, d);
		indices = Shape::CreateQuadIndices();
		break;
	}
	case Type::ROOF_PYRAMID:
	{
		vertices = Shape::CreatePyramidVertices(w, h, d);
		indices = Shape::CreatePyramidIndices();
		break;
	}
	case Type::ROOF_SHED:
	{
		vertices = Shape::CreateShedVertices(w, h, d);
		indices = Shape::CreateShedIndices();
		break;
	}
	case Type::INTERIOR_WALL:
	{
		vertices = Shape::CreateSquareVertices(w, h, d);
		indices = Shape::CreateQuadIndices();
		break;
	}
	case Type::OBJECT:
	{
		vertices = Shape::CreateSquareVertices(w, h, d);
		indices = Shape::CreateQuadIndices();
		//Nothing required if OBJ imported
		break;
	}
	}

	//--CREATE BUFFERS--//

	//Create index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices.data();
	renderer.GetDevice()->CreateBuffer(&indexBufferDesc, &iinitData, &indexBuffer);

	//Create vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices.data();
	renderer.GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer);
}


void Model::CreateShaders(Renderer & renderer)
{
	std::ifstream vsFile("TextureVertexShader.cso", std::ios::binary);
	std::ifstream psFile("TexturePixelShader.cso", std::ios::binary);

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
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		//use append element for each following parameter
	};
	UINT numElements = ARRAYSIZE(layout);
	renderer.GetDevice()->CreateInputLayout(layout, numElements, vsData.data(), vsData.size(), &inputLayout);
	renderer.GetDeviceContext()->IASetInputLayout(inputLayout);
	renderer.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Model::UpdateBuffers(Renderer& renderer)
{
	renderer.GetDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//bind vertex buffer
	UINT stride = sizeof(Vertex);	//size between each vertex
	UINT offset = 0;
	renderer.GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);	//look at function requirements for help
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

void Model::SetTextureString(std::string texStr)
{
	textureStr = texStr;
}

std::string Model::GetTextureString()
{
	return textureStr;
}

XMFLOAT3 Model::GetPosition()
{
	return position;
}

void Model::SetPosition(XMFLOAT3 pos)
{
	position = pos;
}

float Model::GetRotation()
{
	return r;
}

Type Model::GetType()
{
	return type;
}

std::vector<Vertex> & Model::GetVertices()
{
	return vertices;
}

std::vector<DWORD> & Model::GetIndices()
{
	return indices;
}

void Model::SetVertices(std::vector<Vertex> v)
{
	vertices = v;
}

void Model::SetIndices(std::vector<DWORD> i)
{
	indices = i;
}


