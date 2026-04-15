#pragma once
class Shader;

class DebugOutput
{
public:
	static void enable();

	static void checkShaderCompilation(const Shader& shader);
};

