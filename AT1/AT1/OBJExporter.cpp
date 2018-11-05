#include "OBJExporter.h"

using namespace std;

void OBJExporter::Create()
{
	ofstream file("Resources/Export.obj");
	ofstream mtl("Resources/Export.mtl");
	int indexOffset = 1;

	int mtlNumber = 0;
	file << "mtllib Export.mtl" << endl << endl;

	for (int m = 1; m < models.size(); m++)
	{
		string newTexture = "";

		for (int i = 0; i < textures.size(); i++)
		{
			if (models[m]->GetTextureString() == textures[i])
			{
				newTexture = textures[i];
				mtlNumber = i + 1;
			}
		}
		if (newTexture == "")
		{
			textures.push_back(models[m]->GetTextureString());
			newTexture = textures.back();
			++mtlNumber;

			mtl << "newmtl texture_" + newTexture << endl;
			mtl << "d 1" << endl;
			mtl << "illum 1" << endl;
			mtl << "Kd 1.000 1.000 1.000" << endl;
			mtl << "Ka 1.000 1.000 1.000" << endl;
			mtl << "map_Kd " << newTexture << endl;
			mtl << "map_Ka " << newTexture << endl;;
			mtl << endl;
		}
		SetVertices(models[m]->GetVertices(), m);
		SetIndices(models[m]->GetIndices());

		vector<string> positions;
		vector<string> textureCoordinates;
		vector<string> normals;
		vector<string> faces;

		file << "g texture " + newTexture << endl;

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
		for (int i = 0; i < vertices.size(); i++)
		{
			file << textureCoordinates[i] << endl;
		}
		for (int i = 0; i < vertices.size(); i++)
		{
			file << normals[i] << endl;
			++indexOffset;
		}

		file << "usemtl texture_" + newTexture << endl;
		for (int i = 0; i < indices.size(); i += 3)
		{
			file << "f " + faces[i] + faces[i + 1] + faces[i + 2] << endl;
		}
		file << endl;

		ClearVertices();
		ClearIndices();
	}
	mtl.close();
	file.close();
}

void OBJExporter::SetModels(vector<Model*> _models)
{
	models = _models;
}

void OBJExporter::SetTransforms(vector<XMMATRIX> _transforms)
{
	transforms = _transforms;
}

void OBJExporter::SetVertices(vector<Vertex> newVertices, int i)
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

void OBJExporter::SetIndices(vector<DWORD> newIndices)
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