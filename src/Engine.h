#pragma once

#include "Scene.h"
#include "Player.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

private:
	Player player;
	Scene scene;

	float dt{ 0.016f };

	void Update();
	void Render();

	void Update_dt();
};

