#pragma once
#ifndef _STATICMESH_COMPONENT_H
#define _STATICMESH_COMPONENT_H

#include "TransformComponent.h"

class StaticMeshComponent : public TransformComponent
{
public:
	StaticMeshComponent() {};
	StaticMeshComponent(class StaticMesh* StaticMesh);

	void UpdateUniformBuffer(uint32_t currentImage);

	void Draw();

protected:
	class StaticMesh* AssignedStaticMesh{ nullptr };
};
#endif