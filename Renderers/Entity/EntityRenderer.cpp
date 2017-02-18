#include "EntityRenderer.h"

CEntityRenderer::CEntityRenderer(glm::mat4 * projection_matrix)
	: m_ProjectionMatrix(projection_matrix)
{
}

void CEntityRenderer::Init()
{
	m_Shader.Init();
	assert(m_ProjectionMatrix != nullptr);
	m_Shader.LoadProjectionMatrix(*m_ProjectionMatrix);
}

void CEntityRenderer::PrepareFrame(CScene * scene)
{
	m_Shader.Start();
	m_Shader.LoadViewMatrix(scene->GetCamera()->GetViewMatrix());
}

void CEntityRenderer::Render(CScene * scene)
{
	for (auto& entity : scene->GetEntities())
	{

	}
}

void CEntityRenderer::RenderModel(CModel * model, const glm::mat4 & transform_matrix) const
{
	for (const auto& mesh : model->GetMeshes())
	{
		Utils::EnableVao(mesh.GetVao(), mesh.GetUsedAttributes());
	}
}
