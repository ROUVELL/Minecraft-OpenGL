#include "VBO.h"

#include <glad/glad.h>

VBO::VBO(const std::vector<Vertex>& vertices)
{
	glCreateBuffers(1, &ID);
	glNamedBufferData(ID, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() const
{
	Unbind();
	glDeleteBuffers(1, &ID);
}
