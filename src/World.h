#pragma once

#include <memory>
#include <unordered_map>

#include "Chunk.h"
#include "Shader.h"
#include "Texture.h"

using ChunksArray = std::unordered_map<long long int, std::shared_ptr<Chunk>>;

class Player;

class World
{
public:
	World(Player& player);

	Chunk* GetAtSafe(int cx, int cz);
	Chunk* GetAtSafe(const glm::ivec2 pos);
	Chunk* GetAt(int cx, int cz);
	Chunk* GetAt(const glm::ivec2 pos);

	void RemoveVoxel();
	void RemoveVoxelSafe(int wx, int wy, int wz);

	void RebuildChunk(int cx, int cz);

	void Initialize();

	void Update();
	void Render();

private:
	Player& player;

	ChunksArray chunks;

	Shader chunkShader;
	Texture voxelTexture;


};

