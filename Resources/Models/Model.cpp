#include "Model.h"


CModel::CModel()
{

}

void CModel::InitModel(const std::string&  file_name)
{
	m_Filename = file_name;
	CLogger::Instance().Log(file_name + " succesful loaded");
}

CModel::~CModel() 
{
}

void CModel::OpenGLLoadingPass()
{
	for (auto& mesh : m_Meshes)
		mesh.OpenGLLoadingPass();
}

CMesh * CModel::AddMesh(std::vector<float>& positions, std::vector<float>& text_coords, std::vector<float>& normals, std::vector<float>& tangents, std::vector<unsigned short>& indices, SMaterial & material, std::vector<SVertexBoneData>& bones)
{

	/*std::ofstream f("tangents.txt");
	for (auto& i : tangents)
	{
		f << i << "\n";
	}
	f.close();*/
	CMesh mesh(positions, text_coords, normals, tangents, indices, material, bones);
	// Normalize to define scale (height) 1 unit = 1 metr
	m_Meshes.push_back(std::move(mesh));
	CalculateBoudnigBox();
	return &m_Meshes.back();
}

glm::vec3 CModel::GetNormalizedScaleVector(float w, float h, float z) const
{
	int axis;
	if (w == 0 && h == 0 && z == 0)
		return glm::vec3(1);
	else if (w != 0 && h == 0 && z == 0)
		axis = 1;
	else if (w == 0 && h != 0 && z == 0)
		axis = 2;
	else if (w == 0 && h == 0 && z != 0)
		axis = 3;


	glm::vec3 scale_vector(1.f);
	switch (axis)
	{
	case 1:
		scale_vector = glm::vec3(w / m_BoundingBox.m_BoundingSize.x, w / m_BoundingBox.m_BoundingSize.x, w / m_BoundingBox.m_BoundingSize.x);
		break;
	case 2: scale_vector = glm::vec3(h / m_BoundingBox.m_BoundingSize.y, h / m_BoundingBox.m_BoundingSize.y, h / m_BoundingBox.m_BoundingSize.y);
		break;
	case 3: scale_vector = glm::vec3(z / m_BoundingBox.m_BoundingSize.z, z / m_BoundingBox.m_BoundingSize.z, z / m_BoundingBox.m_BoundingSize.z);
		break;
	default: scale_vector = glm::vec3(w / m_BoundingBox.m_BoundingSize.x, h / m_BoundingBox.m_BoundingSize.y, z / m_BoundingBox.m_BoundingSize.z);
		break;
	}
		
	return scale_vector;
	
}

void CModel::CalculateBoudnigBox()
{
	bool first = true;
	for (auto& mesh : m_Meshes)
	{
		if (first)
		{
			m_BoundingBox.m_BoundingBoxMin = mesh.GetBoundingMin();
			m_BoundingBox.m_BoundingBoxMax = mesh.GetBoundingMax();
			first = false;
		}
		else
		{
			m_BoundingBox.m_BoundingBoxMin = Utils::CalculateMinimumVector(m_BoundingBox.m_BoundingBoxMin, mesh.GetBoundingMin());
			m_BoundingBox.m_BoundingBoxMax = Utils::CalculateMinimumVector(mesh.GetBoundingMax(), m_BoundingBox.m_BoundingBoxMax);
			m_BoundingBox.m_BoundingBoxMax = Utils::CalculateMinimumVector(m_BoundingBox.m_BoundingBoxMax, mesh.GetBoundingMax());
		}
	}
	m_BoundingBox.m_BoundingSize = m_BoundingBox.m_BoundingBoxMax - m_BoundingBox.m_BoundingBoxMin;
	m_BoundingBox.m_BoundingCenter = (m_BoundingBox.m_BoundingBoxMax + m_BoundingBox.m_BoundingBoxMin) / 2.f;
}

