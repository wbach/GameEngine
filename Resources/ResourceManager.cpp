#include "ResourceManager.h"

CResourceManager::CResourceManager()
	:  m_TextureLoader(m_Textures, m_OpenGlLoader)
{
}

CModel * CResourceManager::LoadModel(const std::string & file)
{
	m_Models.push_back(std::make_unique<CAssimModel>(m_TextureLoader));
	m_Models.back()->InitModel(file);
	return m_Models.back().get();
}
