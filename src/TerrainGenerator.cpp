#include "TerrainGenerator.h"

#include <cmath>
#include <ctime>
#include <glm/gtc/noise.hpp>

#include "World.h"
#include "Constants.h"

constexpr float a1 = (float)H_CHUNK_HEIGHT;  // amplitude
constexpr float a2 = a1 * 0.5f;
constexpr float a4 = a1 * 0.25f;
constexpr float a8 = a1 * 0.125f;

constexpr float f1 = 0.005f;  // frequency
constexpr float f2 = f1 * 2.0f;
constexpr float f4 = f1 * 4.0f;
constexpr float f8 = f1 * 8.0f;

const glm::uint8 STONE = 1;
const glm::uint8 SAND = 2;
const glm::uint8 DIRT = 3;
const glm::uint8 GRASS = 4;
const glm::uint8 SNOW = 5;

const int STONE_LVL = 49;
const int SAND_LVL = 7;
const int DIRT_LVL = 40;
const int GRASS_LVL = 8;
const int SNOW_LVL = 54;


int GetHeight(int x, int z)
{
    const float island = std::fminf(1.0f / (std::powf(0.0025f * std::hypotf(float(x - WORLD_XZ_CENTER), float(z - WORLD_XZ_CENTER)), 20.0f) + 0.0f), 1.0f);

    float height = 0.0f;

    height += glm::perlin(glm::vec2{ x * f1, z * f1 }) * a1 + a1;
    height += glm::perlin(glm::vec2{ x * f2, z * f2 }) * a2 - a2;
    height += glm::perlin(glm::vec2{ x * f4, z * f4 }) * a4 + a4;
    height += glm::perlin(glm::vec2{ x * f8, z * f8 }) * a8 - a8;
    
    return (int)(std::fmaxf(height, 2.0f) * island);
}

void SetVoxel(Chunk& chunk, int x, int y, int z, int wx, int wz, int height)
{
    std::srand((unsigned int)std::time(nullptr));

    if (y < height - 1)
    {
        // caves  !!! VERY SLOW ON DEBUG !!!
        //if (glm::perlin(glm::vec3{ wx * 0.09f, y * 0.09f, wz * 0.09f }) > 0.0f
        //    && ((glm::perlin(glm::vec2{ wx * 0.1f, wz * 0.1f }) * 3.0f + 3.0f) < y && y < height - 10))
        //    chunk.SetVoxelAt(x, y, z, 0);
        //else
            chunk.SetVoxelAt(x, y, z, STONE);
    }
    else
    {
        const int rng = std::rand() % 7;
        const int ry = y - rng;

        if (SNOW_LVL <= ry && ry < height)         chunk.SetVoxelAt(x, y, z, SNOW);
        else if (STONE_LVL <= ry && ry < SNOW_LVL) chunk.SetVoxelAt(x, y, z, STONE);
        else if (DIRT_LVL <= ry && ry < STONE_LVL) chunk.SetVoxelAt(x, y, z, DIRT);
        else if (GRASS_LVL <= ry && ry < DIRT_LVL) chunk.SetVoxelAt(x, y, z, GRASS);
        else chunk.SetVoxelAt(x, y, z, SAND);
    }

}


