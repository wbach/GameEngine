#include "EntityShader.h"

void CEntityShader::Init()
{
	InitShaderProgram("Data/Shaders/Simple/SimpleEntityShader.vert", "Data/Shaders/Simple/SimpleEntityShader.frag");
	Start();
	GetAllUniformLocations();
	Stop();
}

void CEntityShader::GetAllUniformLocations()
{
	location_TransformationMatrix = GetUniformLocation("TransformationMatrix");
	location_ProjectionMatrix = GetUniformLocation("ProjectionMatrix");
	location_ViewMatrix = GetUniformLocation("ViewMatrix");

	location_IsInstancedRender = GetUniformLocation("IsInstancedRender");

	//Animations
	location_UseBoneTransform = GetUniformLocation("UseBoneTransform");

	for (int x = 0; x < MAX_BONES; x++)
	{
		char tmpVariableName[50]; ; memset(tmpVariableName, 0, 50);
		sprintf(tmpVariableName, "Bones[%i]", x);
		location_Bones[x] = GetUniformLocation(tmpVariableName);
	}
}

void CEntityShader::BindAttributes()
{
	BindAttribute(0, "Position");
	BindAttribute(1, "TexCoord");
	BindAttribute(4, "TransformationMatrixes");
}
void CEntityShader::LoadUseInstancedRendering(const float & use) const
{
	LoadValue(location_IsInstancedRender, use);
}
void CEntityShader::LoadTransformMatrix(const glm::mat4& matrix) const
{
	LoadValue(location_TransformationMatrix, matrix);
}

void CEntityShader::LoadProjectionMatrix(const glm::mat4& matrix) const
{
	LoadValue(location_ProjectionMatrix, matrix);
}

void CEntityShader::LoadViewMatrix(const glm::mat4& matrix) const
{
	LoadValue(location_ViewMatrix, matrix);
}
void CEntityShader::LoadUseBonesTransformation(const float & is) const
{
	LoadValue(location_UseBoneTransform, is);
}
void CEntityShader::LoadBoneTransform(const glm::mat4 & transform, unsigned int id) const
{
	LoadValue(location_Bones[id], transform);
}