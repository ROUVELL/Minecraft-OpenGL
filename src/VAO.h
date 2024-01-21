#pragma once

#include "VBO.h"
#include "EBO.h"

class VAO
{
public:
	VAO() = default;

	void Create();

	void LinkFloatAttr(unsigned int attr, unsigned int numComponents);
	void LinkByteAttr(unsigned int attr, unsigned int numComponents);

	void LinkVBO(VBO vbo) const;
	void LinkEBO(EBO ebo) const;

	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	unsigned int ID{ 0 };
	unsigned int offset{ 0 };
};

