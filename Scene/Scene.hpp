#pragma once
#include <list>
#include "../Objects/GameObject.h"
#include "../Camera/Camera.h"

class CScene
{
public:
    std::list<CGameObject*> GetObjectInRange(const glm::vec3& position, float range);
private:
    std::list<std::unique_ptr<CGameObject>> m_Objects;
    std::unique_ptr<CCamera> m_Camera;
};
