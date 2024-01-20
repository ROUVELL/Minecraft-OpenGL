#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	Camera(const glm::vec3& pos);

	const glm::vec3& GetPosition() const { return position; }
	const glm::vec3& GetDirection() const { return direction; }
	const glm::mat4& GetMatrix() const { return matrix; }

protected:
	glm::vec3 position;
	glm::vec3 direction{ 0.0f, 0.0f, -1.0f };

	void MoveForward(float value);
	void MoveBackward(float value);
	void MoveRight(float value);
	void MoveLeft(float value);
	void MoveUp(float value);
	void MoveDown(float value);

	void RotateX(float angle);
	void RotateY(float angle);

	void UpdateMatrix();

private:
	glm::mat4 matrix;
};

