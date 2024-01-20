#include "Engine.h"

#include <string>

#include "Window.h"

Engine::Engine()
    : player({ 0.0f, 0.0f, 2.0f }), scene(player)
{
    Window::Initialize();
    scene.Initialize();
}

Engine::~Engine()
{
    Window::Terminate();
}

void Engine::Run()
{
    while (Window::IsOpen())
    {
        Window::ProcessEvents();

        Update_dt();
        Update();
        Render();
    }
}

void Engine::Update()
{
    scene.Update(dt);
}

void Engine::Render()
{
    Window::Clear();
    
    scene.Render();

    Window::Flip();
}

void Engine::Update_dt()
{
    static double prevTime{ 0.0 };

    double now = Window::GetTime();

    dt = (float)(now - prevTime);
    prevTime = now;

    std::string fps = std::to_string(1.0f / dt);
    Window::SetTitle(fps.c_str());
}
