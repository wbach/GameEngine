#include "Model.h"


CModel::CModel()
{

}

void CModel::InitModel(std::string file_name)
{
}

CMesh * CModel::AddMesh(std::vector<float>& positions, std::vector<float>& text_coords, std::vector<float>& normals, std::vector<float>& tangents, std::vector<unsigned short>& indices, SMaterial & material, std::vector<SVertexBoneData>& bones)
{
	CMesh mesh(positions, text_coords, normals, tangents, indices, material, bones);
	// Normalize to define scale (height) 1 unit = 1 metr
	mesh.CalculateBoudnigBox(positions);
	m_Meshes.push_back(std::move(mesh));
	return &m_Meshes.back();
}
