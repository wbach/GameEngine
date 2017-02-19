#pragma once
#include <string>
#include <list>
#include <memory>
#include "Transform.h"
#include "../Components/Component.h"

class CGameObject
{
public:
	CGameObject();
	const auto& GetChildrens() { return m_Childrens; }
	const CTransform& GetLocalTransform() const;
	const CTransform& GetWorldTransform() const;
protected:
	std::list<std::unique_ptr<CGameObject>> m_Childrens;
	std::list<std::unique_ptr<CComponent>>  m_Components;

	std::string m_Name;

	CTransform m_LocalTransform;
	CTransform m_WorldTransform;

	static uint s_ID;
	uint m_ID;
};
