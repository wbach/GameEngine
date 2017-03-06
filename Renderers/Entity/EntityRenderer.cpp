#include "EntityRenderer.h"

CEntityRenderer::CEntityRenderer(SProjection* projection_matrix)
	: m_ProjectionMatrix(projection_matrix)
	, m_ClipPlane(glm::vec4(0, 1, 0, 100000))
{
}

void CEntityRenderer::Init()
{
	m_Shader.Init();
	m_Shader.Start();
	assert(m_ProjectionMatrix != nullptr);
	m_Shader.LoadViewDistance(500.f);
	m_Shader.LoadProjectionMatrix(m_ProjectionMatrix->GetProjectionMatrix());
	m_Shader.Stop();
}

void CEntityRenderer::PrepareFrame(CScene * scene)
{
	m_Shader.Start();
	m_Shader.LoadViewMatrix(scene->GetCamera()->GetViewMatrix());
	m_Shader.LoadClipPlane(m_ClipPlane);
	m_Shader.LoadShadowValues(0.f, 10.f, 10.f);

	m_RendererObjectPerFrame = 0;
	m_RendererVertixesPerFrame = 0;
	m_Shader.Stop();
}

void CEntityRenderer::Render(CScene * scene)
{
	m_Shader.Start();
	for (auto& entity : scene->GetEntities())
	{
		if (entity->GetModel() == nullptr)
			continue;

		RenderModel(entity->GetModel(), entity->GetWorldTransform().GetMatrix());
	}
	m_Shader.Stop();
}

void CEntityRenderer::EndFrame(CScene * scene)
{	
	m_Shader.Stop();
}

void CEntityRenderer::RenderModel(CModel * model, const glm::mat4 & transform_matrix) const
{
	m_Shader.LoadTransformMatrix(transform_matrix);	
	m_Shader.LoadUseInstancedRendering(0.f);
	m_Shader.LoadUseFakeLight(0.f);
	m_Shader.LoadUseBonesTransformation(0.f);

	for (const auto& mesh : model->GetMeshes())
	{
		Utils::EnableVao(mesh.GetVao(), mesh.GetUsedAttributes());
		BindMaterial(mesh.GetMaterial());			

		glDrawElements(GL_TRIANGLES, mesh.GetVertexCount(), GL_UNSIGNED_SHORT, 0);
		Utils::DisableVao(mesh.GetUsedAttributes());

		UnBindMaterial(mesh.GetMaterial());
	}
}

void CEntityRenderer::BindMaterial(const SMaterial & material) const
{
	if (material.isTransparency)
		Utils::DisableCulling();

	m_Shader.LoadMeshMaterial(material);

	if (material.m_DiffuseTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material.m_DiffuseTexture->GetId());	
		m_Shader.LoadUseTexture(1.f);
	}
	else
		m_Shader.LoadUseTexture(0.f);

	if (material.m_AmbientTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, material.m_AmbientTexture->GetId());
	}

	if (material.m_NormalTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, material.m_NormalTexture->GetId());
		m_Shader.LoadUseNormalMap(1.f);
	}
	else
		m_Shader.LoadUseNormalMap(0.f);

	if (material.m_SpecularTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, material.m_SpecularTexture->GetId());
	}
}

void CEntityRenderer::UnBindMaterial(const SMaterial & material) const
{
	if (material.isTransparency)
		Utils::EnableCulling();
}
