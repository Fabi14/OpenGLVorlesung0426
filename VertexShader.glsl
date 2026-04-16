#version 460 core

in vec2 vertex;

uniform mat4 model;

void main()
{
	gl_Position = model * vec4(vertex.x,vertex.y, 0.0f, 1.0f);
}