#pragma once
#include <list>
#include <vector>
#include "GameObject.h"

struct GameObjectManager
{
	std::list<std::unique_ptr<CGameObject>> m_Objects;
	std::vector<std::list<CGameObject*>> m_ObjectInGrid;
};