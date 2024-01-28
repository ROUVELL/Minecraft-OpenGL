#include "ChunkMeshBuilder.h"

#include <iostream>
#include <array>

#include "Chunk.h"
#include "World.h"

// faces
constexpr int TOP_FACE =    0;
constexpr int BOTTOM_FACE = 1;
constexpr int RIGHT_FACE =  2;
constexpr int LEFT_FACE =   3;
constexpr int FRONT_FACE =  4;
constexpr int BACK_FACE =   5;

// plane
constexpr int Y_PLANE = 1;
constexpr int X_PLANE = 2;
constexpr int Z_PLANE = 3;

constexpr int WORLD_BORDER = CHUNK_WIDTH * WORLD_WIDTH - 1;

/*
x and z     from 0 to 16   = 5 bits
y           from 0 to 96   = 7 bits
volexId     from 0 to 255  = 8 bits
faceId      from 0 to 5    = 3 bits
ao          from 0 to 3    = 2 bits
flip        from 0 to 1    = 1 bit

total                      = 31 bits
*/

using uInt = unsigned int;

inline static uInt PackData(int x, int y, int z, glm::uint8 voxelId, int faceId, int ao, int flip) noexcept
{
	return (x << 26) | (y << 19) | (z << 14) | (voxelId << 6) | (faceId << 3) | (ao << 1) | flip;
}

inline static bool IsVoid(int vx, int vy, int vz, int wx, int wz, const World& world)
{
	const int cx = wx / CHUNK_WIDTH - (wx < 0 ? 1 : 0);
	const int cz = wz / CHUNK_WIDTH - (wz < 0 ? 1 : 0);

	const Chunk* const chunk_ptr = world.GetChunkAt(cx, cz);

	if (chunk_ptr == nullptr)
		return true;

	if (chunk_ptr->GetVoxelAt((vx + CHUNK_WIDTH) % CHUNK_WIDTH, vy, (vz + CHUNK_WIDTH) % CHUNK_WIDTH))
		return false;

	return true;
};

inline static std::array<int, 4> GetAo(int vx, int vy, int vz, int wx, int wz, const World& world, int plane)
{
	int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;

	switch (plane)
	{
	case Y_PLANE:
		a = IsVoid(vx    , vy, vz - 1, wx    , wz - 1, world);
		b = IsVoid(vx + 1, vy, vz - 1, wx + 1, wz - 1, world);
		c = IsVoid(vx + 1, vy, vz    , wx + 1, wz    , world);
		d = IsVoid(vx + 1, vy, vz + 1, wx + 1, wz + 1, world);
		e = IsVoid(vx    , vy, vz + 1, wx    , wz + 1, world);
		f = IsVoid(vx - 1, vy, vz + 1, wx - 1, wz + 1, world);
		g = IsVoid(vx - 1, vy, vz    , wx - 1, wz    , world);
		h = IsVoid(vx - 1, vy, vz - 1, wx - 1, wz - 1, world);
		break;

	case X_PLANE:
		a = IsVoid(vx, vy + 1, vz    , wx, wz    , world);
		b = IsVoid(vx, vy + 1, vz - 1, wx, wz - 1, world);
		c = IsVoid(vx, vy    , vz - 1, wx, wz - 1, world);
		d = IsVoid(vx, vy - 1, vz - 1, wx, wz - 1, world);
		e = IsVoid(vx, vy - 1, vz    , wx, wz    , world);
		f = IsVoid(vx, vy - 1, vz + 1, wx, wz + 1, world);
		g = IsVoid(vx, vy    , vz + 1, wx, wz + 1, world);
		h = IsVoid(vx, vy + 1, vz + 1, wx, wz + 1, world);
		break;

	case Z_PLANE:
		a = IsVoid(vx    , vy + 1, vz, wx    , wz, world);
		b = IsVoid(vx + 1, vy + 1, vz, wx + 1, wz, world);
		c = IsVoid(vx + 1, vy    , vz, wx + 1, wz, world);
		d = IsVoid(vx + 1, vy - 1, vz, wx + 1, wz, world);
		e = IsVoid(vx    , vy - 1, vz, wx    , wz, world);
		f = IsVoid(vx - 1, vy - 1, vz, wx - 1, wz, world);
		g = IsVoid(vx - 1, vy    , vz, wx - 1, wz, world);
		h = IsVoid(vx - 1, vy + 1, vz, wx - 1, wz, world);
		break;

	default:
		break;
	}

	return std::array<int, 4>({ a + b + c, c + d + e, e + f + g, g + h + a });
}

