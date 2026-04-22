#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	glm::mat4 getViewTransform();
	glm::mat4 getProjectionTransform();
	glm::vec3 getDirection();

	glm::vec3 position{0.f,0.f,0.f};
	//glm::vec3 direction{ 0.f,0.f,-1.f };
	glm::vec3 up{ 0.f,1.f,0.f };

	float yaw{};
	float pitch{};
};

