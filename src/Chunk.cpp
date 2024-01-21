#include "Chunk.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "World.h"
#include "Shader.h"

Chunk::Chunk(int x, int y, int z, World& world)
	: position(x, y, z), world(world)
{
	model = glm::translate(glm::mat4(1.0f), glm::vec3(position * CHUNK_SIZE));

	for (int y = 0; y < CHUNK_SIZE; ++y)
		for (int z = 0; z < CHUNK_SIZE; ++z)
			for (int x = 0; x < CHUNK_SIZE; ++x)
				voxels[x + CHUNK_SIZE * z + CHUNK_AREA * y] = x + y + z + 1;

}

glm::uint8 Chunk::GetVoxelAt(int x, int y, int z) const
{
	if ((0 <= x && x < CHUNK_SIZE) && (0 <= y && y < CHUNK_SIZE) && (0 <= z && z < CHUNK_SIZE))
		return voxels[x + z * CHUNK_SIZE + y * CHUNK_AREA];
	return 0;
}

void Chunk::Build()
{
	BuildChunkMesh(*this, world);
}

void Chunk::Render() const
{
	mesh.Render();
}
