#include "CameraComponent.h"
#include "Window.h"

glm::mat4 CameraComponent::GetViewMatrix() const
{
	//return glm::lookAt(Position, Position + GetForwardVector(), GetUpVector());
    return glm::lookAt(Position, { 0,0,0 }, GetUpVector());
}

glm::mat4 CameraComponent::GetProjectionMatrix() const
{
    Window* MainWindow = Statics::MainWindow;

    return bPerspective
        ?
        glm::perspective(
            glm::radians(Fov),
            (float) MainWindow->VulkanSwapChainExtent.width /
            (float) MainWindow->VulkanSwapChainExtent.height,
            NearPlane,
            FarPlane)
        :
        glm::ortho(
            -(float)MainWindow->VulkanSwapChainExtent.width / 2,
            (float)MainWindow->VulkanSwapChainExtent.width / 2,
            -(float)MainWindow->VulkanSwapChainExtent.height / 2,
            (float)MainWindow->VulkanSwapChainExtent.height / 2,
            NearPlane,
            FarPlane);
}

void CameraComponent::UpdateTranslationFromKeyboard()
{
    glm::vec3 InputVector{};

    for (auto& Key : Statics::Keymap)
    {
        if (Key.second)
        {
            switch (Key.first)
            {
            case GLFW_KEY_W:
            {
                InputVector.y += 1;
                break;
            }
            case GLFW_KEY_A:
            {
                InputVector.x -= 1;
                break;
            }
            case GLFW_KEY_S:
            {
                InputVector.y -= 1;
                break;
            }
            case GLFW_KEY_D:
            {
                InputVector.x += 1;
                break;
            }
            default:
                break;
            }
        }
    }
}

void CameraComponent::UpdateRotationFromMouse()
{
}
