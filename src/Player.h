#pragma once

#include "Camera.h"

class Player : public Camera
{
public:
	Player() = default;
	Player(const glm::vec3& pos);

	void Update(float dt);

private:
	void Movement(float dt);
};

