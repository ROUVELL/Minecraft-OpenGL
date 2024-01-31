#pragma once

#include <glm/vec3.hpp>
#include "Constants.h"

inline bool IsIndexCorrect(int vx, int vy, int vz) noexcept
{
	return (0 <= vx && vx < CHUNK_WIDTH)
		&& (0 <= vy && vy < CHUNK_HEIGHT)
		&& (0 <= vz && vz < CHUNK_WIDTH);
}

inline bool IsIndexCorrect(const glm::ivec3& pos) noexcept
{
	return (0 <= pos.x && pos.x < CHUNK_WIDTH)
		&& (0 <= pos.y && pos.y < CHUNK_HEIGHT)
		&& (0 <= pos.z && pos.z < CHUNK_WIDTH);
}

inline glm::ivec3 GlobalToLocal(int wx, int wy, int wz) noexcept
{
	// NOTE: I think the result will be wrong for negative coordinates!
	return glm::ivec3{ wx % CHUNK_WIDTH, wy % CHUNK_HEIGHT, wz % CHUNK_WIDTH };
}

inline glm::ivec3 GlobalToLocal(const glm::ivec3& pos) noexcept
{
	return glm::ivec3{ pos.x % CHUNK_WIDTH, pos.y % CHUNK_HEIGHT, pos.z % CHUNK_WIDTH };;
}

inline size_t LocalToIndex(int vx, int vy, int vz) noexcept
{
	return vx + CHUNK_WIDTH * vz + CHUNK_AREA * vy;
}

inline size_t LocalToIndex(const glm::ivec3& pos) noexcept
{
	return pos.x + CHUNK_WIDTH * pos.z + CHUNK_AREA * pos.y;
}

inline glm::ivec2 GlobalToChunk(int wx, int wz) noexcept
{
	return glm::ivec2{ wx / CHUNK_WIDTH - (wx < 0 ? 1 : 0), wz / CHUNK_WIDTH - (wz < 0 ? 1 : 0) };
}

inline glm::ivec2 GlobalToChunk(const glm::ivec2& pos) noexcept
{
	return pos / CHUNK_WIDTH;
}

inline glm::ivec2 GlobalToChunk(const glm::ivec3& pos) noexcept
{
	return glm::ivec2{ pos.x / CHUNK_WIDTH, pos.z / CHUNK_WIDTH };
}

inline long long int ChunkPosToKey(int cx, int cz) noexcept
{
	return ((long long)cx << 32) | cz;
}

inline long long int ChunkPosToKey(const glm::ivec2 pos) noexcept
{
	return ((long long)pos.x << 32) | pos.y;
}


