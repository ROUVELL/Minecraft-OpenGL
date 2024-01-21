#pragma once

#include <vector>

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::uint8 voxelId;
	glm::uint8 faceId;

	Vertex(glm::vec3 p, glm::uint8 vId, glm::uint8 fId)
		: position(p), voxelId(vId), faceId(fId)
	{ }
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