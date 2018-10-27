#include "OBJExporter.h"

using namespace std;

void OBJExporter::Create()
{
	ofstream file("Resources/Export.obj");
	ofstream mtl("Resources/Export.mtl");
	int indexOffset = 1;

	int mtlNumber = 0;
	int newMTL = 0;
	std::string prevTexture;

	for (int m = 0; m < models.size(); m++)
	{
		mtlNumber = newMTL;
		file << "g <Group" + std::to_string(mtlNumber) + ">" << endl;

		std::string newTexture = models[m]->GetTextureString();
		if (newTexture != prevTexture)
		{
			mtl << "newmtl texture" + std::to_string(mtlNumber) << endl;
			mtl << "illum 2" << endl;
			mtl << "Kd 1.0 1.0 1.0" << endl;
			mtl << "Ka 1.0 1.0 1.0" << endl;
			mtl << "map_Kd " << newTexture << endl;
			mtl << "map_Ka " << newTexture << endl;
			++newMTL;
		}
		prevTexture = newTexture;

		file << "mtllib Export" + std::to_string(mtlNumber) + ".mtl" << endl << endl;

		SetVertices(models[m]->GetVertices(), m);
		SetIndices(models[m]->GetIndices());

		vector<string> positions;
		vector<string> textureCoordinates;
		vector<string> normals;
		vector<string> faces;

		for (int i = 0; i < vertices.size(); i++)
		{
			positions.push_back("v " + to_string(vertices[i].pos.x) +
				" " + to_string(vertices[i].pos.y) +
				" " + to_string(vertices[i].pos.z));

			textureCoordinates.push_back("vt " + to_string(vertices[i].texture.x) +
				" " + to_string(vertices[i].texture.y));

			normals.push_back("vn " + to_string(vertices[i].normal.x) +
				" " + to_string(vertices[i].normal.y) +
				" " + to_string(vertices[i].normal.z));
		}
		
		for (int i = 0; i < indices.size(); i++)
		{
			faces.push_back(to_string(indices[i] + indexOffset) + "/"
				+ to_string(indices[i] + indexOffset) + "/"
				+ to_string(indices[i] + indexOffset) + " ");
		}

		for (int i = 0; i < vertices.size(); i++)
		{
			file << positions[i] << endl;
		}
		file << endl;
		for (int i = 0; i < vertices.size(); i++)
		{
			file << textureCoordinates[i] << endl;
		}
		file << endl;
		for (int i = 0; i < vertices.size(); i++)
		{
			file << normals[i] << endl;
			++indexOffset;
		}
		file << endl << "usemtl texture" + std::to_string(mtlNumber) << endl;
		for (int i = 0; i < indices.size(); i += 3)
		{
			file << "f " + faces[i] + faces[i + 1] + faces[i + 2] << endl;
		}
		file << endl;

		ClearVertices();
		ClearIndices();
	}
	file.close();
	mtl.close();
}

void OBJExporter::CreateMTL(std::ofstream mtl, int i, std::string texture)
{
	//ofstream mtl("Resources/Export" + std::to_string(i) + ".mtl");
	//mtl << "newmtl texture" + std::to_string(i) << endl;
	//mtl << "illum 2" << endl;
	//mtl << "Kd 1.0 1.0 1.0" << endl;
	//mtl << "Ka 1.0 1.0 1.0" << endl;
	//mtl << "map_Kd " << texture << endl;
	//mtl << "map_Ka " << texture << endl;
	//mtl.close();
}

void OBJExporter::SetModels(std::vector<Model*> _models)
{
	models = _models;
}

void OBJExporter::SetTransforms(std::vector<XMMATRIX> _transforms)
{
	transforms = _transforms;
}

void OBJExporter::SetVertices(std::vector<Vertex> newVertices, int i)
{
	for (int v = 0; v < newVertices.size(); v++)
	{
		XMVECTOR pos = XMVectorSet(newVertices[v].pos.x, newVertices[v].pos.y, newVertices[v].pos.z, 0.0f);
		pos = XMVector3Transform(pos, transforms[i]);

		XMFLOAT4 temp;
		XMStoreFloat4(&temp, pos);

		Vertex newVertex = Vertex(temp.x, temp.y, temp.z,
			newVertices[v].texture.x, newVertices[v].texture.y,
			newVertices[v].normal.x, newVertices[v].normal.y, newVertices[v].normal.z);
		vertices.push_back(newVertex);
	}
	
}

void OBJExporter::SetIndices(std::vector<DWORD> newIndices)
{
	for (int i = 0; i < newIndices.size(); i++)
	{
		indices.push_back(newIndices[i]);
	}
}

void OBJExporter::ClearVertices()
{
	vertices.clear();
}

void OBJExporter::ClearIndices()
{
	indices.clear();
}