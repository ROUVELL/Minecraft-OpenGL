#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowCallbacks.h"

GLFWwindow* Window::instance = nullptr;
int Window::width = 1200;
int Window::height = 900;
int Window::halfWidth = Window::width / 2;
int Window::halfHeight = Window::height / 2;

bool Window::IsOpen()
{
    return !glfwWindowShouldClose(Window::instance);
}

bool Window::IsKeyPressed(int key)
{
    return glfwGetKey(Window::instance, key);
}

bool Window::IsMouseKeyPressed(int key)
{
    return glfwGetMouseButton(Window::instance, key);
}

double Window::GetTime()
{
    return glfwGetTime();
}

void Window::GetCursorPosition(double* mx, double* my)
{
    glfwGetCursorPos(Window::instance, mx, my);
}

void Window::GetWindowCenter(double* px, double* py)
{
    *px = (double)Window::halfWidth;
    *py = (double)Window::halfHeight;
}

void Window::GetWindowSize(double* sx, double* sy)
{
    *sx = (double)Window::width;
    *sy = (double)Window::height;
}

void Window::GetWindowSize(int* sx, int* sy)
{
    *sx = Window::width;
    *sy = Window::height;
}

void Window::SetTitle(const char* title)
{
    glfwSetWindowTitle(Window::instance, title);
}

void Window::SetCursorPosition(int mx, int my)
{
    glfwSetCursorPos(Window::instance, (double)mx, (double)my);
}

void Window::SetCursorToCenter()
{
    glfwSetCursorPos(Window::instance, (double)Window::halfWidth, (double)Window::halfHeight);
}

void Window::SetCursorVisible()
{
    glfwSetInputMode(Window::instance, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::SetCursorDisabled()
{
    glfwSetInputMode(Window::instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::Initialize(Engine* engine)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = NULL;
    /*if (false)
    {
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

        w = mode->width;
        h = mode->height;
    }*/

    GLFWwindow* window = glfwCreateWindow(Window::width, Window::height, "Minecraft OpengGL", monitor, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return;
    }

    glfwSetWindowUserPointer(window, engine);

    glfwSetKeyCallback(window, KeyboardCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetWindowSizeCallback(window, WindowSizeCallback);
    glfwSetWindowCloseCallback(window, WindowCloseCallback);
    glfwSetErrorCallback(ErrorCallback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    gladLoadGL();

    glViewport(0, 0, Window::width, Window::height);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    Window::instance = window;

    Window::SetCursorToCenter();
    Window::SetCursorDisabled();
}

void Window::Terminate()
{
    glfwDestroyWindow(Window::instance);
    glfwTerminate();

    Window::instance = nullptr;
}

void Window::ProcessEvents()
{
    glfwPollEvents();
}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Flip()
{
    glfwSwapBuffers(Window::instance);
}
