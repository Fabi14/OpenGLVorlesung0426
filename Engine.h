#pragma once
#include <functional>
struct GLFWwindow;


class Engine
{
public:
	~Engine();
	bool init();
	void run(const std::function<void(double)>& draw);
private:
	GLFWwindow* pWindow{nullptr};
	double m_time{};
};

