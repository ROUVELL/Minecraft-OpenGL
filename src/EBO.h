#pragma once

#include <vector>

class EBO
{
public:
	EBO(const std::vector<unsigned int>& indices);

	unsigned int GetID() const { return ID; }

	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	unsigned int ID{ 0 };
};

