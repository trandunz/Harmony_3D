#pragma once
#ifndef _TRANSFORM_COMPONENT_H
#define _TRANSFORM_COMPONENT_H

#include "Statics.h"

class TransformComponent
{
public:
	glm::mat4 GetTransformMatrix() const;

	glm::vec3 GetRightVector() const;
	glm::vec3 GetUpVector() const;
	glm::vec3 GetForwardVector() const;

	glm::vec3 Position{0,0,0};
	glm::vec3 Rotation{0,0,0};
	glm::vec3 Scale{1,1,1};
};

#endif