#pragma once
#include <list>
#include "../Objects/GameObject.h"
#include "../Camera/Camera.h"
#include <vector>
#include "../Lights/Light.h"
#include "../Objects/RenderAble/Entity.h"
#include "../Resources/ResourceManager.h"

//Object in scene are in grid (one grid size)
const unsigned int OBJECT_GRID_SIZE = 500;
// const int grid count y in worlds
const unsigned int OBJECT_GRID_COUNT = 100;

class CScene
{
public:
	CScene();

	virtual		 ~CScene() {}
	virtual int	 Initialize() = 0;
	virtual void PostInitialize() {};
	virtual int	 Update() = 0;

	//Add Entities
	void AddObject(std::unique_ptr<CGameObject> object);
	CEntity* AddEntity(const std::string& filename, const glm::vec3 normalized_scale, const glm::vec3& position = glm::vec3(0.f));

	//GetObjects
    std::list<CGameObject*> GetObjectInRange(const glm::vec3& position, float range);
	const std::list<std::unique_ptr<CEntity>>& GetEntities() { return m_Entities; }

	//Cameras
	CCamera* GetCamera();
	
	//Lights
	const CLight& GetDirectionalLight() const;
	const std::vector<CLight>&	GetLights() const;

	//Resources
	CResourceManager& GetResourceManager() { return m_ResourceManager; }
protected:
	//Minimum one light on scene only (night - decrease strength)
	CLight				m_DirectionalLight;
	std::vector<CLight>	m_Lights;

    std::list<std::unique_ptr<CEntity>> m_Entities;

    std::unique_ptr<CCamera> m_Camera;

	CResourceManager m_ResourceManager;
};
