#include "Image.h"
#include "stb_image.h"

Image::Image(const std::string& path, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	int chanelsInFile;
	buffer = stbi_load(path.c_str(), &width, &height, &chanelsInFile, 4);
}

Image::~Image()
{
	stbi_image_free(buffer);
}
