#pragma once

struct GLFWwindow;

void KeyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
void WindowSizeCallback(GLFWwindow* win, int width, int height);
void WindowCloseCallback(GLFWwindow* win);
void ErrorCallback(int errorCode, const char* description);
