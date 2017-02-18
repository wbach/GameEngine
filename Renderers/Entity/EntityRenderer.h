#pragma once
#include "../Renderer.h"
#include "../../Shaders/Simple/Entity/SimpleEnityShader.h"
#include "../../Utils/OpenGL/OpenGLUtils.h"

class CEntityRenderer : public CRenderer
{
public:
	CEntityRenderer(glm::mat4* projection_matrix);
	// Loading lights itp to shader
	virtual void Init() override;
	virtual void PrepareFrame(CScene* scene) override;
	virtual void Render(CScene* scene) override;
	void RenderModel(CModel* model, const glm::mat4& transform_matrix) const;
private:
	CSimpleEntityShader m_Shader;
	glm::mat4* m_ProjectionMatrix;

	std::list<std::unique_ptr<CGameObject>> m_Objects;
};

	
