#include "SceneManager.h"
#include "Statics.h"
#include "Scene_Demo.h"

SceneManager::~SceneManager()
{
	Cleanup();
}

void SceneManager::Cleanup()
{
	if (IsValid(CurrentScene))
	{
		delete CurrentScene;
		CurrentScene = nullptr;
	}
}

void SceneManager::Start()
{
	if (IsValid(CurrentScene) && bSceneInitialized == false)
	{
		bSceneInitialized = true;
		CurrentScene->Start();
	}
}

void SceneManager::Update()
{
	if (IsValid(CurrentScene))
	{
		CurrentScene->Update();
	}
}

void SceneManager::Draw()
{
	if (IsValid(CurrentScene))
	{
		CurrentScene->Draw();
	}
}

void SceneManager::LoadScene(SCENE Scene)
{
	SceneToLoad = Scene;
}

void SceneManager::ChangeToQueuedScene()
{
	if (SceneToLoad == SCENE::UNASSIGNED)
		return;

	if (IsValid(CurrentScene))
	{
		delete CurrentScene;
		CurrentScene = nullptr;
	}

	bSceneInitialized = false;
	
	switch (SceneToLoad)
	{
	case SCENE::SCENE_DEMO:
	{
		CurrentScene = new Scene_Demo();
		break;
	}
	}

	SceneToLoad = SCENE::UNASSIGNED;
}
