#include "World.h"

#include <iostream>
#include <glad/glad.h>

#include "Player.h"

constexpr float MAX_RAY_DIST = 8.0f;

struct RayCastResult
{
	Chunk* chunk_ptr;
	const glm::ivec3 voxelPos;
};

static inline RayCastResult RayCastVoxels(const World& world, const Player& player);


World::World(Player& player)
	: player(player)
{
}

Chunk* World::GetChunkAt(int x, int y) const
{
	auto pair = chunks.find(((long long)x << 32) | y);

	if (pair != chunks.cend())
		return pair->second.get();
	return nullptr;
}

Chunk* World::GetAt(int x, int y)
{
	return chunks[((long long)x << 32) | y].get();
}

void World::Remove()
{
	const RayCastResult result = RayCastVoxels(*this, player);

	if (result.chunk_ptr != nullptr)
		result.chunk_ptr->RemoveAt(result.voxelPos.x, result.voxelPos.y, result.voxelPos.z);
}

void World::RemoveAt(int x, int y, int z)
{
	Chunk* const chunk = GetChunkAt(x / CHUNK_WIDTH, z / CHUNK_WIDTH);

	if (chunk != nullptr)
		chunk->RemoveAt(x % CHUNK_WIDTH, y % CHUNK_HEIGHT, z % CHUNK_WIDTH);
}

void World::Generate()
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

static RayCastResult RayCastVoxels(const World& world, const Player& player)
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
								{ (int)current.x % CHUNK_WIDTH,
								(int)current.y % CHUNK_HEIGHT,
								(int)current.z % CHUNK_WIDTH } };
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
