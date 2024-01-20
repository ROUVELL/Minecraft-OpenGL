#include "VAO.h"

#include <glad/glad.h>

VAO::VAO()
{
	glCreateVertexArrays(1, &ID);
}

void VAO::LinkAttrib(unsigned int attr, unsigned int numComponents,
	int stride, void* offset) const
{
	glEnableVertexAttribArray(attr);
	glVertexAttribPointer(attr, numComponents, GL_FLOAT, GL_FALSE, stride, offset);
}

void VAO::LinkAttrib(unsigned int attr, unsigned int numComponents, unsigned int offset) const
{
	glEnableVertexArrayAttrib(ID, attr);
	glVertexArrayAttribBinding(ID, attr, 0);
	glVertexArrayAttribFormat(ID, attr, numComponents, GL_FLOAT, GL_FALSE, offset * sizeof(GLfloat));
}

void VAO::LinkVBO(VBO vbo) const
{
	glVertexArrayVertexBuffer(ID, 0, vbo.GetID(), 0, sizeof(Vertex));
}

void VAO::LinkEBO(EBO ebo) const
{
	glVertexArrayElementBuffer(ID, ebo.GetID());
}


void VAO::Bind() const
{
	glBindVertexArray(ID);
}

void VAO::Unbind() const
{
	glBindVertexArray(0);
}

void VAO::Delete() const
{
	glDeleteVertexArrays(1, &ID);
}
