#pragma once
#include "Engine.h"
#include <glad/glad.h>
#include <optional>
#include "ShaderProgram.h"

class Viewer3D
{
public:
	bool init();
	void run();
private:
	void draw();

	Engine m_engine;
	GLuint vertexArrayObject{ 0 };
	std::optional<ShaderProgram> m_oShaderProgram{std::nullopt};
};

