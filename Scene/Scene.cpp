#include "Scene.hpp"

CScene::CScene()
	: m_DirectionalLight(glm::vec3(10000, 15000, 10000), glm::vec3(0.8))
{
}

void CScene::AddObject(std::unique_ptr<CGameObject> object)
{
	//m_Objects.push_back(object);
}

void CScene::AddEntity(const std::string & filename)
{
	auto model = m_ResourceManager.LoadModel(filename);
	m_ResourceManager.GetOpenGlLoader().AddObjectToOpenGLLoadingPass(model);
	m_Entities.push_back(std::make_unique<CEntity>(model));
}

std::list<CGameObject*> CScene::GetObjectInRange(const glm::vec3 & position, float range)
{
	int x = static_cast<unsigned int>(position.x / OBJECT_GRID_SIZE);
	int y = static_cast<unsigned int>(position.z / OBJECT_GRID_SIZE);

	return std::list<CGameObject*>();// m_ObjectInGrid[x + y*OBJECT_GRID_COUNT];
}

CCamera * CScene::GetCamera()
{
	return m_Camera.get();
}

const CLight & CScene::GetDirectionalLight() const
{
	return m_DirectionalLight;
}

const std::vector<CLight>& CScene::GetLights() const
{
	return m_Lights;
}
