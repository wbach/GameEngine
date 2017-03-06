#include "GameObject.h"

uint CGameObject::s_ID = 0;

CGameObject::CGameObject()
	: m_ID(s_ID++)
{
}