#version 460 core

layout (location = 0) in vec3 pos;

out vec3 cubeMapTextureCoordinates;

uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	cubeMapTextureCoordinates = pos;
	gl_Position = (projectionTransform * viewTransform * vec4(pos,1.0)).xyww;
}