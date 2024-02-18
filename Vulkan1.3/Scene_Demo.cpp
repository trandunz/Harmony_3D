#include "Scene_Demo.h"
#include "StaticMeshComponent.h"
#include "MeshManager.h"
#include "StaticMesh.h"

Scene_Demo::~Scene_Demo()
{
	delete DemoStaticMeshComponent;
	DemoStaticMeshComponent = nullptr;
}

void Scene_Demo::Start()
{
	DemoStaticMeshComponent = new StaticMeshComponent(Statics::MeshManager->StaticMeshes[0]);
}

void Scene_Demo::Update()
{

}

void Scene_Demo::Draw()
{
	DemoStaticMeshComponent->Draw();
}
