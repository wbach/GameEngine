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
	AddFinalMeshes();
}
void CMyModel::ParseObjFile(const std::string& file_name)
{
	auto file = Utils::ReadFile(file_name);
	std::string path, filename;
	Utils::GetFileAndPath(file_name, filename, path);

	std::replace(file.begin(), file.end(), '\t', ' ');

	std::istringstream f(file);
	//std::ifstream f(file_name);

	std::string line;

	WBLoader::Mesh* current_mesh = nullptr;
	WBLoader::Object* current_object = nullptr;	

	while (std::getline(f, line))
	{
		auto substr = line.substr(line.find_first_not_of(' '));
		auto prefix = substr.substr(0, substr.find_first_of(' '));
		auto value = substr.substr(substr.find_first_of(' ') + 1);

		if (!prefix.compare("mtllib"))		
			ReadMaterialFile(path + "/" + value);
		
		if (!prefix.compare("o"))
			ProcesObject(current_object, value);

		if (!prefix.compare("v"))				
			ProcesVertex(current_object, value);			
		
		if (!prefix.compare("vt"))
			ProcesUVs(current_object, value);

		if (!prefix.compare("vn"))
			ProcesNormal(current_object, value);

		if (!prefix.compare("usemtl"))
			ProcesMaterial(current_object, current_mesh, value);

		if (!prefix.compare("f"))
			ProcesFace(current_object, current_mesh, value);
	}	
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
	SMaterial* current_material = nullptr;	
	while (std::getline(f, line))
	{
		if (line.empty())
			continue;
		auto substr = line.substr(line.find_first_not_of(' '));
		auto prefix = substr.substr(0, substr.find_first_of(' '));
		auto value = substr.substr(substr.find_first_of(' ') + 1);

		if (!prefix.compare("newmtl"))
		{
			materials.push_back(SMaterial());
			current_material = &materials.back();
			current_material->name = value;
		}
		if (!prefix.compare("Ns"))
		{
			if(current_material != nullptr)
				current_material->shineDamper = std::stof(value);
		}
		if (!prefix.compare("Ka"))
		{
			if (current_material != nullptr)
				current_material->ambient = Get::Vector3d(value, ' ');
		}
		if (!prefix.compare("Kd"))
		{
			if (current_material != nullptr)
				current_material->diffuse = Get::Vector3d(value, ' ');
		}
		if (!prefix.compare("Ks"))
		{
			if (current_material != nullptr)
				current_material->specular = Get::Vector3d(value, ' ');
		}
		if (!prefix.compare("Ke"))
		{
			//material.ke = Get::Vector3d(value, ' ');
		}
		if (!prefix.compare("Ni"))
		{
			//material.Ni = std::stof(value);
		}
		if (!prefix.compare("d"))
		{
			//material.d = std::stof(value);
		}
		if (!prefix.compare("illum"))
		{
			//material.illum = std::stoi(value);		
		}
		if (!prefix.compare("map_Kd"))
		{
			if (current_material != nullptr)
				current_material->m_DiffuseTexture = m_TextureLodaer.LoadTexture("../Data/Textures/" + value, true, TextureType::MATERIAL);
		}
		if (!prefix.compare("map_bump") || !prefix.compare("map_Bump"))
		{
			if (current_material != nullptr)
				current_material->m_NormalTexture = m_TextureLodaer.LoadTexture("../Data/Textures/" + value, true, TextureType::MATERIAL);
		}
	}

}

void CMyModel::ProcesVertex(WBLoader::Object * object, const std::string& value)
{	
	if (object == nullptr)
	{
		auto err = "[Error] parsing obj file. " + m_Filename + "\n";
		throw std::runtime_error(err.c_str());
	}
	auto v = Get::Vector3d(value, ' ');
	//glm::vec3 v;
	//sscanf_s(value.c_str(), "%f %f %f", &v.x, &v.y, &v.z);
	vertex.push_back(v);
}

void CMyModel::ProcesNormal(WBLoader::Object * object, const std::string & value)
{	
	if (object == nullptr)
	{
		auto err = "[Error] parsing obj file. " + m_Filename + "\n";
		throw std::runtime_error(err.c_str());
	}
	auto v = Get::Vector3d(value, ' ');
	//glm::vec3 v;
	//sscanf_s(value.c_str(), "%f %f %f", &v.x, &v.y, &v.z);
	normals.push_back(v);
}

