#pragma once

#include <memory>

#include "Chunk.h"
#include "Shader.h"
#include "Texture.h"

constexpr int WORLD_WIDTH = 15;
constexpr int H_WORLD_WIDTH = WORLD_WIDTH >> 1;
constexpr int WORLD_AREA = WORLD_WIDTH * WORLD_WIDTH;

constexpr int WORLD_XZ_CENTER = (H_WORLD_WIDTH * CHUNK_WIDTH) + H_CHUNK_WIDTH;
constexpr int WORLD_Y_CENTER = H_CHUNK_HEIGHT;

using ChunksArray = std::array<std::shared_ptr<Chunk>, WORLD_AREA>;

class Player;

class World
{
public:
	World(Player& player);
	~World();

	const Chunk* GetChunkAt(int x, int y) const;
	const Chunk* GetAt(int x, int y) const { return chunks[x + WORLD_WIDTH * y].get(); }

	void Generate();

	void Update();
	void Render();

private:
	Player& player;

	ChunksArray chunks;

	Shader chunkShader;
	Texture voxelTexture;
};

