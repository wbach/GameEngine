#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>
#include "../OpenGLObject.h"

class CTexture : public COpenGLObject
{
public:
	virtual void OpenGLLoadingPass() = 0;
	const GLuint& GetId() const { return m_Id; }
	virtual ~CTexture()
	{
		if (!m_IsInit)
			return;
		glDeleteTextures(1, &m_Id);
	}

protected:
	GLuint m_Id = 0;
	bool m_IsInit = false;

	std::string filename;
	std::string fullpath;
};