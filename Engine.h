#pragma once
#include <functional>
#include <glm/glm.hpp>
struct GLFWwindow;


class Engine
{
public:
	~Engine();
	bool init();
	void run(const std::function<void(double)>& draw);
	bool getKey(int glfw_Key);

	glm::vec2 getMousePos();
	bool getMouseButton(int button);

	float getWindowAspectRatio();
private:
	GLFWwindow* pWindow{nullptr};
	double m_time{};
};

