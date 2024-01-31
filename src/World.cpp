#include "World.h"

#include <iostream>
#include <glad/glad.h>

#include "Player.h"
#include "Uttils.h"

struct RayCastResult
{
	Chunk* chunk_ptr;
	glm::ivec3 local;
	glm::ivec2 chunkPos;
};

static inline RayCastResult RayCastVoxels(World& world, const Player& player);


World::World(Player& player)
	: player(player)
{
}

Chunk* World::GetAtSafe(int cx, int cz)
{
	if (chunks.contains(ChunkPosToKey(cx, cz)))
		return chunks[ChunkPosToKey(cx, cz)].get();
	return nullptr;
}

Chunk* World::GetAtSafe(const glm::ivec2 pos)
{
	if (chunks.contains(ChunkPosToKey(pos)))
		return chunks[ChunkPosToKey(pos)].get();
	return nullptr;
}

Chunk* World::GetAt(int cx, int cz)
{
	return chunks[ChunkPosToKey(cx, cz)].get();
}

Chunk* World::GetAt(const glm::ivec2 pos)
{
	return chunks[ChunkPosToKey(pos)].get();
}

void World::RemoveVoxel()
{
	const RayCastResult result = RayCastVoxels(*this, player);

	if (result.chunk_ptr != nullptr)
	{
		result.chunk_ptr->RemoveAtSafe(result.local);


		// rebuild adjacent chunks

		/*
		NOTE: It is not necessary to rebuild the neighboring chunk if the blocks
		of the neighboring chunk are not closer to the removed block than 2.
		Since it does not affect the mesh itself or its lighting (ao).
		*/
		if (result.local.x == 0)                    RebuildChunk(result.chunkPos.x - 1, result.chunkPos.y    );
		else if (result.local.x == CHUNK_WIDTH - 1) RebuildChunk(result.chunkPos.x + 1, result.chunkPos.y    );
		if (result.local.z == 0)                    RebuildChunk(result.chunkPos.x    , result.chunkPos.y - 1);
		else if (result.local.z == CHUNK_WIDTH - 1) RebuildChunk(result.chunkPos.x    , result.chunkPos.y + 1);
	}
}

void World::RemoveVoxelSafe(int wx, int wy, int wz)
{
	const long long int key = ChunkPosToKey(GlobalToChunk(wx, wz));

	if (chunks.contains(key))
		chunks[key]->RemoveAtSafe(GlobalToLocal(wx, wy, wz));
}

void World::RebuildChunk(int cx, int cz)
{
	if (chunks.contains(ChunkPosToKey(cx, cz)))
		chunks[ChunkPosToKey(cx, cz)]->Rebuild();
}

void World::Initialize()
{
	chunkShader.Load("default");
	voxelTexture.Load("frame.png", GL_TEXTURE_2D);

	chunkShader.Activate();
	chunkShader.SetTexture(voxelTexture, "u_tex0");
	voxelTexture.Bind();

	for (int z = 0; z < WORLD_WIDTH; ++z)
		for (int x = 0; x < WORLD_WIDTH; ++x)
			chunks[ChunkPosToKey(x, z)] = std::make_shared<Chunk>(x, z, *this);

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

static inline RayCastResult RayCastVoxels(World& world, const Player& player)
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
		chunk_ptr = world.GetAtSafe(GlobalToChunk((int)current.x, (int)current.z));

		if (chunk_ptr != nullptr)
		{
			if (chunk_ptr->GetAtSafe(GlobalToLocal((int)current.x, (int)current.y, (int)current.z)))
				return RayCastResult{ chunk_ptr, GlobalToLocal((int)current.x, (int)current.y, (int)current.z), GlobalToChunk((int)current.x, (int)current.z)};
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
