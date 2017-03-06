#pragma once
#include "Renderer.h"
#include "Entity/EntityRenderer.h"
#include "Framebuffer/DeferedFrameBuffer/DeferedFrameBuffer.h"
#include "LightPassRenderer.h"

class FullRenderer : public CRenderer
{
public:
	FullRenderer(SProjection* projection_matrix);
	// Loading lights itp to shader
	virtual void Init() override;
	virtual void PrepareFrame(CScene* scene) override;
	virtual void Render(CScene* scene) override;
	virtual void EndFrame(CScene* scene) override;
private:

	SProjection* m_ProjectionMatrix;

	//ShadowMap renderes, etc...
	std::vector<std::unique_ptr<CRenderer>> m_Renderers;

	CLightPassRenderer m_LightPassRenderer;
	CDefferedFrameBuffer m_DefferedFrameBuffer;
};