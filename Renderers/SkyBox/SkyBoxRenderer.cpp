#include "SkyBoxRenderer.h"

CSkyBoxRenderer::CSkyBoxRenderer(CModel *model, SProjection *projection_matrix, std::weak_ptr<CFrameBuffer> framebuffer)
    : m_Model(model)
    , m_ProjectionMatrix(projection_matrix)
    , CRenderer(framebuffer)
{

}

void CSkyBoxRenderer::Init()
{
    m_Shader.Init();
    m_Shader.Start();
    m_Shader.LoadProjectionMatrix(m_ProjectionMatrix->GetProjectionMatrix());
    m_Shader.LoadFogColour(.8f, .8f, .8f);
    m_Shader.LoadBlendFactor(1.f);
    m_Shader.Stop();
}

void CSkyBoxRenderer::PrepareFrame(CScene *scene)
{
   m_Shader.Start();
   m_Shader.LoadViewMatrix(scene->GetCamera()->GetViewMatrix(), 0.1f, 100.f);

   auto target = m_Target.lock();
   if (!target)
       return;

   target->BindToDraw();

   for(const auto& mesh : m_Model->GetMeshes())
   {

       glDrawElements(GL_TRIANGLES, mesh.GetVertexCount(), GL_UNSIGNED_SHORT, 0);
   }

   m_Shader.Stop();
}

void CSkyBoxRenderer::Render(CScene *scene)
{

}

void CSkyBoxRenderer::EndFrame(CScene *scene)
{

}

void CSkyBoxRenderer::Subscribe(CGameObject *gameObject)
{

}
