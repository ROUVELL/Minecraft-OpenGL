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

	vao.LinkAttr(Attribute{ 0, 3, GL_UNSIGNED_BYTE, 0 });
	vao.LinkAttr(Attribute{ 1, 1, GL_UNSIGNED_BYTE, (void*)(3 * sizeof(char)) });
	vao.LinkAttr(Attribute{ 2, 1, GL_UNSIGNED_BYTE, (void*)(3 * sizeof(char) + sizeof(char)) });

	vao.Unbind();
	vbo.Delete();
}

void Mesh::Render() const
{
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, count);
	vao.Unbind();
}
