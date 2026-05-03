#include "Texture.h"
#include "Image.h"
#include "ShaderProgram.h"

Texture::Texture(const std::string& path)
{
	Image image(path);

	if (image.buffer)
	{
		glBindTexture(GL_TEXTURE_2D, *m_id);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Texture::bind(const ShaderProgram& shaderProgram, const std::string& uniformName, int textureUnit)
{
	auto uniformID = glGetUniformLocation(shaderProgram.get(), uniformName.c_str());
	glUniform1i(uniformID, textureUnit);

	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, *m_id);
}
