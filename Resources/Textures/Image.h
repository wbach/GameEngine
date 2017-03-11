#pragma once
#include <GL/glew.h>

struct SImage
{
	GLubyte* m_Data = nullptr;
	unsigned int m_Width = 0, m_Height = 0;

	~SImage()
	{
		if (m_Data == nullptr)
			delete m_Data;
	}
};