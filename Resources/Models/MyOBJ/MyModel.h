#pragma once
#include "../Model.h"
#include "../../../Utils/Utils.h"
#include "../../TextureLoader.h"

namespace WBLoader
{
	struct VertexBuffer
	{
		wb::vec3i indexes;
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uvs;
		unsigned int material_id;
	};

	struct Mesh
	{
		std::list<VertexBuffer> vertexBuffer;

		std::vector<unsigned short> indices;
		std::vector<float> fpostions;
		std::vector<float> fuvs;
		std::vector<float> fnormal;
		std::vector<float> ftangents;
		SMaterial material;

		int FindIndex(const std::list<wb::vec3i>& vertexes, const wb::vec3i& v)
		{
			auto it = std::find(vertexes.begin(), vertexes.end(), v);
			auto index = std::distance(vertexes.begin(), it);

			if (it != vertexes.end())
				return index;			
			else 
				return -1;
		}
		int FindIndexFast(std::map<wb::vec3i, unsigned short>& vertexes, const wb::vec3i& v)
		{
			auto it = vertexes.find(v);
			if (it == vertexes.end())			
				return -1;					
			return it->second;			
		}
		void AddVec3ToFloatBuffer(std::vector<float>& buffer, const glm::vec3& v)
		{
			buffer.push_back(v.x);
			buffer.push_back(v.y);
			buffer.push_back(v.z);
		}
		void AddVec2ToFloatBuffer(std::vector<float>& buffer, const glm::vec2& v)
		{
			buffer.push_back(v.x);
			buffer.push_back(v.y);
		}
		void IndexinVBO()
		{
			//std::list<wb::vec3i> out_indexes;
			std::map<wb::vec3i, unsigned short> out_indexes;
			for (auto& v : vertexBuffer)
			{
				//auto i = FindIndex(out_indexes, v.indexes);
				auto i = FindIndexFast(out_indexes, v.indexes);
				if (i >= 0)
				{
					indices.push_back(static_cast<unsigned short>(i));
				}
				else
				{
					AddVec3ToFloatBuffer(fpostions, v.position);
					AddVec3ToFloatBuffer(fnormal, v.normal);
					AddVec2ToFloatBuffer(fuvs, v.uvs);
					auto newIndex = (unsigned short)out_indexes.size();
					//out_indexes.push_back(v.indexes);
					out_indexes[v.indexes] = newIndex;
					indices.push_back(newIndex);
				}
			}
		}
	};

	struct Object
	{
		std::string name;
		std::vector<Mesh> meshes;
	};
}
class CMyModel : public CModel
{
public:
	CMyModel(CTextureLoader& texture_lodaer);
	virtual			~CMyModel() override;
	virtual void	InitModel(const std::string& file_name) override;
private:
	void ParseObjFile(const std::string& file);
	void ReadMaterialFile(const std::string&file);
	void ProcesVertex(WBLoader::Object* object, const std::string& value);
	void ProcesNormal(WBLoader::Object* object, const std::string& value);
	void ProcesUVs(WBLoader::Object* object, const std::string& value);
	void ProcesFace(WBLoader::Object* object, WBLoader::Mesh* mesh, const std::string& value);
	void ProcesObject(WBLoader::Object*& object, const std::string& value);
	void ProcesMaterial(WBLoader::Object* object, WBLoader::Mesh*& mesh, const std::string& value);
	void AddFinalMeshes();

	std::list<WBLoader::Object> objects;
	std::list<SMaterial> materials;

	std::vector<glm::vec3> vertex;
	std::vector<glm::vec2> text_coords;
	std::vector<glm::vec3> normals;

	CTextureLoader&	m_TextureLodaer;
};