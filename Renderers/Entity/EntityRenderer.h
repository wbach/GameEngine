#pragma once
#include "../Renderer.h"
#include "../../Shaders/Simple/Entity/SimpleEnityShader.h"
#include "../../Utils/OpenGL/OpenGLUtils.h"

class CEntityRenderer : public CRenderer
{
public:
	CEntityRenderer(glm::mat4* projection_matrix, bool use_simple_render = false);
	// Loading lights itp to shader
	virtual void Init() override;
	virtual void PrepareFrame(CScene* scene) override;
	virtual void Render(CScene* scene) override;
	virtual void EndFrame(CScene* scene) override;
	void RenderModel(CModel* model, const glm::mat4& transform_matrix) const;
private:
	void BindTextures(const SMaterial& material) const;
	std::unique_ptr<CEntityShader> m_Shader;
	glm::mat4* m_ProjectionMatrix;

	std::list<std::unique_ptr<CGameObject>> m_Objects;
	bool m_UseSimpleShader;
};

	
