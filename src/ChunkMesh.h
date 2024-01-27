#pragma once

#include <vector>

class ChunkMesh
{
public:
	ChunkMesh() = default;

	void Build(const std::vector<unsigned int>& vertexData);

	void Render() const;

private:
	unsigned int vao{ 0 };
	int count{ 0 };
};

