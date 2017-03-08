#pragma once
#include "../GameObject.h"
#include "../../Resources/Models/Model.h"
#include "../../Resources/ResourceManager.h"

class CEntity : public CGameObject
{
public:
	CEntity(CResourceManager& manager, const std::string& filename, const glm::vec3& normalized_scale);
	CEntity(CModel* model, const glm::vec3 normalized_v)
		: m_Model(model)
	{
		m_WorldTransform.SetNormalizedSize(normalized_v);
	}
	CModel* GetModel() { return m_Model; }
private:
	CModel* m_Model;
};