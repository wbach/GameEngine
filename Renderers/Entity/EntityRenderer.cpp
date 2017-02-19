#include "EntityRenderer.h"

CEntityRenderer::CEntityRenderer(glm::mat4 * projection_matrix, bool use_simple_render)
	: m_ProjectionMatrix(projection_matrix)
	, m_UseSimpleShader(use_simple_render)
{
	if (m_UseSimpleShader)
	{
		m_Shader = std::make_unique<CSimpleEntityShader>();
	}
	else
	{

	}
}

void CEntityRenderer::Init()
{
	m_Shader->Init();
	m_Shader->Start();
	assert(m_ProjectionMatrix != nullptr);
	m_Shader->LoadProjectionMatrix(*m_ProjectionMatrix);
	m_Shader->Stop();
}

void CEntityRenderer::PrepareFrame(CScene * scene)
{
	m_Shader->Start();
	m_Shader->LoadViewMatrix(scene->GetCamera()->GetViewMatrix());
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
	m_Shader->Stop();
}

void CEntityRenderer::RenderModel(CModel * model, const glm::mat4 & transform_matrix) const
{
	m_Shader->LoadTransformMatrix(transform_matrix);

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

	if (m_UseSimpleShader)
		return;

	if (material.m_AmbientTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, material.m_AmbientTexture->GetId());
	}
	if (material.m_NormalTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, material.m_NormalTexture->GetId());
	}
	if (material.m_SpecularTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, material.m_SpecularTexture->GetId());
	}
}
