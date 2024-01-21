#pragma once

#include <vector>

#include "World.h"
#include "Shader.h"
#include "Texture.h"

class Player;

class Scene
{
public:
	Scene(Player& player);

	void Initialize();

	void Update(float dt);
	void Render();

private:
	Player& player;
	World world;
};

