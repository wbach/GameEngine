#include "MyModel.h"
#include <algorithm>
CMyModel::CMyModel(CTextureLoader & texture_lodaer)
	: m_TextureLodaer(texture_lodaer)
{
}

CMyModel::~CMyModel()
{
	std::cout << "Destructor my model" << std::endl;
}

void CMyModel::InitModel(const std::string & file_name)
{	
	ParseObjFile(file_name);

}

void CMyModel::ParseObjFile(const std::string& file_name)
{
	auto file = Utils::ReadFile(file_name);
	std::string path, filename;
	Utils::GetFileAndPath(file_name, filename, path);

	std::replace(file.begin(), file.end(), '\t', ' ');

	std::istringstream f(file);
	std::string line;
	while (std::getline(f, line)) {
		auto substr = line.substr(line.find_first_not_of(' '));
		auto prefix = substr.substr(0, substr.find_first_of(' '));
		auto value = substr.substr(substr.find_first_of(' ') + 1);
		if (!prefix.compare("mtllib"))
		{
			ReadMaterialFile(path + "/" + value);
		}
		if (!prefix.compare("o"))
		{
			objects.push_back(Object());
			objects.back().name = value;
		}
		if (!prefix.compare("v"))
		{
			if (objects.empty())
			{
				auto err = "[Error] parsing obj file. " + file_name; +"\n";
				throw std::runtime_error(err.c_str());
			}
			auto vertex = Get::Vector3d(value, ' ');
			objects.back().vertex.push_back(vertex);
		}
		if (!prefix.compare("vt"))
		{
			if (objects.empty())
			{
				auto err = "[Error] parsing obj file. " + file_name; +"\n";
				throw std::runtime_error(err.c_str());
			}
			auto vt = Get::Vector2d(value, ' ');
			objects.back().text_coords.push_back(vt);
		}
		if (!prefix.compare("vn"))
		{
			if (objects.empty())
			{
				auto err = "[Error] parsing obj file. " + file_name; +"\n";
				throw std::runtime_error(err.c_str());
			}
			auto normal = Get::Vector3d(value, ' ');
			objects.back().normals.push_back(normal);
		}
		if (!prefix.compare("f"))
		{
			if (objects.empty())
			{
				auto err = "[Error] parsing obj file. " + file_name; +"\n";
				throw std::runtime_error(err.c_str());
			}
			Face face;
			//		2//1 4//1 1//1
			auto tokens = Utils::SplitString(value, ' ');
			int y = 0;
			for (auto& t : tokens)
			{
				//		2//1
				auto vf = Utils::SplitString(t, '/');				
				//std::cout << "Token : " << t << '\n';
				int x = 0;
				for (auto& i : vf)
				{		
					//if (!i.empty())
					//int a =  std::stoi(i) - 1;
					if (x == 0)
					{
						if (!i.empty())
						{
							int a = std::stoi(i) - 1;
							objects.back().indices.push_back(a);
							face.position[y] = objects.back().vertex[a];
						}
						//if (!i.empty())
						//	face.position[y] = objects.back().vertex[a];
					}
					if (x == 1)
					{
						if (!i.empty())
						{
							int a = std::stoi(i) - 1;
							face.texture_coord[y] = objects.back().text_coords[a];
						}
							
					}
					if (x == 2)
					{
						if (!i.empty())
						{
							int a = std::stoi(i) - 1;
							face.normal[y] = objects.back().normals[a];
						}							
					}
					x++;
			//		std::cout << "I : " << i.c_str() << ' '; 
				}
				y++;
			//	std::cout << '\n';
			}
			objects.back().faces.push_back(face);
		}
		if (!prefix.compare("map_Kd"))
		{
			if (objects.empty())
			{
				auto err = "[Error] parsing obj file. " + file_name; +"\n";
				throw std::runtime_error(err.c_str());
			}

			//auto texture = m_TextureLodaer.LoadTexture(value, true, TextureType::MATERIAL);
			// = texture;
		}
	}
	SBonesInfo m_BonesInfo;
	SMaterial mat;

	//for (auto& i : objects.back().vertex)
	//{
	//	postions.push_back(i.x);
	//	postions.push_back(i.y);
	//	postions.push_back(i.z);
	//}
	//for (auto& i : objects.back().normals)
	//{
	//	normals.push_back(i.x);
	//	normals.push_back(i.y);
	//	normals.push_back(i.z);
	//}
	//for (auto& i : objects.back().text_coords)
	//{
	//	text_coords.push_back(i.x);
	//	text_coords.push_back(i.y);
	//}
	/*for (auto& i : objects.back().indices)
	{
		indices.push_back(i);
	}*/
	int xx = 0;
	for(auto& f : objects.back().faces)
	{		
		for (int x = 0; x < 3; x++)
		{
			postions.push_back(f.position[x].x);
			postions.push_back(f.position[x].y);
			postions.push_back(f.position[x].z);
			indices.push_back(xx++);
		}
		for (int x = 0; x < 3; x++)
		{
			normals.push_back(f.normal[x].x);
			normals.push_back(f.normal[x].y);
			normals.push_back(f.normal[x].z);
		}
		for (int x = 0; x < 3; x++)
		{
			text_coords.push_back(f.texture_coord[x].x);
			text_coords.push_back(f.texture_coord[x].y);
		}
		
	}	
	AddMesh(postions, text_coords, normals, tangents, indices, mat, m_BonesInfo.bones);
}
//Example Material file
//# Blender MTL File : 'None'
//# Material Count : 3
//
//newmtl Material
//Ns 96.078431
//Ka 1.000000 1.000000 1.000000
//Kd 0.640000 0.001047 0.492338
//Ks 0.500000 0.500000 0.500000
//Ke 0.000000 0.000000 0.000000
//Ni 1.000000
//d 1.000000
//illum 2
void CMyModel::ReadMaterialFile(const std::string& file_name)
{
	auto file = Utils::ReadFile(file_name);
//	std::cout << file << std::endl;

	std::istringstream f(file);
	std::string line;
	Material material;
	while (std::getline(f, line))
	{
		if (line.empty())
			continue;
		auto substr = line.substr(line.find_first_not_of(' '));
		auto prefix = substr.substr(0, substr.find_first_of(' '));
		auto value = substr.substr(substr.find_first_of(' ') + 1);

		if (!prefix.compare("newmtl"))
		{
			material.name = value;
		}
		if (!prefix.compare("Ns"))
		{
			material.Ns = std::stof(value);
		}
		if (!prefix.compare("Ka"))
		{
			material.ka = Get::Vector3d(value, ' ');
		}
		if (!prefix.compare("Kd"))
		{
			material.kd = Get::Vector3d(value, ' ');
		}
		if (!prefix.compare("Ks"))
		{
			material.ks = Get::Vector3d(value, ' ');
		}
		if (!prefix.compare("Ke"))
		{
			material.ke = Get::Vector3d(value, ' ');
		}
		if (!prefix.compare("Ni"))
		{
			material.Ni = std::stof(value);
		}
		if (!prefix.compare("d"))
		{
			material.d = std::stof(value);
		}
		if (!prefix.compare("illum"))
		{
			material.illum = std::stoi(value);
			materials.push_back(material);
			material = Material();
		}
	}

}
