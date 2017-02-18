#pragma once
#include "Texture.h"
#include "Image.h"

class CMaterialTexture : public CTexture
{
public:
	CMaterialTexture(bool keepData, const std::string& file , const std::string& filepath, const SImage& image );
	virtual void OpenGLLoadingPass() override;
private:
	SImage m_Image;

	bool m_KeepData = false;
};