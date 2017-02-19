#pragma once
#include <string>
#include <vector>
#include <FreeImage.h>
#include "Models/Material.h"
#include "Textures/MaterialTexture.h"
#include <memory>
#include <algorithm>
#include <list>
#include "OpenGLLoader.h"
#include "freeImage/FreeImage.h"

namespace TextureType
{
	enum Type
	{
		MATERIAL = 0
	};
}

class CTextureLoader
{
public:
	CTextureLoader(std::vector<std::unique_ptr<CTexture>>& textures_vector, COpenGLLoader& openGLLoader);
	void ReadFile(const std::string& file, SImage& image, TextureFlip::Type flip_mode = TextureFlip::NONE);
	//Return place in texture loader not in OpenGL
	CTexture* LoadTexture(const std::string& file, bool opengl_pass = true, TextureType::Type type = TextureType::MATERIAL, TextureFlip::Type flip_mode = TextureFlip::NONE);
	CTexture* LoadTextureImmediately(const std::string& file, TextureType::Type type = TextureType::MATERIAL, TextureFlip::Type flip_mode = TextureFlip::NONE);
private:
	std::vector<std::unique_ptr<CTexture>>& m_Textures;
	COpenGLLoader&   m_OpenGLLoader;
	glm::vec2 m_MaxTextureResolution;	
};