void CMyModel::ProcesUVs(WBLoader::Object * object, const std::string & value)
{	
	if (object == nullptr)
	{
		auto err = "[Error] parsing obj file. " + m_Filename + "\n";
		throw std::runtime_error(err.c_str());
	}
	auto v = Get::Vector2d(value, ' ');
	//glm::vec2 v;
	//sscanf_s(value.c_str(), "%f %f", &v.x, &v.y);
	text_coords.push_back(v);	
}

void CMyModel::ProcesFace(WBLoader::Object * object, WBLoader::Mesh* mesh, const std::string & value)
{
	if (object == nullptr && mesh == nullptr)
	{
		auto err = "[Error] parsing obj file. " + m_Filename + "\n";
		throw std::runtime_error(err.c_str());
	}
	
	/*wb::vec3i f1, f2, f3;
	sscanf_s(value.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d",
		&f1.x, &f1.y, &f1.z, 
		&f2.x, &f2.y, &f2.z, 
		&f3.x, &f3.y, &f3.z);
	
	f1.x -= 1;
	f1.y -= 1;
	f1.z -= 1;

	f2.x -= 1;
	f2.y -= 1;
	f2.z -= 1;

	f3.x -= 1;
	f3.y -= 1;
	f3.z -= 1;

	WBLoader::VertexBuffer vb;
	vb.indexes = f1;
	vb.position = vertex[f1.x];
	vb.uvs = text_coords[f1.y];
	vb.normal = normals[f1.z];
	mesh->vertexBuffer.push_back(vb);

	vb.indexes = f2;
	vb.position = vertex[f2.x];
	vb.uvs = text_coords[f2.y];
	vb.normal = normals[f2.z];
	mesh->vertexBuffer.push_back(vb);

	vb.indexes = f3;
	vb.position = vertex[f3.x];
	vb.uvs = text_coords[f3.y];
	vb.normal = normals[f3.z];
	mesh->vertexBuffer.push_back(vb);
	return;*/

	//		2//1 4//1 1//1
	auto tokens = Utils::SplitString(value, ' ');
	if (tokens.size() > 3) return;

	for (auto& t : tokens)
	{
		WBLoader::VertexBuffer vb;
		//		2//1
		auto vf = Utils::SplitString(t, '/');
		int x = 0;
		for (auto& i : vf)
		{
			int ii = 0;
			if (!i.empty())
			{
				ii = std::stoi(i) - 1;
			}

			if (x == 0)
			{
				if (!i.empty())
				{
					vb.indexes.x = ii;
					vb.position = vertex[ii];
				}
			}
			if (x == 1)
			{
				if (!i.empty())
				{
					vb.indexes.y = ii;
					vb.uvs = text_coords[ii];
				}

			}
			if (x == 2)
			{
				if (!i.empty())
				{
					vb.indexes.z = ii;
					vb.normal = normals[ii];
				}
			}
			x++;
		}
		mesh->vertexBuffer.push_back(vb);
	}	
}

void CMyModel::ProcesObject(WBLoader::Object *& object, const std::string & value)
{
	objects.push_back(WBLoader::Object());
	object = &objects.back();
	object->name = value;
}

void CMyModel::ProcesMaterial(WBLoader::Object * object, WBLoader::Mesh *& mesh, const std::string & value)
{
	if (object == nullptr)
	{
		auto err = "[Error] parsing obj file. " + m_Filename + "\n";
		throw std::runtime_error(err.c_str());
	}

	object->meshes.push_back(WBLoader::Mesh());
	mesh = &objects.back().meshes.back();	

	auto f = [&](const SMaterial& v) {
		return value == v.name;
	};
	auto material = std::find_if(std::begin(materials), std::end(materials), f);
	mesh->material = *material;
}

void CMyModel::AddFinalMeshes()
{
	SBonesInfo m_BonesInfo;
	for (auto& obj : objects)
	{
		for (auto& mesh : obj.meshes)
		{
			mesh.IndexinVBO();
			AddMesh(mesh.fpostions, mesh.fuvs, mesh.fnormal, mesh.ftangents, mesh.indices, mesh.material, m_BonesInfo.bones);
		}
	}
}
