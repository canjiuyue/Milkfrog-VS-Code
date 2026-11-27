#include <iostream>

#include "OptionsScene.h"
#include "SceneManager.h"

using namespace std;

OptionsScene::OptionsScene(SceneManager* sm) : manager(sm) {}

void OptionsScene::OnEnter()
{
    cout << "Options Scene Entered" << endl;
    buttons.clear();

    buttons.emplace_back(50, 50, 200, 50, "Back", [this]() { m_switch_to_menu = true; });
}

void OptionsScene::Update(float dt)
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

void OptionsScene::Draw()
{
    string t = "Game Settings";
    int w = MeasureText(t.c_str(), 60);
    DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);

    for (auto& btn : buttons)
    {
        btn.Draw();
    }
}

void OptionsScene::OnExit() {}
