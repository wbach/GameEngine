#pragma once
#include <vector>

namespace VertexBufferObjects
{
	enum Type
	{
		INDICES = 0,
		POSITION,
		TEXT_COORD,
		NORMAL,
		TANGENT,
		TRANSFORM_MATRIX,
		BONES,
		COUNT,
	};
};

class CMeshes
{
public:
    CMeshes(const CMeshes&) = delete;

    const GLuint& GetVao() const;
	const GLuint& GetVbo(VertexBufferObjects::Type type) const;
	const GLuint& GetVertexCount() const;
	const SMaterial& GetMaterial() const;
private:
    SMaterial	m_Material;
    GLuint		m_Vao;
	GLuint		m_Vbos[VertexBufferObjects::COUNT];
	GLuint		m_VertexCount;

	glm::vec3	m_BoundingBoxMin,
				m_BoundingBoxMax,
				m_BoundingCenter,
				m_BoundingSize;

    std::vector<float> positions;
	std::vector<float> text_coords;
	std::vector<float> normals;
	std::vector<float> tangents;
	std::vector<unsigned short> indices;
	std::vector<SVertexBoneData> m_Bones;
	std::vector<glm::mat4> m_InstancedMatrixes;
};
