#pragma once

#include <array>
#include <glm/glm.hpp>

#include "ChunkMesh.h"
#include "ChunkMeshBuilder.h"

constexpr int CHUNK_WIDTH = 16;
constexpr int CHUNK_HEIGHT = 96;
constexpr int H_CHUNK_WIDTH = CHUNK_WIDTH >> 1;
constexpr int H_CHUNK_HEIGHT = CHUNK_HEIGHT >> 1;
constexpr int CHUNK_AREA = CHUNK_WIDTH * CHUNK_WIDTH;
constexpr int CHUNK_VOLUME = CHUNK_AREA * CHUNK_HEIGHT;

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

	void Build();

	void Render() const;

private:
	World& world;

	VoxelsArray voxels{ 0 };

	ChunkMesh mesh;

	glm::ivec2 position{ 0 };
	glm::mat4 model{ 1.0f };

	friend void BuildChunkMesh(Chunk& chunk, const World& world);
};

