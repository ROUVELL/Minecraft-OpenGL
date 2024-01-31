#include "Chunk.h"

#include <glm/gtc/matrix_transform.hpp>

#include "World.h"
#include "ChunkMeshBuilder.h"
#include "TerrainGenerator.h"
#include "Uttils.h"

Chunk::Chunk(int cx, int cy, World& world)
	: position(cx, cy), world(world)
{
	model = glm::translate(glm::mat4(1.0f), glm::vec3(cx * CHUNK_WIDTH, 0, cy * CHUNK_WIDTH));

    const glm::ivec2 chunkPos = position * CHUNK_WIDTH;

	for (int x = 0; x < CHUNK_WIDTH; ++x)
    {
        const int wx = x + chunkPos.x;

        for (int z = 0; z < CHUNK_WIDTH; ++z)
        {
            const int wz = z + chunkPos.y;
            
            const int height = GetHeight(wx, wz);

            for (int y = 0; y < height; ++y)
                voxels[LocalToIndex(x, y, z)] = position.x + position.y + 1;
                //SetVoxel(*this, x, y, z, wx, wz, height);
        }
    }
}

glm::uint8 Chunk::GetAtSafe(int vx, int vy, int vz) const
{
	if (IsIndexCorrect(vx, vy, vz))
		return voxels[LocalToIndex(vx, vy, vz)];
	return 0;
}

glm::uint8 Chunk::GetAtSafe(const glm::ivec3& pos) const
{
    if (IsIndexCorrect(pos))
        return voxels[LocalToIndex(pos)];
    return 0;
}

glm::uint8 Chunk::GetAt(int vx, int vy, int vz) const
{
    return voxels[LocalToIndex(vx, vy, vz)];
}

glm::uint8 Chunk::GetAt(const glm::ivec3& pos) const
{
    return voxels[LocalToIndex(pos)];
}

void Chunk::SetAtSafe(int vx, int vy, int vz, glm::uint8 id)
{
    if (IsIndexCorrect(vx, vy, vz))
        voxels[LocalToIndex(vx, vy, vz)] = id;
}

void Chunk::SetAtSafe(const glm::ivec3& pos, glm::uint8 id)
{
    if (IsIndexCorrect(pos))
        voxels[LocalToIndex(pos)] = id;
}

void Chunk::SetAt(int vx, int vy, int vz, glm::uint8 id)
{
    voxels[LocalToIndex(vx, vy, vz)] = id;
}

void Chunk::SetAt(const glm::ivec3& pos, glm::uint8 id)
{
    voxels[LocalToIndex(pos)] = id;
}

void Chunk::RemoveAtSafe(int vx, int vy, int vz)
{
    if (GetAtSafe(vx, vy, vz))
    {
        SetAt(vx, vy, vz, 0);
        Rebuild();
    }
}

void Chunk::RemoveAtSafe(const glm::ivec3& pos)
{
    if (GetAtSafe(pos))
    {
        SetAt(pos, 0);
        Rebuild();
    }
}

void Chunk::Build()
{
	mesh.Build(BuildChunkMesh(*this, world));
}

void Chunk::Rebuild()
{
    mesh.Rebuild(BuildChunkMesh(*this, world));
}

void Chunk::Render() const
{
	mesh.Render();
}
