#include "Statics.h"
#include "Window.h"

void Draw();

int main() 
{
    Window& window = Statics::MainWindow->Get();
    window.Init();

    while (!glfwWindowShouldClose(window.GlfwWindow)) {
        glfwPollEvents();
        Draw();
    }

    return window.Cleanup();
}

void Draw()
{
    Statics::MainWindow->Draw();
}
