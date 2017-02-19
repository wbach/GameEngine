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
	void UpdateMatrix() { matrix = Utils::CreateTransformationMatrix(position, rotation, scale); }
	glm::vec2 GetPositionXZ() { return glm::vec2(position.x, position.z); }
	const glm::mat4& GetMatrix() const { return matrix; }
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 matrix;
};