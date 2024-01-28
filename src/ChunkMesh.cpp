#include "ChunkMesh.h"

#include <iostream>
#include "glad/glad.h"

void ChunkMesh::Build(const std::vector<unsigned int>& vertexData)
{
	count = static_cast<int>(vertexData.size());

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(unsigned int), vertexData.data(), GL_STATIC_DRAW);

	/*
	 For glVertexAttribIPointer, only the integer types GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT are accepted.
	 Values are always left as integer values.

	 https://docs.gl/gl3/glVertexAttribPointer
	*/

	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(unsigned int), 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glDeleteBuffers(0, &vbo);

}

void ChunkMesh::Rebuild(const std::vector<unsigned int>& vertexData)
{
	if (vertexData.size() != count)
	{
		Build(vertexData);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexData.size() * sizeof(unsigned int), vertexData.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

void ChunkMesh::Render() const
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, count);
	glBindVertexArray(0);
}
