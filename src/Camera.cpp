#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

constexpr glm::vec3 UP{ 0.0f, 1.0f, 0.0f };
constexpr glm::vec3 DOWN{ 0.0f, -1.0f, 0.0f };

const glm::mat4 PROJ_MATRIX = glm::perspective(glm::radians(60.0f), 1200.0f / 900.0f, 0.1f, 1000.0f);


Camera::Camera()
	: position{ 0.0f }
{
	UpdateMatrix();
}

Camera::Camera(const glm::vec3& pos)
	: position{ pos }
{
	UpdateMatrix();
}

void Camera::MoveForward(float value)
{
	position += direction * value;
}

void Camera::MoveBackward(float value)
{
	position -= direction * value;
}

void Camera::MoveRight(float value)
{
	position += glm::normalize(glm::cross(direction, UP)) * value;
}

void Camera::MoveLeft(float value)
{
	position += glm::normalize(glm::cross(direction, DOWN)) * value;
}

void Camera::MoveUp(float value)
{
	position += UP * value;
}

void Camera::MoveDown(float value)
{
	position += DOWN * value;
}

void Camera::RotateX(float angle)
{
	const glm::vec3 newDir = glm::rotate(direction, glm::radians(angle), glm::normalize(glm::cross(direction, UP)));

	if (!(glm::angle(newDir, UP) <= glm::radians(5.0f) || glm::angle(newDir, DOWN) <= glm::radians(5.0f)))
		direction = newDir;
}

void Camera::RotateY(float angle)
{
	direction = glm::rotate(direction, glm::radians(angle), UP);
}

void Camera::UpdateMatrix()
{
	matrix = PROJ_MATRIX * glm::lookAt(position, position + direction, UP);
}
