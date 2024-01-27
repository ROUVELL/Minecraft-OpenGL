#include "EBO.h"

#include <glad/glad.h>


EBO::EBO(const std::vector<unsigned int>& indices)
{
	Create(indices);
}

void EBO::Create(const std::vector<unsigned int>& indices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() const
{
	Unbind();
	glDeleteBuffers(1, &ID);
}
