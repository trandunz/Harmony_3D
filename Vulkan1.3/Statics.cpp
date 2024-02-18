#include "Statics.h"
#include "Window.h"
#include "SceneManager.h"
#include "MeshManager.h"
#include "CameraComponent.h"

Window* Statics::MainWindow{ &Window::Get() };
SceneManager* Statics::SceneManager{ &SceneManager::Get() };
MeshManager* Statics::MeshManager{ &MeshManager::Get() };
CameraComponent* Statics::ActiveCamera{ nullptr };
KEYMAP Statics::Keymap{};
float Statics::DeltaTime{};
double Statics::LastTime{};

void Statics::UpdateDeltaTime()
{
	double CurrentTime = glfwGetTime();
	DeltaTime = CurrentTime - LastTime;
	LastTime = CurrentTime;
}
