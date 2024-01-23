#include "Engine.h"

#include <iostream>
#include <string>

#include "Window.h"

Engine::Engine()
    : player({ WORLD_XZ_CENTER, CHUNK_HEIGHT + 2, WORLD_XZ_CENTER}),
    world(player)
{
    Window::Initialize();
    world.Generate();
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
    player.Update(dt);
    world.Update();
}

void Engine::Render()
{
    Window::Clear();
    
    world.Render();

    Window::Flip();
}

void Engine::Update_dt()
{
    static float prevTime = 0.0;

    float now = (float)(Window::GetTime());

    dt = now - prevTime;
    prevTime = now;
    
    const std::string fps = std::to_string(1.0f / dt);
    Window::SetTitle(fps.c_str());
}
