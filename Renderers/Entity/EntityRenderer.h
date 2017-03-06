#pragma once
#include "../Renderer.h"
#include "Shaders/GeometryEntityShader.h"
#include "../../Utils/OpenGL/OpenGLUtils.h"

class CEntityRenderer : public CRenderer
{
public:
    CEntityRenderer(SProjection* projection_matrix);
	// Loading lights itp to shader
	virtual void Init() override;
	virtual void PrepareFrame(CScene* scene) override;
	virtual void Render(CScene* scene) override;
	virtual void EndFrame(CScene* scene) override;
	void RenderModel(CModel* model, const glm::mat4& transform_matrix) const;
private:
	void BindMaterial(const SMaterial& material) const;
	void UnBindMaterial(const SMaterial& material) const;
	CEntityGeometryPassShader m_Shader;
	SProjection* m_ProjectionMatrix;

	glm::vec4	m_ClipPlane;
};
