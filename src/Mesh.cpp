#include "Mesh.h"

#include "glad/glad.h"

Mesh::Mesh()
{
}

Mesh::Mesh(const std::vector<Vertex>& vert, const std::vector<unsigned int>& ind)
{
	Build(vert, ind);
}

void Mesh::Build(const std::vector<Vertex>& vert, const std::vector<unsigned int>& ind)
{
	elements = static_cast<int>(ind.size());

	VBO vbo{ vert };
	EBO ebo{ ind };

	vao.LinkAttrib(0, 3, 0);
	vao.LinkAttrib(1, 2, 3);

	vao.LinkVBO(vbo);
	vao.LinkEBO(ebo);

	vbo.Delete();
	ebo.Delete();
}

void Mesh::Render() const
{
	vao.Bind();
	glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}
