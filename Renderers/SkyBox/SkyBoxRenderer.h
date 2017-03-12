#pragma once
#include "../Renderer.h"
#include "Shaders/SkyBoxShader.h"
#include "../../Utils/OpenGL/OpenGLUtils.h"
#include "../../Resources/Models/Model.h"

class CSkyBoxRenderer : public CRenderer
{
public:
    CSkyBoxRenderer(CModel* model, SProjection* projection_matrix, std::weak_ptr<CFrameBuffer> framebuffer);
    virtual void Init() override;
    virtual void PrepareFrame(CScene* scene) override;
    virtual void Render(CScene* scene) override;
    virtual void EndFrame(CScene* scene) override;
    virtual void Subscribe(CGameObject* gameObject) override;
private:
    CSkyBoxShader   m_Shader;
    CModel*         m_Model;
    SProjection*	m_ProjectionMatrix;
    glm::vec4	m_ClipPlane;
};