std::vector<unsigned int> BuildChunkMesh(Chunk& chunk, const World& world)
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
			
			const bool CHECK_FRONT = wz != WORLD_BORDER;
			const bool CHECK_BACK = wz != 0;

			for (int x = 0; x < CHUNK_WIDTH; ++x)
			{
				const int wx = x + chunkPos.x * CHUNK_WIDTH;
				
				const bool CHECK_RIGHT = wx != WORLD_BORDER;
				const bool CHECK_LEFT = wx != 0;

				const glm::uint8 voxelID = chunk.GetAt(x, y, z);
				if (!voxelID)
					continue;

				// top face
 				if (IS_TOP || IsVoid(x, y + 1, z, wx, wz, world))
				{
					const auto ao = GetAo(x, y + 1, z, wx, wz, world, Y_PLANE);
					const int flip = ao[3] + ao[1] > ao[0] + ao[2];

					uInt v0 = PackData(x + 1, y + 1, z    , voxelID, TOP_FACE, ao[0], flip);
					uInt v1 = PackData(x + 1, y + 1, z + 1, voxelID, TOP_FACE, ao[1], flip);
					uInt v2 = PackData(x    , y + 1, z + 1, voxelID, TOP_FACE, ao[2], flip);
					uInt v3 = PackData(x    , y + 1, z    , voxelID, TOP_FACE, ao[3], flip);

					if (flip)
						vertData.insert(vertData.end(), { v1, v2, v3, v1, v3, v0 });
					else
						vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// bottom face
				if (CHECK_BOTTOM && IsVoid(x, y - 1, z, wx, wz, world))
				{
					const auto ao = GetAo(x, y - 1, z, wx, wz, world, Y_PLANE);
					const int flip = ao[3] + ao[1] > ao[0] + ao[2];

					uInt v0 = PackData(x + 1, y, z + 1, voxelID, BOTTOM_FACE, ao[3], flip);
					uInt v1 = PackData(x + 1, y, z    , voxelID, BOTTOM_FACE, ao[2], flip);
					uInt v2 = PackData(x    , y, z    , voxelID, BOTTOM_FACE, ao[1], flip);
					uInt v3 = PackData(x,     y, z + 1, voxelID, BOTTOM_FACE, ao[0], flip);

					if (flip)
						vertData.insert(vertData.end(), { v1, v2, v3, v1, v3, v0 });
					else
						vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// right face
				if (CHECK_RIGHT && IsVoid(x + 1, y, z, wx + 1, wz, world))
				{
					const auto ao = GetAo(x + 1, y, z, wx + 1, wz, world, X_PLANE);
					const int flip = ao[3] + ao[1] > ao[0] + ao[2];

					uInt v0 = PackData(x + 1, y + 1, z    , voxelID, RIGHT_FACE, ao[0], flip);
					uInt v1 = PackData(x + 1, y    , z    , voxelID, RIGHT_FACE, ao[1], flip);
					uInt v2 = PackData(x + 1, y    , z + 1, voxelID, RIGHT_FACE, ao[2], flip);
					uInt v3 = PackData(x + 1, y + 1, z + 1, voxelID, RIGHT_FACE, ao[3], flip);

					if (flip)
						vertData.insert(vertData.end(), { v1, v2, v3, v1, v3, v0 });
					else
						vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// left face
				if (CHECK_LEFT && IsVoid(x - 1, y, z, wx - 1, wz, world))
				{
					const auto ao = GetAo(x - 1, y, z, wx - 1, wz, world, X_PLANE);
					const int flip = ao[3] + ao[1] > ao[0] + ao[2];

					uInt v0 = PackData(x, y + 1, z + 1, voxelID, LEFT_FACE, ao[3], flip);
					uInt v1 = PackData(x, y    , z + 1, voxelID, LEFT_FACE, ao[2], flip);
					uInt v2 = PackData(x, y    , z    , voxelID, LEFT_FACE, ao[1], flip);
					uInt v3 = PackData(x, y + 1, z    , voxelID, LEFT_FACE, ao[0], flip);

					if (flip)
						vertData.insert(vertData.end(), { v1, v2, v3, v1, v3, v0 });
					else
						vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// front face
				if (CHECK_FRONT && IsVoid(x, y, z + 1, wx, wz + 1, world))
				{
					const auto ao = GetAo(x, y, z + 1, wx, wz + 1, world, Z_PLANE);
					const int flip = ao[3] + ao[1] > ao[0] + ao[2];

					uInt v0 = PackData(x + 1, y + 1, z + 1, voxelID, FRONT_FACE, ao[0], flip);
					uInt v1 = PackData(x + 1, y    , z + 1, voxelID, FRONT_FACE, ao[1], flip);
					uInt v2 = PackData(x    , y    , z + 1, voxelID, FRONT_FACE, ao[2], flip);
					uInt v3 = PackData(x    , y + 1, z + 1, voxelID, FRONT_FACE, ao[3], flip);

					if (flip)
						vertData.insert(vertData.end(), { v1, v2, v3, v1, v3, v0 });
					else
						vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// back face
				if (CHECK_BACK && IsVoid(x, y, z - 1, wx, wz - 1, world))
				{
					const auto ao = GetAo(x, y, z - 1, wx, wz - 1, world, Z_PLANE);
					const int flip = ao[3] + ao[1] > ao[0] + ao[2];

					uInt v0 = PackData(x,     y + 1, z, voxelID, BACK_FACE, ao[3], flip);
					uInt v1 = PackData(x    , y    , z, voxelID, BACK_FACE, ao[2], flip);
					uInt v2 = PackData(x + 1, y    , z, voxelID, BACK_FACE, ao[1], flip);
					uInt v3 = PackData(x + 1, y + 1, z, voxelID, BACK_FACE, ao[0], flip);

					if (flip)
						vertData.insert(vertData.end(), { v1, v2, v3, v1, v3, v0 });
					else
						vertData.insert(vertData.end(), { v0, v1, v2, v0, v2, v3 });
				}
			}
		}
	}

	return vertData;
}


