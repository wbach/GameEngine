#include "GeometryEntityShader.h"

void CEntityGeometryPassShader::GetAllUniformLocations()
{
	CEntityShader::GetAllUniformLocations();

	location_ClipPlane = GetUniformLocation("ClipPlane");

	location_UseFakeLighting = GetUniformLocation("IsUseFakeLighting");
	location_UseNormalMap = GetUniformLocation("IsUseNormalMap");
	//Textures
	location_UseTexture = GetUniformLocation("UseTexture");
	location_ModelTexture = GetUniformLocation("gColorMap");
	location_NormalMap = GetUniformLocation("NormalMap");

	//Shadows
	location_ShadowVariables = GetUniformLocation("ShadowVariables");
	location_ShadowMap = GetUniformLocation("ShadowMap");
	location_ToShadowMapSpace = GetUniformLocation("ToShadowMapSpace");

	//Mesh Material
	location_MaterialAmbient = GetUniformLocation("ModelMaterial.m_Ambient");
	location_MaterialDiffuse = GetUniformLocation("ModelMaterial.m_Diffuse");
	location_MaterialSpecular = GetUniformLocation("ModelMaterial.m_Specular");

	//Skip render
	location_ViewDistance = GetUniformLocation("ViewDistance");
}

void CEntityGeometryPassShader::ConnectTextureUnits()
{
	LoadValue(location_ModelTexture, 0);
	LoadValue(location_NormalMap, 1);
	LoadValue(location_ShadowMap, 2);
}

void CEntityGeometryPassShader::BindAttributes()
{
	BindAttribute(0, "Position");
	BindAttribute(1, "TexCoord");
	BindAttribute(2, "Normal");
	BindAttribute(3, "Tangent");
	BindAttribute(4, "TransformationMatrixes");
}

void CEntityGeometryPassShader::Init()
{
	InitShaderProgram("../Data/Shaders/Entity/EntityGeometryPassShader.vert", "../Data/Shaders/Entity/EntityGeometryPassShader.frag");
	Start();
	GetAllUniformLocations();
	ConnectTextureUnits();
	//for (int x = 0; x < MAX_BONES; x++)
	//{
	//	glm::mat4 m(1.f);
	//	LoadBoneTransform(m, x);
	//}
	//glm::mat4 m(1.f);
	////m *= glm::translate(glm::vec3(0, -1, 0));
	//m *= glm::rotate(20.f, glm::vec3(0, 1, 0));
	//LoadBoneTransform(m, 9);
	Stop();
}

void CEntityGeometryPassShader::LoadViewDistance(const float & distance) const
{
	LoadValue(location_ViewDistance, distance);
}

void CEntityGeometryPassShader::LoadUseFakeLight(const float & use) const
{
	LoadValue(location_UseFakeLighting, use);
}

void CEntityGeometryPassShader::LoadUseNormalMap(const float & use) const
{
	LoadValue(location_UseNormalMap, use);
}

void CEntityGeometryPassShader::LoadMeshMaterial(const SMaterial & material) const
{
	LoadValue(location_MaterialAmbient, material.ambient);
	LoadValue(location_MaterialDiffuse, material.diffuse);
	LoadValue(location_MaterialSpecular, material.specular);
}

void CEntityGeometryPassShader::LoadToShadowSpaceMatrix(const glm::mat4 & matrix) const
{
	LoadValue(location_ToShadowMapSpace, matrix);
}

void CEntityGeometryPassShader::LoadShadowValues(const float & is, const float & distance, const float & shadow_map_size) const
{
	LoadValue(location_ShadowVariables, glm::vec3(is, distance - 5, shadow_map_size));
}

void CEntityGeometryPassShader::LoadClipPlane(const glm::vec4 clip_plane) const
{
	LoadValue(location_ClipPlane, clip_plane);
}

void CEntityGeometryPassShader::LoadUseTexture(const float & is) const
{
	LoadValue(location_UseTexture, is);
}