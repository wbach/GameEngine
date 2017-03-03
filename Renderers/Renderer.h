#pragma once
#include "../Scene/Scene.hpp"

class CRenderer
{
public:
    virtual void Init() = 0 ;
    virtual void PrepareFrame(CScene* scene) = 0;
    virtual void Render(CScene* scene) = 0;
	virtual void EndFrame(CScene* scene) = 0;
    //Debug
    const unsigned int& GetObjectsPerFrame();
	const unsigned int& GetVertexPerFrame();
protected:
    //Debug variables
    unsigned int m_RendererObjectPerFrame = 0;
	unsigned int m_RendererVertixesPerFrame = 0;
	unsigned int m_MaxVerices = 0;
};
