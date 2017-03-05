#include "FullRenderer.h"

void  FullRenderer ::Init()
{
     for(auto& renderer : m_Renderers)
    {
        renderer->Init();
    }
}
void FullRenderer ::PrepareFrame(CScene* scene)
{
    for(auto& renderer : m_Renderers)
    {
        renderer->PrepareFrame(scene);
    }
}
void FullRenderer ::Render(CScene* scene)
{
    for(auto& renderer : m_Renderers)
    {
        renderer->Render(scene);
    }
}
void FullRenderer ::EndFrame(CScene* scene)
{
    for(auto& renderer : m_Renderers)
    {
        renderer->EndFrame(scene);
    }
}
