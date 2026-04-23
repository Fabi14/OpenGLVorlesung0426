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
	bool getKey(int glfw_Key) const;

	glm::vec2 getMousePos() const;
	bool getMouseButton(int button) const;

	float getWindowAspectRatio() const;
	glm::vec2 getWindowSize() const;

private:
	GLFWwindow* m_pWindow{nullptr};
	double m_time{};
};

