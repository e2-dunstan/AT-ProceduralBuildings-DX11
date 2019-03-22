#include "OBJImporter.h"

using namespace std;

void OBJImporter::ReadOBJ(std::string filename)
{
	vertices.clear();
	indices.clear();

	ifstream file(filename);

	if (file.is_open())
	{
		string line;
		vector<string> positions;
		vector<string> textureCoordinates;
		vector<string> normals;
		vector<string> faces;
		while (getline(file, line))
		{
			if (line.find("v ") != string::npos)
			{
				positions.push_back(line);
			}
			else if (line.find("vt") != string::npos)
			{
				textureCoordinates.push_back(line);
			}
			else if (line.find("vn") != string::npos)
			{
				normals.push_back(line);
			}
			else if (line.find("f ") != string::npos)
			{
				faces.push_back(line);
			}
		}
		file.close();

		string space = " ";
		size_t pos = 0;
		string item = "v";

		//Vertex generation
		for (int i = 0; i < positions.size(); i++)
		{
			vertices.push_back(Vertex(10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000));
			//Set vertex positions
			while ((pos = positions[i].find(space)) != string::npos)
			{
				item = positions[i].substr(0, pos);
				//do something with it
				if (!item.find("v") == string::npos)
				{
					if (vertices[i].pos.x == 10000)
						vertices[i].pos.x = stoi(item);
					else if (vertices[i].pos.y == 10000)
						vertices[i].pos.y = stoi(item);
					else if (vertices[i].pos.z == 10000)
						vertices[i].pos.z = stoi(item);
				}
				positions[i].erase(0, pos + space.length());
			}
			//Set texture coordinates
			while ((pos = textureCoordinates[i].find(space)) != string::npos)
			{
				item = textureCoordinates[i].substr(0, pos);
				//do something with it
				if (item.find("v") == string::npos)
				{
					if (vertices[i].texture.x == 10000)
						vertices[i].texture.x = stoi(item);
					else if (vertices[i].texture.y == 10000)
						vertices[i].texture.y = stoi(item);
				}
				positions[i].erase(0, pos + space.length());
			}
			//Set normal coordinates
			while ((pos = normals[i].find(space)) != string::npos)
			{
				item = normals[i].substr(0, pos);
				//do something with it
				if (!item.find("v") == string::npos)
				{
					if (vertices[i].normal.x == 10000)
						vertices[i].normal.x = stoi(item);
					else if (vertices[i].normal.y == 10000)
						vertices[i].normal.y = stoi(item);
					else if (vertices[i].normal.z == 10000)
						vertices[i].normal.z = stoi(item);
				}
				positions[i].erase(0, pos + space.length());
			}
		}


		space = " ";
		string slash = "/";
		pos = 0;
		item = "f ";

		//Index generation
		for (int i = 0; i < faces.size(); i++)
		{
			faces[i].erase(0, 2);

			while ((pos = faces[i].find(space)) != string::npos
				|| (pos = faces[i].find(slash)) != string::npos)
			{
				item = faces[i].substr(0, pos);
				//do something with it
				if (item.find("f") == string::npos)
				{
					indices.push_back(stoi(item));
				}
				faces[i].erase(0, pos + 1);
			}
		}
	}
}

std::vector<Vertex> OBJImporter::GetVertices()
{
	return vertices;
}

std::vector<DWORD> OBJImporter::GetIndices()
{
	return indices;
}
