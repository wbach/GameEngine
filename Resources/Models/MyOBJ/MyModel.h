#pragma once
#include "../Model.h"
#include "../../../Utils/Utils.h"
#include "../../TextureLoader.h"


class CMyModel : public CModel
{
public:
	CMyModel(CTextureLoader& texture_lodaer);
	virtual			~CMyModel() override;
	virtual void	InitModel(const std::string& file_name) override;
private:
	struct Material
	{
		std::string name;
		float Ns;
		glm::vec3 ka;
		glm::vec3 kd;
		glm::vec3 ks;
		glm::vec3 ke;
		float Ni;
		float d;
		int illum;
	};

	struct Face
	{
		glm::vec3 position[3];
		glm::vec3 normal[3];
		glm::vec2 texture_coord[3];
		unsigned int material_id;
	};

	struct Object
	{
		std::string name;
		std::vector<Face> faces;
		std::vector<Material> materials;
		
		std::vector<unsigned short> indices;
		std::vector<glm::vec3> vertex;
		std::vector<glm::vec2> text_coords;
		std::vector<glm::vec3> normals;
	};

	std::vector<float> postions;
	std::vector<float> text_coords;
	std::vector<float> normals;
	std::vector<float> tangents;
	std::vector<unsigned short> indices;

	void ParseObjFile(const std::string& file);
	void ReadMaterialFile(const std::string&file);
	
	std::list<Object> objects;
	std::list<Material> materials;

	CTextureLoader&	m_TextureLodaer;
};