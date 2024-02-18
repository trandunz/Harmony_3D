#include "Statics.h"
#include "Window.h"
#include "SceneManager.h"
#include "MeshManager.h"

void Draw();

int main() 
{
    Window& window = Statics::MainWindow->Get();
    window.Init();

    Statics::MeshManager->CreatePrimitives();

    Statics::SceneManager->LoadScene(SCENE::SCENE_DEMO);

    while (!glfwWindowShouldClose(window.GlfwWindow)) {
        Statics::SceneManager->ChangeToQueuedScene();
        glfwPollEvents();
        Statics::SceneManager->Start();
        Statics::SceneManager->Update();
        Draw();
    }

    return window.Cleanup();
}

void Draw()
{
    Statics::MainWindow->Draw();
}
