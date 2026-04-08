#pragma once
struct GLFWwindow;

class Engine
{
public:
	~Engine();
	bool init();
	void run();
private:
	GLFWwindow* pWindow{nullptr};
};

