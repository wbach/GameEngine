#pragma once
#include "../Renderer.h"
#include "Shaders/GeometryEntityShader.h"
#include "../../Utils/OpenGL/OpenGLUtils.h"

class CEntityRenderer : public CRenderer
{
public:
    CEntityRenderer(glm::mat4* projection_matrix);
	// Loading lights itp to shader
	virtual void Init() override;
	virtual void PrepareFrame(CScene* scene) override;
	virtual void Render(CScene* scene) override;
	virtual void EndFrame(CScene* scene) override;
	void RenderModel(CModel* model, const glm::mat4& transform_matrix) const;
private:
	void BindTextures(const SMaterial& material) const;
	CEntityGeometryPassShader m_Shader;
	glm::mat4* m_ProjectionMatrix;
};
