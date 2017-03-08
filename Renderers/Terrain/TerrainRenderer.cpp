#include "TerrainRenderer.h"

CTerrainRenderer::CTerrainRenderer(SProjection * projection_matrix)
	: m_ProjectionMatrix(projection_matrix)
	, m_ClipPlane(glm::vec4(0, 1, 0, 100000))
{
}

void CTerrainRenderer::Init()
{
	m_Shader.Init();
	//m_Shader.Start();
	//assert(m_ProjectionMatrix != nullptr);
	////_Shader.LoadViewDistance(500.f);
	//m_Shader.LoadProjectionMatrix(m_ProjectionMatrix->GetProjectionMatrix());
	//m_Shader.Stop();
}

void CTerrainRenderer::PrepareFrame(CScene * scene)
{
	//m_Shader.Start();
	//m_Shader.LoadViewMatrix(scene->GetCamera()->GetViewMatrix());
	////m_Shader.LoadClipPlane(m_ClipPlane);
	////m_Shader.LoadShadowValues(0.f, 10.f, 10.f);

	//m_RendererObjectPerFrame = 0;
	//m_RendererVertixesPerFrame = 0;
	//m_Shader.Stop();
}

void CTerrainRenderer::Render(CScene * scene)
{

}

void CTerrainRenderer::EndFrame(CScene * scene)
{

}

void CTerrainRenderer::Subscribe(CGameObject * gameObject)
{
	auto terrain = dynamic_cast<CTerrain*>(gameObject);
	if (terrain != nullptr)
		m_Subscribes.push_back(terrain);
}

void CTerrainRenderer::RenderModel(CModel * model, const glm::mat4 & transform_matrix) const
{
}

void CTerrainRenderer::BindMaterial(const SMaterial & material) const
{
}

void CTerrainRenderer::UnBindMaterial(const SMaterial & material) const
{
}
