#include "TransformComponent.h"

glm::mat4 TransformComponent::GetTransformMatrix() const
{
    glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1), Position);

    glm::mat4 ScaleMatrix = glm::scale(glm::mat4(1), Scale);

    glm::mat4 RotationMatrix = glm::mat4(1);
    glm::mat4 rotXmatrix = glm::rotate(glm::mat4(1), glm::radians(Rotation.x), glm::vec3(1.0f, 0.0, 0.0));
    glm::mat4 rotYmatrix = glm::rotate(glm::mat4(1), glm::radians(Rotation.y), glm::vec3(0.0, 1.0f, 0.0));
    glm::mat4 rotZmatrix = glm::rotate(glm::mat4(1), glm::radians(Rotation.z), glm::vec3(0.0, 0.0, 1.0f));
    RotationMatrix = rotZmatrix * rotYmatrix * rotXmatrix;

    return TranslationMatrix * ScaleMatrix * RotationMatrix;
}

glm::vec3 TransformComponent::GetRightVector() const
{
    return glm::normalize(glm::cross(GetForwardVector(), { 0,0,1 }));
}

glm::vec3 TransformComponent::GetUpVector() const
{
    return glm::normalize(glm::cross(GetRightVector(), GetForwardVector()));
}

glm::vec3 TransformComponent::GetForwardVector() const
{
    return glm::normalize(glm::vec3{
        cos(glm::radians(Rotation.x)) * cos(glm::radians(Rotation.z)),
        sin(glm::radians(Rotation.x)),
        cos(glm::radians(Rotation.x)) * sin(glm::radians(Rotation.z))
        });
}
