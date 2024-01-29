#include "World.h"

#include <iostream>
#include <glad/glad.h>

#include "Player.h"
#include "Constants.h"

struct RayCastResult
{
	Chunk* chunk_ptr;
	int vx, vy, vz;
	int cx, cz;
};

static inline RayCastResult RayCastVoxels(const World& world, const Player& player);


World::World(Player& player)
	: player(player)
{
}

Chunk* World::GetChunkAt(int cx, int cy) const
{
	auto pair = chunks.find(((long long)cx << 32) | cy);

	if (pair != chunks.cend())
		return pair->second.get();
	return nullptr;
}

Chunk* World::GetAt(int cx, int cy)
{
	return chunks[((long long)cx << 32) | cy].get();
}

void World::RemoveVoxel()
{
	const RayCastResult result = RayCastVoxels(*this, player);

	if (result.chunk_ptr != nullptr)
		result.chunk_ptr->RemoveAt(result.vx, result.vy, result.vz);

	// rebuild adjacent chunks

	/*
	NOTE: It is not necessary to rebuild the neighboring chunk if the blocks
	of the neighboring chunk are not closer to the removed block than 2.
	Since it does not affect the mesh itself or its lighting (ao).
	*/
	if (result.vx == 0)                    RebuildChunk(result.cx - 1, result.cz);
	else if (result.vx == CHUNK_WIDTH - 1) RebuildChunk(result.cx + 1, result.cz);
	if (result.vz == 0)                    RebuildChunk(result.cx, result.cz - 1);
	else if (result.vz == CHUNK_WIDTH - 1) RebuildChunk(result.cx, result.cz + 1);
}

void World::RemoveVoxel(int wx, int wy, int wz)
{
	Chunk* const chunk = GetChunkAt(wx / CHUNK_WIDTH, wz / CHUNK_WIDTH);

	if (chunk != nullptr)
		chunk->RemoveAt(wx % CHUNK_WIDTH, wy % CHUNK_HEIGHT, wz % CHUNK_WIDTH);
}

void World::RebuildChunk(int cx, int cz)
{
	Chunk* const chunk_ptr = GetChunkAt(cx, cz);
	if (chunk_ptr != nullptr)
		chunk_ptr->Rebuild();
}

void World::Initialize()
{
	chunkShader.Load("default");
	voxelTexture.Load("frame.png", GL_TEXTURE_2D);

	chunkShader.Activate();
	chunkShader.SetTexture(voxelTexture, "u_tex0");
	voxelTexture.Bind();

	for (int y = 0; y < WORLD_WIDTH; ++y)
		for (int x = 0; x < WORLD_WIDTH; ++x)
			chunks[((long long)x << 32) | y] = std::make_shared<Chunk>(x, y, *this);

	for (const auto& chunk : chunks)
		chunk.second->Build();
}

void World::Update()
{
	chunkShader.SetCamMat(player.GetMatrix());
}

void World::Render()
{
	for (const auto& chunk : chunks)
	{
		chunkShader.SetModelMat(chunk.second->GetModelMat());
		chunk.second->Render();
	}
}

static inline RayCastResult RayCastVoxels(const World& world, const Player& player)
{
	const glm::vec3 start = player.GetPosition();
	const glm::vec3 end = start + player.GetDirection() * MAX_RAY_DIST;

	glm::vec3 current = glm::vec3(start);

	const glm::vec3 d = glm::sign(end - start);
	const glm::vec3 delta = glm::vec3(
		(d.x != 0) ? std::fminf(d.x / (end.x - start.x), 10000.0f) : 10000.0f,
		(d.y != 0) ? std::fminf(d.y / (end.y - start.y), 10000.0f) : 10000.0f,
		(d.z != 0) ? std::fminf(d.z / (end.z - start.z), 10000.0f) : 10000.0f
	);
	glm::vec3 max = glm::vec3(
		(d.x > 0) ? delta.x * (1.0f - glm::fract(start.x)) : delta.x * glm::fract(start.x),
		(d.y > 0) ? delta.y * (1.0f - glm::fract(start.y)) : delta.y * glm::fract(start.y),
		(d.z > 0) ? delta.z * (1.0f - glm::fract(start.z)) : delta.z * glm::fract(start.z)
	);

	Chunk* chunk_ptr = nullptr;

	while (!(max.x > 1.0f && max.y > 1.0f && max.z > 1.0f))
	{
		chunk_ptr = world.GetChunkAt((int)current.x / CHUNK_WIDTH, (int)current.z / CHUNK_WIDTH);

		if (chunk_ptr != nullptr)
		{
			if (chunk_ptr->GetVoxelAt((int)current.x % CHUNK_WIDTH, (int)current.y % CHUNK_HEIGHT, (int)current.z % CHUNK_WIDTH))
				return RayCastResult{ chunk_ptr,
								(int)current.x % CHUNK_WIDTH,
								(int)current.y % CHUNK_HEIGHT,
								(int)current.z % CHUNK_WIDTH,
								(int)current.x / CHUNK_WIDTH,
								(int)current.z / CHUNK_WIDTH };
		}

		if (max.x < max.y)
		{
			if (max.x < max.z)
			{
				current.x += d.x;
				max.x += delta.x;
			}
			else
			{
				current.z += d.z;
				max.z += delta.z;
			}
		}
		else
		{
			if (max.y < max.z)
			{
				current.y += d.y;
				max.y += delta.y;
			}
			else
			{
				current.z += d.z;
				max.z += delta.z;
			}
		}
	}

	return RayCastResult{ nullptr };
}		
