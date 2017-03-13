#include "GrassRenderer.h"

CGrassRenderer::CGrassRenderer(SProjection * projection_matrix, std::weak_ptr<CFrameBuffer> framebuffer)
	: m_Projection(projection_matrix)
	, m_Texture(nullptr)
	, CRenderer(framebuffer)
{	
}

void CGrassRenderer::Init()
{	
	m_Shader.Init();
	m_Shader.Start();
	m_Shader.LoadProjectionMatrix(m_Projection->GetProjectionMatrix());
	m_Shader.Stop();

	for (float y = 0.f; y < 100.f; y++)
		for (float x = 0.f; x < 100.f; x++)
		{
			grassvertex.push_back(x * 2.f);
			grassvertex.push_back(1);
			grassvertex.push_back(y *2.f);
		}
	m_MeshVao = Utils::CreateVao();
	m_VertexSize = grassvertex.size() / 3;
	m_VertexVbo = Utils::StoreDataInAttributesList(0, 3, grassvertex);
	Utils::UnbindVao();
	grassvertex.clear();

	Log("Grass renderer initialized.");
}

void CGrassRenderer::PrepareFrame(CScene * scene)
{
	if (m_Texture == nullptr)
	{
		m_Texture = scene->GetResourceManager().GetTextureLaoder().LoadTextureImmediately("../Data/Textures/G3_Nature_Plant_Grass_06_Diffuse_01.png");
	}
}

void CGrassRenderer::Render(CScene * scene)
{
	auto target = m_Target.lock();
	if (!target)
		return;
	target->BindToDraw();

	m_Shader.Start();
	m_Shader.LoadGlobalTime(scene->GetDeltaTime());
	m_Shader.LoadShadowValues(0.f, 0.f, 512.f);
	m_Shader.LoadViewMatrix(scene->GetCamera()->GetViewMatrix());
	m_Shader.LoadViewDistance(1000.f);

	Utils::DisableCulling();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture->GetId());

	glBindVertexArray(m_MeshVao);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_POINTS, 0, m_VertexSize);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	Utils::EnableCulling();
	
	m_Shader.Stop();
}

void CGrassRenderer::EndFrame(CScene * scene)
{
}

void CGrassRenderer::Subscribe(CGameObject * gameObject)
{
}
