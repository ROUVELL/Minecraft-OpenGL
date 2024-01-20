#pragma once

#include <vector>

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 uv;
};

class VBO
{
public:
	VBO(const std::vector<Vertex>& vertices);

	unsigned int GetID() const { return ID; }

	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	unsigned int ID{ 0 };
};