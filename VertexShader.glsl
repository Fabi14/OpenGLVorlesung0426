#version 460 core

in vec2 vertex;

void main()
{
	gl_Position = vec4(vertex.x,vertex.y, 0.0f, 1.0f);
}