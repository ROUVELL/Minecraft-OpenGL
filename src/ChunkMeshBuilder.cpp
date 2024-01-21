#include "ChunkMeshBuilder.h"

#include <vector>

#include "Chunk.h"
#include "World.h"

constexpr glm::uint8 TOP_FACE =    0;
constexpr glm::uint8 BOTTOM_FACE = 1;
constexpr glm::uint8 RIGHT_FACE =  2;
constexpr glm::uint8 LEFT_FACE =   3;
constexpr glm::uint8 FRONT_FACE =  4;
constexpr glm::uint8 BACK_FACE =   5;

inline bool IsVoid(const World& world, int vx, int vy, int vz, int wx, int wy, int wz)
{
	const int cx = wx / CHUNK_SIZE - (wx < 0 ? 1 : 0);
	const int cy = wy / CHUNK_SIZE - (wy < 0 ? 1 : 0);
	const int cz = wz / CHUNK_SIZE - (wz < 0 ? 1 : 0);

	const Chunk* chunk_ptr = world.GetChunkAt(cx, cy, cz);

	if (chunk_ptr == nullptr)
		return true;

	if (chunk_ptr->At((vx + CHUNK_SIZE) % CHUNK_SIZE, (vy + CHUNK_SIZE) % CHUNK_SIZE, (vz + CHUNK_SIZE) % CHUNK_SIZE))
		return false;

	return true;
};

void BuildChunkMesh(Chunk& chunk, const World& world)
{
	std::vector<Vertex> vertices;

	const glm::ivec3 chunkPos = chunk.GetPosition();

	for (int y = 0; y < CHUNK_SIZE; ++y)
	{
		const int wy = y + chunkPos.y * CHUNK_SIZE;

		for (int z = 0; z < CHUNK_SIZE; ++z)
		{
			const int wz = z + chunkPos.z * CHUNK_SIZE;

			for (int x = 0; x < CHUNK_SIZE; ++x)
			{
				const glm::uint8 voxelID = chunk.At(x, y, z);

				if (!voxelID)
					continue;

				const int wx = x + chunkPos.x * CHUNK_SIZE;

				// top face
				if (IsVoid(world, x, y + 1, z, wx, wy + 1, wz))
				{
					Vertex v0{ { x + 1, y + 1, z     }, voxelID, TOP_FACE };
					Vertex v1{ { x + 1, y + 1, z + 1 }, voxelID, TOP_FACE };
					Vertex v2{ { x    , y + 1, z + 1 }, voxelID, TOP_FACE };
					Vertex v3{ { x    , y + 1, z     }, voxelID, TOP_FACE };

					vertices.insert(vertices.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// bootom face
				if (IsVoid(world, x, y - 1, z, wx, wy - 1, wz))
				{
					Vertex v0{ { x + 1, y, z + 1 }, voxelID, BOTTOM_FACE };
					Vertex v1{ { x + 1, y, z     }, voxelID, BOTTOM_FACE };
					Vertex v2{ { x    , y, z     }, voxelID, BOTTOM_FACE };
					Vertex v3{ { x,     y, z + 1 }, voxelID, BOTTOM_FACE };

					vertices.insert(vertices.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// right face
				if (IsVoid(world, x + 1, y, z, wx + 1, wy, wz))
				{
					Vertex v0{ { x + 1, y + 1, z     }, voxelID, RIGHT_FACE };
					Vertex v1{ { x + 1, y    , z     }, voxelID, RIGHT_FACE };
					Vertex v2{ { x + 1, y    , z + 1 }, voxelID, RIGHT_FACE };
					Vertex v3{ { x + 1, y + 1, z + 1 }, voxelID, RIGHT_FACE };

					vertices.insert(vertices.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// left face
				if (IsVoid(world, x - 1, y, z, wx - 1, wy, wz))
				{
					Vertex v0{ { x, y + 1, z + 1 }, voxelID, LEFT_FACE };
					Vertex v1{ { x, y    , z + 1 }, voxelID, LEFT_FACE };
					Vertex v2{ { x, y    , z     }, voxelID, LEFT_FACE };
					Vertex v3{ { x, y + 1, z     }, voxelID, LEFT_FACE };

					vertices.insert(vertices.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// front face
				if (IsVoid(world, x, y, z + 1, wx, wy, wz + 1))
				{
					Vertex v0{ { x + 1, y + 1, z + 1 }, voxelID, FRONT_FACE };
					Vertex v1{ { x + 1, y    , z + 1 }, voxelID, FRONT_FACE };
					Vertex v2{ { x    , y    , z + 1 }, voxelID, FRONT_FACE };
					Vertex v3{ { x    , y + 1, z + 1 }, voxelID, FRONT_FACE };

					vertices.insert(vertices.end(), { v0, v1, v2, v0, v2, v3 });
				}
				// back face
				if (IsVoid(world, x, y, z - 1, wx, wy, wz - 1))
				{
					Vertex v0{ { x,     y + 1, z }, voxelID, BACK_FACE };
					Vertex v1{ { x    , y    , z }, voxelID, BACK_FACE };
					Vertex v2{ { x + 1, y    , z }, voxelID, BACK_FACE };
					Vertex v3{ { x + 1, y + 1, z }, voxelID, BACK_FACE };

					vertices.insert(vertices.end(), { v0, v1, v2, v0, v2, v3 });
				}
			}
		}
	}
	
	chunk.mesh.Build(vertices);
}


