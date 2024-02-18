#pragma once
#ifndef _MESHMANAGER_H
#define _MESHMANAGER_H
#include "Statics.h"

class MeshManager
{
public:
	inline static MeshManager& Get() {
		static MeshManager Instance;
		return Instance;
	}
	int Cleanup();

	void CreatePrimitives();

	std::vector<class StaticMesh*> StaticMeshes{};

private:
	MeshManager() {};
	MeshManager& operator=(const  MeshManager&) = delete;
	MeshManager(const  MeshManager&) = delete;
};
#endif
