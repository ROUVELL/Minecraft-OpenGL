#include "VAO.h"

#include <glad/glad.h>

void VAO::Create()
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

void VAO::LinkAttr(const Attribute& attr)
{
	glVertexAttribPointer(attr.layout, attr.components, attr.type, GL_FALSE, static_cast<GLsizei>(sizeof(Vertex)), attr.offset);
	glEnableVertexAttribArray(attr.layout);
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
