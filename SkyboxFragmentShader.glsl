#version 460 core

in vec3 cubeMapTextureCoordinates;

out vec4 fragColor;

uniform samplerCube cubemapTexture;

void main()
{
	fragColor = texture(cubemapTexture,cubeMapTextureCoordinates);
}