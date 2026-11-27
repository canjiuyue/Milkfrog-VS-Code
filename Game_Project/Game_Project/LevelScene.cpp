#include <iostream>

#include "LevelScene.h"
#include "SceneManager.h"

using namespace std;

LevelScene::LevelScene(SceneManager* sm) : manager(sm) {}

void LevelScene::OnEnter()
{
    cout << "Level Selection" << endl;
    buttons.clear();

    float btnWidth = 300;
    float btnHeight = 60;
    float startX = (1200 - btnWidth) / 2;
    float startY = 600;
    float gap = 100;

    buttons.emplace_back(startX, startY, btnWidth, btnHeight, "Level 1", [this]() { m_switch_to_level_1 = true; });
    buttons.emplace_back(startX, startY + gap, btnWidth, btnHeight, "Level 2", [this]() {  m_switch_to_level_2 = true; });
    buttons.emplace_back(startX, startY + gap * 2, btnWidth, btnHeight, "Level 3", [this]() { m_switch_to_level_3 = true; });
    buttons.emplace_back(50, 50, 200, 50, "Back", [this]() { m_switch_to_character = true; });
}

void LevelScene::Update(float dt)
{
    for (auto& btn : buttons)
    {
        btn.Update();
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        m_switch_to_character = true;
    }

    if (m_switch_to_level_1)
    {
        manager->SwitchTo(SceneName::Level1);
        m_switch_to_level_1 = false;
    }

    if (m_switch_to_level_2)
    {
        manager->SwitchTo(SceneName::Level2);
        m_switch_to_level_2 = false;
    }

    if (m_switch_to_level_3)
    {
        manager->SwitchTo(SceneName::Level3);
        m_switch_to_level_3 = false;
    }

    if (m_switch_to_character)
    {
        manager->SwitchTo(SceneName::CharacterSelection);
        m_switch_to_character = false;
    }
}

void LevelScene::Draw()
{
    string t = "Select Level...";
    int w = MeasureText(t.c_str(), 60);
    DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);

    for (auto& btn : buttons)
    {
        btn.Draw();
    }
}
