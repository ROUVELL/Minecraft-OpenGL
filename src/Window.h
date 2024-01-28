#pragma once

struct GLFWwindow;
class Engine;

class Window
{
public:
	Window() = delete;

	static bool IsInitialized() { return instance != nullptr; }
	static bool IsOpen();
	static bool IsKeyPressed(int key);
	static bool IsMouseKeyPressed(int key);

	static GLFWwindow* GetInstance() { return instance; }
	static double GetTime();
	static void GetCursorPosition(double* mx, double* my);
	static void GetWindowCenter(double* px, double* py);
	static void GetWindowSize(double* sx, double* sy);
	static void GetWindowSize(int* sx, int* sy);

	static void SetTitle(const char* title);
	static void SetCursorPosition(int mx, int my);
	static void SetCursorToCenter();
	static void SetCursorVisible();
	static void SetCursorDisabled();

	static void Initialize(Engine* engine);
	static void Terminate();
	static void ProcessEvents();
	static void Clear();
	static void Flip();

private:
	static GLFWwindow* instance;

	static int width, height, halfWidth, halfHeight;

};

