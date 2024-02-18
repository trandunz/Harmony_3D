#pragma once
#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

enum class SCENE
{
	UNASSIGNED = 0,

	SCENE_DEMO
};

class SceneManager
{
public:
	inline static SceneManager& Get() {
		static SceneManager Instance;
		return Instance;
	}
	~SceneManager();

	void Cleanup();

	void Start();
	void Update();
	void Draw();

	void LoadScene(SCENE Scene);
	void ChangeToQueuedScene();

protected:
	class Scene* CurrentScene{ nullptr };
	SCENE SceneToLoad{ SCENE::UNASSIGNED };
	bool bSceneInitialized{false};

private:
	SceneManager() {};
	SceneManager& operator=(const  SceneManager&) = delete;
	SceneManager(const  SceneManager&) = delete;
};
#endif

