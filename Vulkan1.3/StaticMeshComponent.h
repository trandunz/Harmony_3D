#pragma once
#ifndef _STATICMESHCOMPONENT_H
#define _STATICMESHCOMPONENT_H

#include "Transform.h"

class StaticMeshComponent
{
public:
	StaticMeshComponent() {};
	StaticMeshComponent(class StaticMesh* StaticMesh);

	void UpdateUniformBuffer(uint32_t currentImage);

	void Draw();

protected:
	Transform Transform{};
	class StaticMesh* AssignedStaticMesh{ nullptr };
};
#endif