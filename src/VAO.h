#pragma once

#include "VBO.h"

struct Attribute
{
	using uInt = unsigned int;

	uInt layout;
	uInt components;  // 1, 2, 3, or 4
	uInt type;        // GL_FLOAT, GL_INT etc.
	void* offset;
};

class VAO
{

public:
	VAO() = default;

	void Create();

	void LinkAttr(const Attribute& attr);

	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	unsigned int ID{ 0 };
};

