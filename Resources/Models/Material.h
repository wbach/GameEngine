#pragma once
#include <string>
#include "glm/glm.hpp"
#include <vector>
#include "../Textures/Texture.h"

struct SMaterial
{
	glm::vec3 ambient  = glm::vec3(0);
	glm::vec3 diffuse  = glm::vec3(0.8);
	glm::vec3 specular = glm::vec3(0);

	float shineDamper  = 0.f;
	float reflectivity = 0.f;

	bool isTransparency  = false;
	bool useFakeLighting = false;

	int m_DiffuseTexture = -1;
	int m_AmbientTexture = -1;
	int m_SpecularTexture = -1;
	int m_NormalTexture = -1;

	int numberOfRows = 1;
	int textureIndex = 0;

	float getTextureXOffset() 
	{
		int column = textureIndex%numberOfRows;
		return (float)column / (float)numberOfRows;
	}
	float getTextureYOffset()
	{
		int row = textureIndex / numberOfRows;
		return (float)row / (float)numberOfRows;
	}
};
