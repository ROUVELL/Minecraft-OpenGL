#pragma once

class Chunk;

int GetHeight(int x, int z);

void SetVoxel(Chunk& chunk, int x, int y, int z, int wx, int wz, int height);

