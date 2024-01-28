#pragma once

#include <memory>
#include <unordered_map>

#include "Chunk.h"
#include "Shader.h"
#include "Texture.h"

constexpr int WORLD_WIDTH = 1;
constexpr int H_WORLD_WIDTH = WORLD_WIDTH >> 1;
constexpr int WORLD_AREA = WORLD_WIDTH * WORLD_WIDTH;

constexpr int WORLD_XZ_CENTER = (H_WORLD_WIDTH * CHUNK_WIDTH) + H_CHUNK_WIDTH;
constexpr int WORLD_Y_CENTER = H_CHUNK_HEIGHT;

using ChunksArray = std::unordered_map<long long int, std::shared_ptr<Chunk>>;

class Player;

class World
{
public:
	World(Player& player);

	Chunk* GetChunkAt(int x, int y) const;
	Chunk* GetAt(int x, int y);

	void Remove();
	void RemoveAt(int x, int y, int z);

	void Generate();


	void Update();
	void Render();

private:
	Player& player;

	ChunksArray chunks;

	Shader chunkShader;
	Texture voxelTexture;
};

