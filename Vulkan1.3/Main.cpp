#include "Statics.h"
#include "Window.h"
#include "SceneManager.h"
#include "MeshManager.h"
#include "CameraComponent.h"

void Draw();

int main() 
{
    Window& window = Statics::MainWindow->Get();
    window.Init();

    CameraComponent SceneCamera{};
    SceneCamera.Position = { 0.0f, 2.0f, 2.0f };
    Statics::ActiveCamera = &SceneCamera;

    Statics::MeshManager->CreatePrimitives();

    Statics::SceneManager->LoadScene(SCENE::SCENE_DEMO);

    while (!glfwWindowShouldClose(window.GlfwWindow)) {
        Statics::SceneManager->ChangeToQueuedScene();
        glfwPollEvents();
        Statics::SceneManager->Start();
        Statics::SceneManager->Update();
        Draw();
        Statics::UpdateDeltaTime();
    }

    return window.Cleanup();
}

void Draw()
{
    Statics::MainWindow->Draw();
}
