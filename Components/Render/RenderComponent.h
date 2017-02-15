#pragma once
#include "../Component.h"
#include "RenderInfo.h"

class CRenderComponent : public CComponent
{
public:
    CRenderComponent(CResourceManager& rm, std::list<CComponent*>& render_list)
    {
    }
    void Update()
    {
        m_RenderList.push_back(this);
        RenderInfo info;
        info.m_RenderFunction = std::bind(&CRenderComponent::Update, this);
    }
    void Render()
    {
        m_Shader->LoadTransformMatrix()
        for(const auto& mesh : model->GetMeshes())
        {
            EnableVao(mesh.GetVao(), 3);
            glDrawElements(GL_TRIANGLES, mesh.GetVertexCount());
            DisableVao(3);
        }
    }
private:
    void EnableVao(int vao, int acount)
    {
        glBindVertexArray(vao);
        for(int x = 0; x < acount; x++)
            glEnableVertexAttribArray(x);
    }
    void DisableVao(int acount)
    {
        for(int x = acount; x > 0; x--)
            glDisableVertexAttribArray(x);
         glBindVertexArray(0);
    }

    CModel *model;
    CShaderProgram* m_Shader;
    std::list<CComponent*>& m_RenderList;
};
