#include "OBJExporter.h"

using namespace std;

void OBJExporter::Create(std::vector<Model::Vertex> vertices, std::vector<DWORD> indices)
{
	ofstream mtl("Export.mtl");
	mtl << "newmtl texture" << endl;
	mtl << "illum 1" << endl;
	mtl << "Kd 0.50 0.50 0.50" << endl;
	mtl << "Ka 0.50 0.50 0.50" << endl;
	mtl << "map_Kd George_Foreman.tga" << endl;
	mtl << "map_Ka George_Foreman.tga" << endl;
	mtl.close();

	ofstream file("Export.obj");
	
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
		faces.push_back(to_string(indices[i] + 1) + "/"
					  + to_string(indices[i] + 1) + "/"
					  + to_string(indices[i] + 1) + " ");
	}

	file << "mtllib Export.mtl" << endl;
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
	}
	file << "usemtl texture" << endl;
	for (int i = 0; i < indices.size(); i+=3)
	{
		file << "f " + faces[i] + faces[i + 1] + faces[i + 2] << endl;
	}
	file.close();
}
