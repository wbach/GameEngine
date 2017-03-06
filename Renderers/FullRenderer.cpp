#include "FullRenderer.h"

FullRenderer::FullRenderer(SProjection* projection_matrix)
	: m_LightPassRenderer(projection_matrix)
	, m_ProjectionMatrix(projection_matrix)
{
	m_Renderers.push_back(std::make_unique<CEntityRenderer>(projection_matrix));
}

void FullRenderer::Init()
{
	m_DefferedFrameBuffer.Init(m_ProjectionMatrix->GetWindowSize());

     for(auto& renderer : m_Renderers)
    {
        renderer->Init();
    }

	 m_LightPassRenderer.Init();
}
void FullRenderer::PrepareFrame(CScene* scene)
{
    for(auto& renderer : m_Renderers)
    {
        renderer->PrepareFrame(scene);
    }
	m_LightPassRenderer.PrepareFrame(scene);
}
void FullRenderer::Render(CScene* scene)
{
	m_DefferedFrameBuffer.BindToDraw();

	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

    for(auto& renderer : m_Renderers)
    {
        renderer->Render(scene);
    }

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	m_DefferedFrameBuffer.BindTextures();
	m_LightPassRenderer.Render(scene);
}
void FullRenderer::EndFrame(CScene* scene)
{
    for(auto& renderer : m_Renderers)
    {
        renderer->EndFrame(scene);
    }
	m_LightPassRenderer.EndFrame(scene);
}
