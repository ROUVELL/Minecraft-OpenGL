#include "Chunk.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>

#include "World.h"
#include "Shader.h"

Chunk::Chunk(int x, int y, World& world)
	: position(x, y), world(world)
{
	model = glm::translate(glm::mat4(1.0f), glm::vec3(x * CHUNK_WIDTH, 0, y * CHUNK_WIDTH));

    const glm::ivec2 chunkPos = position * CHUNK_WIDTH;

	for (int x = 0; x < CHUNK_WIDTH; ++x)
    {
        int wx = x + chunkPos.x;

        for (int z = 0; z < CHUNK_WIDTH; ++z)
        {
            int wz = z + chunkPos.y;

            int height = (int)(glm::simplex(glm::vec2(wx, wz) * 0.01f) * 32 + 32);

            for (int y = 0; y < height; ++y)
                voxels[x + CHUNK_WIDTH * z + CHUNK_AREA * y] = y;
        }
    }

}

glm::uint8 Chunk::GetVoxelAt(int x, int y, int z) const
{
	if ((0 <= x && x < CHUNK_WIDTH) && (0 <= y && y < CHUNK_HEIGHT) && (0 <= z && z < CHUNK_WIDTH))
		return voxels[x + z * CHUNK_WIDTH + y * CHUNK_AREA];
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
