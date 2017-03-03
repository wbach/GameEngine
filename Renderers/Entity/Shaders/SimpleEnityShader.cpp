#include "SimpleEnityShader.h"

void CSimpleEntityShader::Init()
{
	InitShaderProgram("../Data/Shaders/Simple/SimpleEntityShader.vert", "../Data/Shaders/Simple/SimpleEntityShader.frag");
	Start();
	GetAllUniformLocations();
	BindAttributes();
	Stop();
}