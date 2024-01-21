#include "VAO.h"

#include <glad/glad.h>

void VAO::Create()
{
	glCreateVertexArrays(1, &ID);
}

void VAO::LinkFloatAttr(unsigned int attr, unsigned int numComponents)
{
	glEnableVertexArrayAttrib(ID, attr);
	glVertexArrayAttribBinding(ID, attr, 0);
	glVertexArrayAttribFormat(ID, attr, numComponents, GL_FLOAT, GL_FALSE, offset);
	offset += numComponents * sizeof(GLfloat);
}

void VAO::LinkByteAttr(unsigned int attr, unsigned int numComponents)
{
	glEnableVertexArrayAttrib(ID, attr);
	glVertexArrayAttribBinding(ID, attr, 0);
	glVertexArrayAttribFormat(ID, attr, numComponents, GL_UNSIGNED_BYTE, GL_FALSE, offset);
	offset += numComponents * sizeof(GLbyte);
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
