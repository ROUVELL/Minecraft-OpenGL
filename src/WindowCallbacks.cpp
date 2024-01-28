#include "WindowCallbacks.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void KeyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(win, 1);

        else if (key == GLFW_KEY_F1) glfwSwapInterval(1);
        else if (key == GLFW_KEY_F2) glfwSwapInterval(0);
        else if (key == GLFW_KEY_F3) glEnable(GL_CULL_FACE);
        else if (key == GLFW_KEY_F4) glDisable(GL_CULL_FACE);
        else if (key == GLFW_KEY_F5) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else if (key == GLFW_KEY_F6) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else if (key == GLFW_KEY_F7) glCullFace(GL_BACK);
        else if (key == GLFW_KEY_F8) glCullFace(GL_FRONT);
    }
}

void MouseButtonCallback(GLFWwindow* win, int button, int action, int mods)
{
}

void WindowSizeCallback(GLFWwindow* win, int width, int height)
{
}

void WindowCloseCallback(GLFWwindow* win)
{
}

void ErrorCallback(int errorCode, const char* description)
{
    std::cout << "GLFW_ERROR: (" << errorCode << ") " << description << "\n";
}
