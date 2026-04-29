#include "Texture.h"
#include "stb_image.h"

namespace
{
	struct Image
	{
		Image(const std::string& path)
		{
			int chanelsInFile;
			buffer = stbi_load(path.c_str(), &width, &height, &chanelsInFile, 4);
		}
		~Image()
		{
			stbi_image_free(buffer);
		}

		int width;
		int height;
		unsigned char* buffer;

	};
}


Texture::Texture(const std::string& path)
{
	Image image(path);

	if (image.buffer)
	{
		glBindTexture(GL_TEXTURE_2D, *m_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.buffer);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, *m_id);
}
