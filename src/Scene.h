#pragma once

#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

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

	Shader shader;
	Texture texture;
	std::vector<Mesh> meshes;
};

