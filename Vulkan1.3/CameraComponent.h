#pragma once
#ifndef _CAMERA_COMPONENT_H
#define _CAMERA_COMPONENT_H

#include "TransformComponent.h"

class CameraComponent : public TransformComponent
{
public:
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    void UpdateTranslationFromKeyboard();
    void UpdateRotationFromMouse();

protected:
    bool bPerspective{ true };
    float NearPlane = 0.1f;
    float FarPlane = 2000.0f;
    float Fov = 45.0f;
};
#endif

