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
	void update(double deltaTime);
	void handleInput(double deltaTime);
	void createGui();


	Engine m_engine;
	std::optional<VertexBuffer> m_oVertexBuffer{ std::nullopt };
	std::optional<ShaderProgram> m_oShaderProgram{ std::nullopt };
	float m_angleForModelTransform = 0.f;

	std::optional<VertexBuffer> m_oVertexBufferCube{ std::nullopt };
	std::optional<ShaderProgram> m_oShaderProgramCube{ std::nullopt };

	Camera m_camera;

	glm::vec2 m_lastMousePos{  };

	bool m_bShowImguiWindow{ false };
	bool m_drawSquare{ true };
	bool m_drawSquare2{ true };
	glm::vec4 m_clearColor{ 0.f, 0.f, 0.5f, 1.f };
	float m_rotationSpeed{ 10.f };
};

