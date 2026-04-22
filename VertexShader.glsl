#version 460 core

in vec2 vertex;

uniform mat4 model;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	gl_Position = projectionTransform * viewTransform * model * vec4(vertex.xy, 0.0f, 1.0f);
}