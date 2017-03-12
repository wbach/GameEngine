#include "TerrainRenderer.h"

CTerrainRenderer::CTerrainRenderer(SProjection * projection_matrix, std::weak_ptr<CFrameBuffer> framebuffer)
	: m_ProjectionMatrix(projection_matrix)
	, m_ClipPlane(glm::vec4(0, 1, 0, 100000))
	, CRenderer(framebuffer)
{
}

void CTerrainRenderer::Init()
{
	m_Shader.Init();
	m_Shader.Start();
	assert(m_ProjectionMatrix != nullptr);
	m_Shader.LoadViewDistance(500.f);
	m_Shader.LoadProjectionMatrix(m_ProjectionMatrix->GetProjectionMatrix());
	m_Shader.Stop();
	

	Log("CTerrainRenderer initialized.");
}

void CTerrainRenderer::PrepareFrame(CScene * scene)
{
	for (auto& sub : m_Subscribes)
	{
		sub->m_Quad.Init();
	}
	
	m_Shader.Start();
	m_Shader.LoadViewMatrix(scene->GetCamera()->GetViewMatrix());
	m_Shader.LoadCameraPosition(scene->GetCamera()->GetPosition());

	m_Shader.LoadTransformMatrix(Utils::CreateTransformationMatrix(glm::vec3(100, 0, 100), glm::vec3(0, 0, 0), glm::vec3(100)));
	m_Shader.LoadDispFactor(25);
	//m_Shader.LoadClipPlane(m_ClipPlane);
	//m_Shader.LoadShadowValues(0.f, 10.f, 10.f);

	m_RendererObjectPerFrame = 0;
	m_RendererVertixesPerFrame = 0;
	m_Shader.Stop();
}

void CTerrainRenderer::Render(CScene * scene)
{
	auto target = m_Target.lock();
	if (!target)
		return;

	target->BindToDraw();
	m_Shader.Start();
	for (auto& sub : m_Subscribes)
	{
		BindTextures(sub);

		if (sub->model != nullptr)
		{
			for (auto& m : sub->model->GetMeshes())
			{			
				Utils::EnableVao(m.GetVao(), m.GetUsedAttributes());
				glDrawElements(GL_PATCHES, m.GetVertexCount(), GL_UNSIGNED_SHORT, 0);
				Utils::DisableVao(m.GetUsedAttributes());
			}				
		}
		//sub->Render();
	}
	m_Shader.Stop();
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

void CTerrainRenderer::BindTextures(CTerrain * terrain) const
{
	int i = 0;
	for (auto& t : terrain->m_Textures)
	{
		if (t != nullptr)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, t->GetId());
		}
		i++;
	}
}
