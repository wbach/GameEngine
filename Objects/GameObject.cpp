#include "GameObject.h"

uint CGameObject::s_ID = 0;

CGameObject::CGameObject()
	: m_ID(s_ID++)
{
}

const CTransform & CGameObject::GetLocalTransform()
{
	return m_LocalTransform;
}

const CTransform & CGameObject::GetWorldTransform()
{
	return m_WorldTransform;
}

