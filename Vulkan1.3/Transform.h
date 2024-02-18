#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Statics.h"

struct Transform
{
public:
	glm::vec3 Position{0,0,0};
	glm::vec3 Rotation{0,0,0};
	glm::vec3 Scale{1,1,1};
};

#endif