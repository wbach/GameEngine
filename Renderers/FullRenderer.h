#pragma once
#include "Renderer.h"
#include "Entity/EntityRenderer.h"
class FullRenderer : public CRenderer
{
    public:
	FullRenderer(glm::mat4* projection_matrix, bool use_simple_render = false);
	// Loading lights itp to shader
	virtual void Init() override;
	virtual void PrepareFrame(CScene* scene) override;
	virtual void Render(CScene* scene) override;
	virtual void EndFrame(CScene* scene) override;
private:

	glm::mat4* m_ProjectionMatrix;

	//ShadowMap renderes, etc...
	std::vector<std::unique_ptr<CRenderer>> m_Renderers;
};