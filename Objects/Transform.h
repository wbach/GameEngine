#pragma once
#include "glm/glm.hpp"
#include "../Utils/Utils.h"

struct CTransform
{
public:
	CTransform() :CTransform(glm::vec3(0)) {}
	CTransform(const glm::vec2& pos) : CTransform(glm::vec3(pos.x, 0, pos.y)) {}
	CTransform(const glm::vec3& pos) : CTransform(pos, glm::vec3(0)) {}
	CTransform(const glm::vec3& pos, const glm::vec3& rot) : CTransform(pos, rot, glm::vec3(1)) {}
	CTransform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) : position(pos), rotation(rot), scale(scale), matrix(Utils::CreateTransformationMatrix(pos, rot, scale)) {}	
	
	void IncrasePosition(float dx, float dy, float dz, unsigned int index = 0)
	{
		IncrasePosition(glm::vec3(dx, dy, dz));
	}
	void IncrasePosition(glm::vec3 v, unsigned int index = 0)
	{
		position += v;
		UpdateMatrix();
	}
	void IncreaseRotation(float dx, float dy, float dz)
	{
		rotation += glm::vec3(dx, dy, dz);
		UpdateMatrix();
	}
	void UpdateMatrix() { matrix = Utils::CreateTransformationMatrix(position, rotation, scale * normalized); }
	
	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetRotation() const { return rotation; }
	glm::vec2 GetPositionXZ() const { return glm::vec2(position.x, position.z); }
	const glm::mat4& GetMatrix() const { return matrix; }

	void SetNormalizedSize(const glm::vec3& size)
	{ 
		normalized = size;  
		UpdateMatrix(); 
	}
	void SetPosition(const glm::vec3& pos) { position = pos;  UpdateMatrix(); }
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 matrix;
	glm::vec3 normalized = glm::vec3(1.f);
};