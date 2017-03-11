#include "FullRenderer.h"

FullRenderer::FullRenderer(SProjection* projection_matrix)
	: m_ProjectionMatrix(projection_matrix)
	, m_DefferedFrameBuffer(new CDefferedFrameBuffer())
{
	m_Renderers.push_back(std::make_unique<CTerrainRenderer>(projection_matrix, m_DefferedFrameBuffer));
	m_Renderers.emplace_back(new CEntityRenderer(projection_matrix, m_DefferedFrameBuffer));
	//LightPass have to be after all geometry passes
	m_Renderers.emplace_back(new CLightPassRenderer(projection_matrix, m_DefferedFrameBuffer));	
}

void FullRenderer::Init()
{
	m_DefferedFrameBuffer->Init(m_ProjectionMatrix->GetWindowSize());

     for(auto& renderer : m_Renderers)
    {
        renderer->Init();
    }
	Log("FullRenderer initialized.");
}
void FullRenderer::PrepareFrame(CScene* scene)
{
	m_DefferedFrameBuffer->Clean();

    for(auto& renderer : m_Renderers)
    {
        renderer->PrepareFrame(scene);
    }	
	//glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_BACK, GL_LINE);
}
void FullRenderer::Render(CScene* scene)
{
    for(auto& renderer : m_Renderers)
    {
        renderer->Render(scene);
    }
}
void FullRenderer::EndFrame(CScene* scene)
{
    for(auto& renderer : m_Renderers)
    {
        renderer->EndFrame(scene);
    }
}

void FullRenderer::Subscribe(CGameObject * gameObject)
{
	for (auto& renderer : m_Renderers)
		renderer->Subscribe(gameObject);
}
