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

const Chunk* World::GetChunkAt(int x, int y) const
{
	if ((0 <= x && x < WORLD_WIDTH) && (0 <= y && y < WORLD_WIDTH))
		return chunks[x + WORLD_WIDTH * y].get();
	return nullptr;
}

void World::Generate()
{
	chunkShader.Load("default");
	voxelTexture.Load("frame.png");

	chunkShader.Activate();
	chunkShader.SetTexture(voxelTexture, "u_tex0");
	voxelTexture.Bind();

	for (int y = 0; y < WORLD_WIDTH; ++y)
		for (int x = 0; x < WORLD_WIDTH; ++x)
			chunks[x + WORLD_WIDTH * y] = std::make_shared<Chunk>(x, y, *this);

	for (const auto& chunk : chunks)
		chunk->Build();

	std::cout << ((1.0f * CHUNK_VOLUME * WORLD_AREA) / 1024.0f) / 1024.0f << " Mb! \n";
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
