#pragma once

#include <vector>

#include "VAO.h"


class Mesh
{
public:
	Mesh();
	Mesh(const std::vector<Vertex>& vert, const std::vector<unsigned int>& ind);

	void Build(const std::vector<Vertex>& vert,
		const std::vector<unsigned int>& ind);

	void Render() const;

private:
	VAO vao;

	int elements{ 0 };
};
