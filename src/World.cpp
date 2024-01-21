#include "World.h"

#include <iostream>

#include "Player.h"

World::World(Player& player)
	: player(player)
{
}

World::~World()
{
}

const Chunk* World::GetChunkAt(int x, int y, int z) const
{
	if ((0 <= x && x < WORLD_WIDTH) && (0 <= y && y < WORLD_HEIGHT) && (0 <= z && z < WORLD_WIDTH))
		return chunks[x + z * WORLD_WIDTH + y * WORLD_AREA].get();
	return nullptr;
}

void World::Generate()
{
	chunkShader.Load("default");
	voxelTexture.Load("frame.png");

	chunkShader.Activate();
	chunkShader.SetTexture(voxelTexture, "u_tex0");
	voxelTexture.Bind();

	for (int y = 0; y < WORLD_HEIGHT; ++y)
		for (int z = 0; z < WORLD_WIDTH; ++z)
			for (int x = 0; x < WORLD_WIDTH; ++x)
				chunks[x + WORLD_WIDTH * z + WORLD_AREA * y] = std::make_shared<Chunk>(x, y, z, *this);

	for (const auto& chunk : chunks)
		chunk->Build();

	std::cout << (sizeof(char) * CHUNK_VOLUME * WORLD_VOLUME) / (1024 * 1024) << " Mb! \n";
}

void World::Update()
{
	chunkShader.SetCamMat(player.GetMatrix());
}

void World::Render()
{
	for (const auto& chunk : chunks)
	{
		chunkShader.SetModelMat(chunk->GetModelMat());
		chunk->Render();
	}
}
