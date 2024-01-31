#pragma once

#include <array>
#include <glm/glm.hpp>

#include "ChunkMesh.h"
#include "Constants.h"

using VoxelsArray = std::array<glm::uint8, CHUNK_VOLUME>;

class World;

class Chunk
{
public:
	Chunk(int cx, int cy, World& world);

	const glm::mat4& GetModelMat() const { return model; }
	glm::ivec2 GetPosition() const { return position; }

	glm::uint8 GetAtSafe(int vx, int vy, int vz) const;
	glm::uint8 GetAtSafe(const glm::ivec3& pos) const;
	glm::uint8 GetAt(int vx, int vy, int vz) const;
	glm::uint8 GetAt(const glm::ivec3& pos) const;

	void SetAtSafe(int vx, int vy, int vz, glm::uint8 id);
	void SetAtSafe(const glm::ivec3& pos, glm::uint8 id);
	void SetAt(int vx, int vy, int vz, glm::uint8 id);
	void SetAt(const glm::ivec3& pos, glm::uint8 id);
	void RemoveAtSafe(int vx, int vy, int vz);
	void RemoveAtSafe(const glm::ivec3& pos);

	void Build();
	void Rebuild();

	void Render() const;

private:
	World& world;

	VoxelsArray voxels{ 0 };

	ChunkMesh mesh;

	glm::ivec2 position{ 0 };
	glm::mat4 model{ 1.0f };
};

