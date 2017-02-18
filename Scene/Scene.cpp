#include "Scene.hpp"

void CScene::AddObject(std::unique_ptr<CGameObject> object)
{
	m_Objects.push_back(object);
}

std::list<CGameObject*> CScene::GetObjectInRange(const glm::vec3 & position, float range)
{
	int x = static_cast<unsigned int>(position.x / OBJECT_GRID_SIZE);
	int y = static_cast<unsigned int>(position.z / OBJECT_GRID_SIZE);

	return m_ObjectInGrid[x + y*OBJECT_GRID_COUNT];
}

CCamera * CScene::GetCamera()
{
	return m_Camera.get();
}

const std::vector<CLight>& CScene::GetLights() const
{
	return m_Lights;
}
