#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>


glm::mat4 Camera::getViewTransform()
{
    return glm::lookAt(position, position + getDirection(), up);
}

glm::mat4 Camera::getProjectionTransform(float aspectRatio)
{
    return glm::perspective(glm::radians(60.f), aspectRatio,0.1f ,100.f );
}

glm::vec3 Camera::getDirection()
{
    auto rotateX = glm::rotate(glm::radians(pitch), glm::vec3{ 1.f,0.f,0.f });
    auto rotateY = glm::rotate(glm::radians(yaw), glm::vec3{ 0.f ,1.f, 0.f });


    return rotateY * rotateX * glm::vec4{ 0.f,0.f, -1.f,0.f };
}
