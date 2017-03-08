#include "Entity.h"

CEntity::CEntity(CResourceManager & manager, const std::string & filename, const glm::vec3 & normalized_scale)
{
	m_Model = manager.LoadModel(filename);
	manager.GetOpenGlLoader().AddObjectToOpenGLLoadingPass(m_Model);
	m_Model->CalculateBoudnigBox();
	auto vec = m_Model->GetNormalizedScaleVector(normalized_scale.x, normalized_scale.y, normalized_scale.z);
	m_WorldTransform.SetNormalizedSize(vec);
}
