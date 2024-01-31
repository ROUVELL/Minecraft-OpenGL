#pragma once

#include <vector>

class Chunk;
class World;

std::vector<unsigned int> BuildChunkMesh(Chunk& chunk, World& world);
