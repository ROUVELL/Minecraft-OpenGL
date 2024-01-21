#pragma once

#include <vector>

#include "VAO.h"


class Mesh
{
public:
	Mesh() = default;
	Mesh(const std::vector<Vertex>& vert);

	void Build(const std::vector<Vertex>& vert);

	void Render() const;

private:
	VAO vao;

	int count{ 0 };
};
