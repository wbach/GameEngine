#pragma once
#include <string>
#include <list>
#include <memory>
#include "Transform.h"
#include "../Components/Component.h"

class CGameObject
{
public:
	virtual ~CGameObject() {}
	CGameObject();
        const std::list<std::unique_ptr<CGameObject>>& GetChildrens() { return m_Childrens; }
		CTransform m_LocalTransform;
		CTransform m_WorldTransform;
protected:
	std::list<std::unique_ptr<CGameObject>> m_Childrens;
	std::list<std::unique_ptr<CComponent>>  m_Components;
	std::string m_Name;	
	static uint s_ID;
	uint m_ID;
};
