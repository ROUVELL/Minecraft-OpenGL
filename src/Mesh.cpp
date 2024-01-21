#include "Mesh.h"

#include "glad/glad.h"

Mesh::Mesh(const std::vector<Vertex>& vert)
{
	Build(vert);
}

void Mesh::Build(const std::vector<Vertex>& vert)
{
	count = static_cast<int>(vert.size());

	vao.Create();

	VBO vbo{ vert };

	vao.LinkFloatAttr(0, 3);
	vao.LinkByteAttr(1, 1);
	vao.LinkByteAttr(2, 1);

	vao.LinkVBO(vbo);

	vbo.Delete();
}

void Mesh::Render() const
{
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, count);
	vao.Unbind();
}
