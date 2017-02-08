#pragma once
#include <string>
#include <list>
#include <memory>
#include "Transform.h"

class CGameObject
{
public:
	CGameObject();
	virtual void Render() = 0;
	const auto& GetChildrens() { return m_Childrens; }
	const CTransform& GetLocalTransform();
	const CTransform& GetWorldTransform();
protected:
	std::list<std::unique_ptr<CGameObject>> m_Childrens;
	std::string m_Name;

	CTransform m_LocalTransform;
	CTransform m_WorldTransform;

	static uint s_ID;
	uint m_ID;
};