#include "OBJImporter.h"

using namespace std;

void OBJImporter::ReadOBJs(std::string filename)
{
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
			if (line.find("v "))
			{
				positions.push_back(line);
			}
			else if (line.find("vt"))
			{
				textureCoordinates.push_back(line);
			}
			else if (line.find("vn"))
			{
				normals.push_back(line);
			}
			else if (line.find("f "))
			{
				faces.push_back(line);
			}
		}
		file.close();

		string space = " ";
		size_t pos = 0;
		string item = "v";
		for (int i = 0; i < positions.size(); i++)
		{
			vertices.push_back(new Vertex(10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000));
			//Set vertex positions
			while ((pos = positions[i].find(space)) != string::npos)
			{
				item = positions[i].substr(0, pos);
				//do something with it
				if (!item.find("v"))
				{
					if (vertices[i]->pos.x == 10000)
						vertices[i]->pos.x = stoi(item);
					else if (vertices[i]->pos.y == 10000)
						vertices[i]->pos.y = stoi(item);
					else if (vertices[i]->pos.z == 10000)
						vertices[i]->pos.z = stoi(item);
				}
				positions[i].erase(0, pos + space.length());
			}
			//Set texture coordinates
			while ((pos = textureCoordinates[i].find(space)) != string::npos)
			{
				item = textureCoordinates[i].substr(0, pos);
				//do something with it
				if (!item.find("v"))
				{
					if (vertices[i]->texture.x == 10000)
						vertices[i]->texture.x = stoi(item);
					else if (vertices[i]->texture.y == 10000)
						vertices[i]->texture.y = stoi(item);
				}
				positions[i].erase(0, pos + space.length());
			}
			//Set normal coordinates
			while ((pos = normals[i].find(space)) != string::npos)
			{
				item = normals[i].substr(0, pos);
				//do something with it
				if (!item.find("v"))
				{
					if (vertices[i]->normal.x == 10000)
						vertices[i]->normal.x = stoi(item);
					else if (vertices[i]->normal.y == 10000)
						vertices[i]->normal.y = stoi(item);
					else if (vertices[i]->normal.z == 10000)
						vertices[i]->normal.z = stoi(item);
				}
				positions[i].erase(0, pos + space.length());
			}
		}
	}
}
