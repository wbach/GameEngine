#pragma once
#include "../GameObject.h"
#include "../../Resources/Models/Model.h"

class CEntity : public CGameObject
{
public:
	CEntity(CModel* model)
		: m_Model(model)
	{
	}
	CModel* GetModel() { return m_Model; }
private:
	CModel* m_Model;
};