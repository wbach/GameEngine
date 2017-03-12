#include "TerrainShader.h"

void CTerrainShader::Init()
{	
	CreateProgram();
	AddShader("../Shaders/Terrain/TerrainShader.vert", GL_VERTEX_SHADER);
	AddShader("../Shaders/Terrain/TerrainShader.frag", GL_FRAGMENT_SHADER);
	AddShader("../Shaders/Terrain/TerrainShader.cs", GL_TESS_CONTROL_SHADER);
    AddShader("../Shaders/Terrain/TerrainShader.es", GL_TESS_EVALUATION_SHADER);
	FinalizeShader();
	
	Start();
	GetAllUniformLocations();
    ConnectTextureUnits();
	Stop();
}

void CTerrainShader::GetAllUniformLocations()
{
	location_TransformationMatrix = GetUniformLocation("TransformationMatrix");
	location_ProjectionMatrix = GetUniformLocation("ProjectionMatrix");
	location_ViewMatrix = GetUniformLocation("ViewMatrix");


	location_CameraPosition = GetUniformLocation("cameraPosition");
	location_DispFactor = GetUniformLocation("gDispFactor");
	location_ViewDistance = GetUniformLocation("ViewDistance");

	//Get location of samplers 2d
	location_blendMap = GetUniformLocation("BlendMap");

	location_backgroundTexture = GetUniformLocation("BackgroundTexture");
	location_rTexture = GetUniformLocation("rTexture");
	location_bTexture = GetUniformLocation("bTexture");
	location_gTexture = GetUniformLocation("gTexture");

	location_backgroundTextureNormal = GetUniformLocation("BackgroundTextureNormal");
	location_rTextureNormal = GetUniformLocation("rTextureNormal");
	location_bTextureNormal = GetUniformLocation("bTextureNormal");
	location_gTextureNormal = GetUniformLocation("gTextureNormal");

	location_RockTexture = GetUniformLocation("RockTexture");
	location_RockTextureNormal = GetUniformLocation("RockTextureNormal");
	location_DisplacementMap = GetUniformLocation("gDisplacementMap");
}

void CTerrainShader::BindAttributes()
{
	BindAttribute(0, "Position");
	BindAttribute(1, "TexCoord");
	BindAttribute(2, "Normal");
}

void CTerrainShader::ConnectTextureUnits()
{
    LoadValue(location_backgroundTexture, 0);
    LoadValue(location_rTexture, 1);
    LoadValue(location_gTexture, 2);
    LoadValue(location_bTexture, 3);
    LoadValue(location_blendMap, 4);
    LoadValue(location_backgroundTextureNormal, 5);
    LoadValue(location_rTextureNormal, 6);
    LoadValue(location_gTextureNormal, 7);
    LoadValue(location_bTextureNormal, 8);
    LoadValue(location_RockTexture, 9);
    LoadValue(location_RockTextureNormal, 10);
    LoadValue(location_DisplacementMap, 11);
}

void CTerrainShader::LoadTransformMatrix(const glm::mat4 & matrix) const
{
	LoadValue(location_TransformationMatrix, matrix);
}

void CTerrainShader::LoadProjectionMatrix(const glm::mat4 & matrix) const
{
	LoadValue(location_ProjectionMatrix, matrix);
}

void CTerrainShader::LoadViewMatrix(const glm::mat4 & matrix) const
{
	LoadValue(location_ViewMatrix, matrix);
}

void CTerrainShader::LoadCameraPosition(const glm::vec3 & position) const
{
	LoadValue(location_CameraPosition, position);
}

void CTerrainShader::LoadDispFactor(float factor) const
{
	LoadValue(location_DispFactor, factor);
}

void CTerrainShader::LoadViewDistance(float distance) const
{
	LoadValue(location_ViewDistance, distance);
}
