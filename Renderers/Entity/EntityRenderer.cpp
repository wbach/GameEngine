#include "EntityRenderer.h"

CEntityRenderer::CEntityRenderer(glm::mat4 * projection_matrix)
	: m_ProjectionMatrix(projection_matrix)
{
}

void CEntityRenderer::Init()
{
	m_Shader.Init();
	m_Shader.Start();
	assert(m_ProjectionMatrix != nullptr);
	m_Shader.LoadProjectionMatrix(*m_ProjectionMatrix);
	m_Shader.Stop();
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
		if (entity->GetModel() == nullptr)
			continue;

		RenderModel(entity->GetModel(), entity->GetWorldTransform().GetMatrix());
	}
}

void CEntityRenderer::EndFrame(CScene * scene)
{
	m_Shader.Stop();
}

void CEntityRenderer::RenderModel(CModel * model, const glm::mat4 & transform_matrix) const
{
	m_Shader.LoadTransformMatrix(transform_matrix);

	for (const auto& mesh : model->GetMeshes())
	{
		Utils::EnableVao(mesh.GetVao(), mesh.GetUsedAttributes());
		BindTextures(mesh.GetMaterial());
		glDrawElements(GL_TRIANGLES, mesh.GetVertexCount(), GL_UNSIGNED_SHORT, 0);
		Utils::DisableVao(mesh.GetUsedAttributes());
	}
}

void CEntityRenderer::BindTextures(const SMaterial & material) const
{
	if (material.m_DiffuseTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material.m_DiffuseTexture->GetId());	
			//TODO : load using texture to shader
			//m_SimpleShader.LOad
	}
}
