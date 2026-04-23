#version 460 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;

out vec2 uvs;

uniform mat4 model;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	gl_Position = projectionTransform * viewTransform * model * vec4(vertex.xyz, 1.0f);
	uvs = vertex.xy;
}