#pragma once
#include "../../../Shaders/ShaderProgram.h"
#include "glm/gtc/matrix_transform.hpp"

class CTerrainShader : public CShaderProgram
{
public:
	virtual void Init();
	void GetAllUniformLocations();
	void BindAttributes() override;
	void ConnectTextureUnits();
	void LoadTransformMatrix(const glm::mat4& matrix) const;
	void LoadProjectionMatrix(const glm::mat4& matrix) const;
	void LoadViewMatrix(const glm::mat4& matrix) const;
	void LoadCameraPosition(const glm::vec3& position) const;
	void LoadDispFactor(float factor) const;
	void LoadViewDistance(float distance) const;
protected:
	int location_TransformationMatrix;
	int location_ProjectionMatrix;
	int location_ViewMatrix;

	int location_CameraPosition;
	int location_DispFactor;
	int location_ViewDistance;
	
	//Samplers2d location
	int location_blendMap;
	int location_backgroundTexture;
	int location_rTexture;
	int location_bTexture;
	int location_gTexture;
	int location_RockTexture;

	int location_backgroundTextureNormal;
	int location_rTextureNormal;
	int location_bTextureNormal;
	int location_gTextureNormal;
	int location_RockTextureNormal;
	int location_DisplacementMap;
};
