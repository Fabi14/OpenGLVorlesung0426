#pragma once
#include "Engine.h"
#include <glad/glad.h>
#include <optional>
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "Camera.h"

class Viewer3D
{
public:
	bool init();
	void run();
private:
	void draw();

	Engine m_engine;
	std::optional<VertexBuffer> m_oVertexBuffer{ std::nullopt };
	std::optional<ShaderProgram> m_oShaderProgram{ std::nullopt };
	float angle = 0.f;

	Camera m_camera;
};

