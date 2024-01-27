#include "ChunkMeshBuilder.h"

#include <vector>

#include "Chunk.h"
#include "World.h"

// faces
constexpr glm::uint8 TOP_FACE =    0;
constexpr glm::uint8 BOTTOM_FACE = 1;
constexpr glm::uint8 RIGHT_FACE =  2;
constexpr glm::uint8 LEFT_FACE =   3;
constexpr glm::uint8 FRONT_FACE =  4;
constexpr glm::uint8 BACK_FACE =   5;

// UVs
constexpr glm::uint8 BOTTOM_LEFT =  0;  // 00
constexpr glm::uint8 TOP_LEFT =     1;  // 01
constexpr glm::uint8 BOTTOM_RIGHT = 2;  // 10
constexpr glm::uint8 TOP_RIGHT =    3;  // 11

/*
x and z     from 0 to 32   = 6 bits
y           from 0 to 96   = 7 bits
volexId     from 0 to 255  = 8 bits
uv          from 0 to 3    = 2 bits

total                      = 29 bits
*/

using uInt = unsigned int;

inline static uInt PackData(int x, int y, int z, glm::uint8 voxelId, glm::uint8 uv) noexcept
{
	return (x << 23) | (y << 16) | (z << 10) | (voxelId << 2)  | uv;
}

inline static bool IsVoid(const World& world, int vx, int vy, int vz, int wx, int wz)
{
	const int cx = wx / CHUNK_WIDTH - (wx < 0 ? 1 : 0);
	const int cz = wz / CHUNK_WIDTH - (wz < 0 ? 1 : 0);

	const Chunk* const chunk_ptr = world.GetChunkAt(cx, cz);

	if (chunk_ptr == nullptr)
		return false;

	if (chunk_ptr->GetAt((vx + CHUNK_WIDTH) % CHUNK_WIDTH, vy, (vz + CHUNK_WIDTH) % CHUNK_WIDTH))
		return false;

	return true;
};

void BuildChunkMesh(Chunk& chunk, const World& world)
{
	std::vector<uInt> vertData;

	const glm::ivec2 chunkPos = chunk.GetPosition();

	for (int y = 0; y < CHUNK_HEIGHT; ++y)
	{
		const bool IS_TOP = y == (CHUNK_HEIGHT - 1);
		const bool CHECK_BOTTOM = y != 0;

		for (int z = 0; z < CHUNK_WIDTH; ++z)
		{
			const int wz = z + chunkPos.y * CHUNK_WIDTH;

			for (int x = 0; x < CHUNK_WIDTH; ++x)
			{
				const glm::uint8 voxelID = chunk.GetAt(x, y, z);

				if (!voxelID)
					continue;

				const int wx = x + chunkPos.x * CHUNK_WIDTH;

				// top face
				if (IS_TOP || IsVoid(world, x, y + 1, z, wx, wz))
				{
					uInt v0 = PackData(x + 1, y + 1, z    , voxelID, TOP_RIGHT);
					uInt v1 = PackData(x + 1, y + 1, z + 1, voxelID, BOTTOM_RIGHT);
					uInt v2 = PackData(x    , y + 1, z + 1, voxelID, BOTTOM_LEFT);
					uInt v3 = PackData(x    , y + 1, z    , voxelID, TOP_LEFT);

					vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// bottom face
				if (CHECK_BOTTOM && IsVoid(world, x, y - 1, z, wx, wz))
				{
					uInt v0 = PackData(x + 1, y, z + 1, voxelID, TOP_RIGHT);
					uInt v1 = PackData(x + 1, y, z    , voxelID, BOTTOM_RIGHT);
					uInt v2 = PackData(x    , y, z    , voxelID, BOTTOM_LEFT);
					uInt v3 = PackData(x,     y, z + 1, voxelID, TOP_LEFT);

					vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// right face
				if (IsVoid(world, x + 1, y, z, wx + 1, wz))
				{
					uInt v0 = PackData(x + 1, y + 1, z    , voxelID, TOP_RIGHT);
					uInt v1 = PackData(x + 1, y    , z    , voxelID, BOTTOM_RIGHT);
					uInt v2 = PackData(x + 1, y    , z + 1, voxelID, BOTTOM_LEFT);
					uInt v3 = PackData(x + 1, y + 1, z + 1, voxelID, TOP_LEFT);

					vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// left face
				if (IsVoid(world, x - 1, y, z, wx - 1, wz))
				{
					uInt v0 = PackData(x, y + 1, z + 1, voxelID, TOP_RIGHT);
					uInt v1 = PackData(x, y    , z + 1, voxelID, BOTTOM_RIGHT);
					uInt v2 = PackData(x, y    , z    , voxelID, BOTTOM_LEFT);
					uInt v3 = PackData(x, y + 1, z    , voxelID, TOP_LEFT);

					vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// front face
				if (IsVoid(world, x, y, z + 1, wx, wz + 1))
				{
					uInt v0 = PackData(x + 1, y + 1, z + 1, voxelID, TOP_RIGHT);
					uInt v1 = PackData(x + 1, y    , z + 1, voxelID, BOTTOM_RIGHT);
					uInt v2 = PackData(x    , y    , z + 1, voxelID, BOTTOM_LEFT);
					uInt v3 = PackData(x    , y + 1, z + 1, voxelID, TOP_LEFT);

					vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// back face
				if (IsVoid(world, x, y, z - 1, wx, wz - 1))
				{
					uInt v0 = PackData(x,     y + 1, z, voxelID, TOP_RIGHT);
					uInt v1 = PackData(x    , y    , z, voxelID, BOTTOM_RIGHT);
					uInt v2 = PackData(x + 1, y    , z, voxelID, BOTTOM_LEFT);
					uInt v3 = PackData(x + 1, y + 1, z, voxelID, TOP_LEFT);

					vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
			}
		}
	}
	
	chunk.mesh.Build(vertData);
}


