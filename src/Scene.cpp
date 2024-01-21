#include "Scene.h"

#include "Player.h"

Scene::Scene(Player& player)
    : player(player), world(player)
{
}

void Scene::Initialize()
{
    world.Generate();
}

void Scene::Update(float dt)
{
    player.Update(dt);
    world.Update();
}

void Scene::Render()
{
    world.Render();
}
