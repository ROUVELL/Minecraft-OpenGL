#pragma once

#include <memory>

#include "Chunk.h"
#include "Shader.h"
#include "Texture.h"

constexpr int WORLD_WIDTH = 50;
constexpr int WORLD_HEIGHT = 10;
constexpr int WORLD_AREA = WORLD_WIDTH * WORLD_WIDTH;
constexpr int WORLD_VOLUME = WORLD_AREA * WORLD_HEIGHT;

using ChunksArray = std::array<std::shared_ptr<Chunk>, WORLD_VOLUME>;

class Player;

class World
{
public:
	World(Player& player);
	~World();

	const Chunk* GetChunkAt(int x, int y, int z) const;
	const Chunk* At(int x, int y, int z) const { return chunks[x + WORLD_WIDTH * z + WORLD_AREA * y].get(); }

	void Generate();

	void Update();
	void Render();

private:
	Player& player;

	ChunksArray chunks;

	Shader chunkShader;
	Texture voxelTexture;
};

