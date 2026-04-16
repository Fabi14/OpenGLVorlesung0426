#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>


glm::mat4 Camera::getViewTransform()
{
    glm::vec3 up{ 0.f,1.f,0.f };
    return glm::lookAt(position, position + direction, up);
}

glm::mat4 Camera::getProjectionTransform()
{
    return glm::perspective(glm::radians(60.f), 640.f/480.f ,0.1f ,100.f );
}
