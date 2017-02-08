#include "MaterialTexture.h"


CMaterialTexture::CMaterialTexture(const std::string & file, const std::string & filepath, const SImage & image)
	: m_Filename(file)
	, m_Fullpath(filepath)
	, m_Image(image)
{
}

void CMaterialTexture::OpenGLLoadingPass()
{
	if (m_Image.m_Data == nullptr || m_IsInit)
	{
		std::string error = "[Error] OGL There was an error loading the texture : " + filename + "\n";
		throw std::runtime_error(error.c_str());
	}

	glGenTextures(1, &m_Id);
	GLenum hubo_error = glGetError();

	if (hubo_error)
	{
		delete[] m_Image.m_Data;
		std::string error = "[Error] OGL There was an error loading the texture : " + filename + "\n";
		throw std::runtime_error(error.c_str());
	}

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_Id);
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Image. m_Width, m_Image.m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)m_Image.m_Data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (!m_KeepData)
	{
		delete[] m_Image.m_Data;
		m_Image.m_Data = nullptr;
	}		
	m_IsInit = true;
}