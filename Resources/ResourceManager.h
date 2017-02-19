#pragma once
#include "Models/Model.h"
#include "Models/Assimp/AssimpModel.h"
#include "TextureLoader.h"
#include "OpenGLLoader.h"
#include "SimpleModels/Quad.h"
#include <vector>
#include <memory>

class CResourceManager
{
public:
	CResourceManager();
	CModel* LoadModel(const std::string& file);
	CModel* GetModel(unsigned int id) { return m_Models[id].get(); }
	COpenGLLoader& GetOpenGlLoader() { return m_OpenGlLoader; }
	CTextureLoader& GetTextureLaoder() { return m_TextureLoader; }
private:
	std::vector<std::unique_ptr<CModel>>    m_Models;
	std::vector<std::unique_ptr<CTexture>>	m_Textures;

	COpenGLLoader m_OpenGlLoader;
	CTextureLoader m_TextureLoader;
};
