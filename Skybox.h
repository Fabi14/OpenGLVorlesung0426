#pragma once
#include <optional>
#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include "Camera.h"

class Skybox
{
public:
	Skybox();
	void draw(const Camera& camera, float windowAspectRatio);

private:
	std::optional<VertexBuffer> m_oVertexBuffer;
	std::optional<ShaderProgram> m_shaderProgram;

	UniqueResource m_texId{
		[] {GLuint id; glGenTextures(1,&id); return id; }(),
		[](GLuint id) {glDeleteTextures(1,&id); }
	};
};

