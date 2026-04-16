#include "Camera.h"

glm::mat4 Camera::getViewTransform()
{
    return glm::mat4(1);
}

glm::mat4 Camera::getProjectionTransform()
{
    return glm::mat4(1);
}
