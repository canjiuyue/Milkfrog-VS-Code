#include <iostream>

#include "LoadScene.h"
#include "SceneManager.h"

using namespace std;

LoadScene::LoadScene(SceneManager* sm) : manager(sm) {}

void LoadScene::OnEnter()
{
    cout << "Load Selection" << endl;
    buttons.clear();

    buttons.emplace_back(50, 50, 200, 50, "Back", [this]() { m_switch_to_menu = true; });
}

void LoadScene::Update(float dt)
{
    for (auto& btn : buttons)
    {
        btn.Update();
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        m_switch_to_menu = true;
    }

    if (m_switch_to_menu)
    {
        manager->SwitchTo(SceneName::Menu);
        m_switch_to_menu = false;
    }
}

void LoadScene::Draw()
{
    string t = "Select Load...";
    int w = MeasureText(t.c_str(), 60);
    DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);

    for (auto& btn : buttons)
    {
        btn.Draw();
    }
}

void LoadScene::OnExit() {}
