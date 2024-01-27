#pragma once

#include <vector>

#include <glm/glm.hpp>

struct Vertex
{
	glm::i8vec3 position;
	glm::uint8 voxelId;
	glm::uint8 faceId;

	Vertex(glm::i8vec3 p, glm::uint8 vId, glm::uint8 fId)
		: position(p), voxelId(vId), faceId(fId)
	{ }
};

class VBO
{
public:
	VBO() = default;
	VBO(const std::vector<Vertex>& vertices);

	unsigned int GetID() const { return ID; }

	void Create(const std::vector<Vertex>& vertices);
	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	unsigned int ID{ 0 };
};