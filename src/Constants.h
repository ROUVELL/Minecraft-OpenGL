#pragma once

// chunk
constexpr int CHUNK_WIDTH = 16;
constexpr int CHUNK_HEIGHT = 96;
constexpr int H_CHUNK_WIDTH = CHUNK_WIDTH >> 1;
constexpr int H_CHUNK_HEIGHT = CHUNK_HEIGHT >> 1;
constexpr int CHUNK_AREA = CHUNK_WIDTH * CHUNK_WIDTH;
constexpr int CHUNK_VOLUME = CHUNK_AREA * CHUNK_HEIGHT;

// world
constexpr int WORLD_WIDTH = 10;
constexpr int H_WORLD_WIDTH = WORLD_WIDTH >> 1;
constexpr int WORLD_AREA = WORLD_WIDTH * WORLD_WIDTH;
constexpr int WORLD_XZ_CENTER = (H_WORLD_WIDTH * CHUNK_WIDTH) + H_CHUNK_WIDTH;
constexpr int WORLD_Y_CENTER = H_CHUNK_HEIGHT;
constexpr int WORLD_BORDER = CHUNK_WIDTH * WORLD_WIDTH - 1;

// faces
constexpr int TOP_FACE = 0;
constexpr int BOTTOM_FACE = 1;
constexpr int RIGHT_FACE = 2;
constexpr int LEFT_FACE = 3;
constexpr int FRONT_FACE = 4;
constexpr int BACK_FACE = 5;

// plane
constexpr int Y_PLANE = 1;
constexpr int X_PLANE = 2;
constexpr int Z_PLANE = 3;

// raycasting
constexpr float MAX_RAY_DIST = 8.0f;