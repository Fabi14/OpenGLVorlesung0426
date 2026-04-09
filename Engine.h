#pragma once
#include <functional>
struct GLFWwindow;


class Engine
{
public:
	~Engine();
	bool init();
	void run(const std::function<void()>& draw);
private:
	GLFWwindow* pWindow{nullptr};
};

