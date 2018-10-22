#include "OBJExporter.h"

using namespace std;

void OBJExporter::Create()
{
	ofstream mtl("Resources/Export.mtl");
	mtl << "newmtl texture" << endl;
	mtl << "illum 2" << endl;
	mtl << "Kd 1.0 1.0 1.0" << endl;
	mtl << "Ka 1.0 1.0 1.0" << endl;
	mtl << "map_Kd George_Foreman.tga" << endl;
	mtl << "map_Ka George_Foreman.tga" << endl;
	mtl.close();

	// THIS MAY CAUSE ISSUES
	ofstream file("Resources/Export.obj");
	
	vector<string> positions;
	vector<string> textureCoordinates;
	vector<string> normals;
	vector<string> faces;

	for (int i = 0; i < allVertices.size(); i++)
	{
		positions.push_back("v " + to_string(allVertices[i].pos.x) + 
							" " + to_string(allVertices[i].pos.y) +
							" " + to_string(allVertices[i].pos.z));

		textureCoordinates.push_back("vt " + to_string(allVertices[i].texture.x) +
									" " + to_string(allVertices[i].texture.y));

		normals.push_back("vn " + to_string(allVertices[i].normal.x) +
							" " + to_string(allVertices[i].normal.y) +
							" " + to_string(allVertices[i].normal.z));
	}
	for (int i = 0; i < allIndices.size(); i++)
	{
		faces.push_back(to_string(allIndices[i] + 1) + "/"
					  + to_string(allIndices[i] + 1) + "/"
					  + to_string(allIndices[i] + 1) + " ");
	}

	file << "mtllib Export.mtl" << endl;
	for (int i = 0; i < allVertices.size(); i++)
	{
		file << positions[i] << endl;
	}
	file << endl;
	for (int i = 0; i < allVertices.size(); i++)
	{
		file << textureCoordinates[i] << endl;
	}
	file << endl;
	for (int i = 0; i < allVertices.size(); i++)
	{
		file << normals[i] << endl;
	}
	file << "usemtl texture" << endl;
	for (int i = 0; i < allIndices.size(); i+=3)
	{
		file << "f " + faces[i] + faces[i + 1] + faces[i + 2] << endl;
	}
	file.close();
}

void OBJExporter::SetVertices(std::vector<Vertex> newVertices)
{
	for (int v = 0; v < newVertices.size(); v++)
	{
		allVertices.push_back(newVertices[v]);
	}
}

void OBJExporter::SetIndices(std::vector<DWORD> newIndices)
{
	for (int i = 0; i < newIndices.size(); i++)
	{
		allIndices.push_back(newIndices[i]);
	}
}


