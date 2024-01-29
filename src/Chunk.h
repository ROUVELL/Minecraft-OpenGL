#pragma once

#include <array>
#include <glm/glm.hpp>

#include "ChunkMesh.h"
#include "ChunkMeshBuilder.h"
#include "Constants.h"

using VoxelsArray = std::array<glm::uint8, CHUNK_VOLUME>;

class World;

class Chunk
{
public:
	Chunk(int x, int y, World& world);

	const glm::mat4& GetModelMat() const { return model; }

	glm::ivec2 GetPosition() const { return position; }
	glm::uint8 GetVoxelAt(int x, int y, int z) const;
	glm::uint8 GetAt(int x, int y, int z) const { return voxels[x + CHUNK_WIDTH * z + CHUNK_AREA * y]; }

	void SetVoxelAt(int x, int y, int z, glm::uint8 id) { voxels[x + CHUNK_WIDTH * z + CHUNK_AREA * y] = id; }
	void RemoveAt(int x, int y, int z);

	void Build();
	void Rebuild();

	void Render() const;

private:
	World& world;

	VoxelsArray voxels{ 0 };

	ChunkMesh mesh;

	glm::ivec2 position{ 0 };
	glm::mat4 model{ 1.0f };

	friend std::vector<unsigned int> BuildChunkMesh(Chunk& chunk, const World& world);
};

