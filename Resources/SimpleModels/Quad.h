#pragma once
#include "../../Utils/OpenGL/OpenGLUtils.h"

struct SSimpleQuad
{
	bool isInit = false;
	int m_IndicesSize = 0;
	GLuint vao, i_vbo, vbo_id, vbo_text_id;
	void Init() {
		Utils::CreateQuad(vao, i_vbo, vbo_id, vbo_text_id, m_IndicesSize);
		isInit = true;
	}
	~SSimpleQuad()
	{
		if (isInit)
			Utils::DeleteQuad(vao, i_vbo, vbo_id, vbo_text_id);
	}
};
