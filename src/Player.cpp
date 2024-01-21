#include "Player.h"

#include <GLFW/glfw3.h>

#include "Window.h"

Player::Player(const glm::vec3& pos)
	: Camera(pos)
{
}

void Player::Update(float dt)
{
	Movement(dt);
	UpdateMatrix();
}

void Player::Movement(float dt)
{
    const float step = 40.0f * dt;

    if (Window::IsKeyPressed(GLFW_KEY_W))  MoveForward(step);
    if (Window::IsKeyPressed(GLFW_KEY_S))  MoveBackward(step);
    if (Window::IsKeyPressed(GLFW_KEY_A))  MoveLeft(step);
    if (Window::IsKeyPressed(GLFW_KEY_D))  MoveRight(step);
    if (Window::IsKeyPressed(GLFW_KEY_SPACE))         MoveUp(step);
    if (Window::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))  MoveDown(step);

    double mx, my, cx, cy, sx, sy;
    Window::GetCursorPosition(&mx, &my);
    Window::GetWindowCenter(&cx, &cy);
    Window::GetWindowSize(&sx, &sy);

    float rotX = (float)((my - cy) / sy) * 1000.0f * dt;
    float rotY = (float)((mx - cx) / sx) * 1000.0f * dt;

    RotateX(-rotX);
    RotateY(-rotY);

    Window::SetCursorToCenter();
}
