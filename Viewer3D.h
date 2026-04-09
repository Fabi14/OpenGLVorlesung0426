#pragma once
#include "Engine.h"
#include <glad/glad.h>

class Viewer3D
{
public:
	bool init();
	void run();
private:
	void draw();

	Engine m_engine;
	GLuint vertexArrayObject{ 0 };
	GLuint shaderProgram{ 0 };
};

