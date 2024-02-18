#include "Statics.h"
#include "Window.h"
#include "SceneManager.h"
#include "MeshManager.h"

Window* Statics::MainWindow{ &Window::Get() };
SceneManager* Statics::SceneManager{ &SceneManager::Get() };
MeshManager* Statics::MeshManager{ &MeshManager::Get() };