#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	glm::mat4 getViewTransform();
	glm::mat4 getProjectionTransform();
};

