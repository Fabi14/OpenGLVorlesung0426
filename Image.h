#pragma once
#include <string>

struct Image
{
	Image(const std::string& path, bool flip = true);
	~Image();

	int width;
	int height;
	unsigned char* buffer;

};

