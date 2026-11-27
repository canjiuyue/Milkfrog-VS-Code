#include <iostream>

#include "MenuScene.h"
#include "SceneManager.h"

using namespace std;

MenuScene::MenuScene(SceneManager* sm) : manager(sm) {}

void MenuScene::OnEnter()
{
    cout << "MenuScene Loaded" << endl;
    buttons.clear();

    float btnWidth = 300;
    float btnHeight = 60;
    float startX = (1200 - btnWidth) / 2;
    float startY = 400;
    float gap = 80;

    buttons.emplace_back(startX, startY, btnWidth, btnHeight, "Start", [this]() { m_switch_to_character_selection = true; });
    buttons.emplace_back(startX, startY + gap, btnWidth, btnHeight, "Load", [this]() { m_switch_to_load = true; });
    buttons.emplace_back(startX, startY + gap * 2, btnWidth, btnHeight, "Options",[this]() { m_switch_to_options = true; });
    buttons.emplace_back(startX, startY + gap * 3, btnWidth, btnHeight, "Quit", []() { CloseWindow(); });
}

void MenuScene::Update(float dt)
{
    for (auto& btn : buttons)
    {
        btn.Update();
    }

    if (m_switch_to_character_selection)
    {
        manager->SwitchTo(SceneName::CharacterSelection);
        m_switch_to_character_selection = false;
    }
    else if (m_switch_to_load)
    {
        manager->SwitchTo(SceneName::Load);
        m_switch_to_load = false;
    }
    else if (m_switch_to_options)
    {
        manager->SwitchTo(SceneName::Options);
        m_switch_to_options = false;
    }
}

void MenuScene::Draw()
{
    string t = "Touhou Red Magic Castle";
    int w = MeasureText(t.c_str(), 60);
    DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);

    for (auto& btn : buttons)
    {
        btn.Draw();
    }
}

void MenuScene::OnExit() {}
