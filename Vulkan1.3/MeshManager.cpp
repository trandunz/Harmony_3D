#include "MeshManager.h"
#include "StaticMesh.h"

int MeshManager::Cleanup()
{
	for (auto& StaticMesh : StaticMeshes)
	{
		if (IsValid(StaticMesh))
		{
			delete StaticMesh;
			StaticMesh = nullptr;
		}
	}
	StaticMeshes.clear();

	return 0;
}

void MeshManager::CreatePrimitives()
{
	StaticMeshes.push_back(new StaticMesh());
}
