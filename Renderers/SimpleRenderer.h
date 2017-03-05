#pragma once
#include "Renderer.h"
#include "Entity/Shaders/SimpleEnityShader.h"

class SimpleRenderer : public CRenderer
{
public:
    SimpleRenderer(glm::mat4* projection_matrix);

	virtual void Init() override;
	virtual void PrepareFrame(CScene* scene) override;
	virtual void Render(CScene* scene) override;
	virtual void EndFrame(CScene* scene) override;
	void RenderModel(CModel* model, const glm::mat4& transform_matrix) const;
private:
	void BindTextures(const SMaterial& material) const;

	CSimpleEntityShader m_Shader;
	glm::mat4* m_ProjectionMatrix;
};
