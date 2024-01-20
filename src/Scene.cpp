#include "Scene.h"

#include "Player.h"

Scene::Scene(Player& player)
    : player(player)
{
}

void Scene::Initialize()
{
    std::vector<Vertex> vertices{
        Vertex{{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        Vertex{{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        Vertex{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        Vertex{{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}
    };

    std::vector<unsigned int> indices{
        0, 1, 2,
        0, 2, 3
    };

    meshes.emplace_back(vertices, indices);

    shader.Load("default");
    texture.Load("test.png");

    shader.Activate();
    shader.SetTexture(texture, "u_tex0");
    texture.Bind();
}

void Scene::Update(float dt)
{
    player.Update(dt);
    shader.SetCamMat(player.GetMatrix());
}

void Scene::Render()
{
    for (const auto& mesh : meshes)
        mesh.Render();
}
