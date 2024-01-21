#pragma once

#include <array>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "ChunkMeshBuilder.h"

constexpr int CHUNK_SIZE = 32;
constexpr int H_CHUNK_SIZE = CHUNK_SIZE / 2;
constexpr int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
constexpr int CHUNK_VOLUME = CHUNK_AREA * CHUNK_SIZE;

using VoxelsArray = std::array<glm::uint8, CHUNK_VOLUME>;

class World;

class Chunk
{
public:
	Chunk(int x, int y, int z, World& world);

	const glm::mat4& GetModelMat() const { return model; }

	glm::ivec3 GetPosition() const { return position; }
	glm::uint8 GetVoxelAt(int x, int y, int z) const;
	glm::uint8 At(int x, int y, int z) const { return voxels[x + CHUNK_SIZE * z + CHUNK_AREA * y]; }

	void Build();

	void Render() const;

private:
	World& world;

	VoxelsArray voxels{ 0 };

	Mesh mesh;

	glm::ivec3 position{ 0 };
	glm::mat4 model{ 1.0f };

	friend void BuildChunkMesh(Chunk& chunk, const World& world);
};

