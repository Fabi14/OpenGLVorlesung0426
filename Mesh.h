#pragma once

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

using Index = unsigned int;

struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<Index> indices;


	static Mesh getQuad()
	{
		std::vector<Vertex> vertices{
			{glm::vec3{ -0.5f,-0.5f, 0.f }, glm::vec3{ 0.f ,0.f,1.f}},
			{glm::vec3{ 0.5f, 0.5f , 0.f}, glm::vec3{ 0.f ,0.f,1.f}},
			{glm::vec3{ 0.5f, -0.5f, 0.f}, glm::vec3{ 0.f ,0.f,1.f}},
			{glm::vec3{ -0.5f,0.5f , 0.f}, glm::vec3{ 0.f ,0.f,1.f}},
		};

		std::vector<Index> indices{ 0, 1, 2, 0, 3, 1 };

		return Mesh{ .vertices = vertices, .indices = indices };
	}

	static Mesh getCube()
	{
		//TODO
		return {};
	}
};

