#pragma once

#include "VBO.h"
#include "EBO.h"

class VAO
{
public:
	VAO();

	void LinkAttrib(unsigned int attr, unsigned int numComponents,
		int stride, void* offset) const;
	void LinkAttrib(unsigned int attr, unsigned int numComponents, unsigned int offset) const;
	void LinkVBO(VBO vbo) const;
	void LinkEBO(EBO ebo) const;

	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	unsigned int ID{ 0 };
};

