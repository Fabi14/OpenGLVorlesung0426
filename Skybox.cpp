#include "Skybox.h"
#include "Mesh.h"
#include "Image.h"
#include <array>
#include <string>
#include <ranges>
#include "Shader.h"

namespace
{
	const std::array<std::string, 6> c_skyboxImageNames{
		"Models\\Skybox\\right.jpg",
		"Models\\Skybox\\left.jpg",
		"Models\\Skybox\\top.jpg",
		"Models\\Skybox\\bottom.jpg",
		"Models\\Skybox\\front.jpg",
		"Models\\Skybox\\back.jpg",
	};
}

Skybox::Skybox()
{
	// 3D model cube laden (Vertices)
	Mesh cube = Mesh::getCube();
	m_oVertexBuffer = VertexBuffer(cube.vertices, cube.indices);

	// Bilder für cubemap (Texturen)
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *m_texId);
	for (const auto& [i, fileName] : std::views::enumerate(c_skyboxImageNames))
	{
		Image image(fileName, false);

		if (image.buffer)
		{
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.buffer);
		}
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// Shader für Skybox
	m_shaderProgram = ShaderProgram(Shader("SkyboxVertexShader.glsl", GL_VERTEX_SHADER)
		, Shader("SkyboxFragmentShader.glsl", GL_FRAGMENT_SHADER));

}

void Skybox::draw(const Camera& camera, float windowAspectRatio)
{
	// shader aktiviern
	if (!m_shaderProgram)
	{
		return;
	}
	m_shaderProgram->bind();
	// Camera immer inerhalb des Cubes
	glm::mat4 view = glm::mat3(camera.getViewTransform());
	m_shaderProgram->setCameraTransform(
		view,
		camera.getProjectionTransform(windowAspectRatio),
		camera.position);
	// cubemap texture aktivieren
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *m_texId);
	GLint oldFaceCallMode;
	glGetIntegerv(GL_CULL_FACE_MODE, &oldFaceCallMode);

	GLint oldDepthMode{};
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthMode);

	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);

	// innenflächen des Würfels zeichnen
	m_oVertexBuffer->bind();
	glDrawElements(GL_TRIANGLES, m_oVertexBuffer->getIndexCount(), GL_UNSIGNED_INT, 0);

	glCullFace(oldFaceCallMode);
	glDepthFunc(oldDepthMode);
}
