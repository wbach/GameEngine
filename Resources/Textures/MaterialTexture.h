#pragma once
#include "Texture.h"
#include "Image.h"

class CMaterialTexture : public CTexture
{
public:
	CMaterialTexture(const std::string& file , const std::string& filepath, const SImage& image );
	virtual void OpenGLLoadingPass() override;
private:
	std::string m_Filename;
	std::string m_Fullpath;

	SImage m_Image;

	bool m_KeepData = false;
};