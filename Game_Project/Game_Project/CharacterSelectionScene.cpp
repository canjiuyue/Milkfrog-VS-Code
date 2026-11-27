#include <iostream>

#include "CharacterSelectionScene.h"
#include "SceneManager.h"

using namespace std;

CharacterSelectionScene::CharacterSelectionScene(SceneManager* sm) : manager(sm) {}

void CharacterSelectionScene::OnEnter()
{
    cout << "Character Selection" << endl;
    buttons.clear();

    float btnWidth = 300;
    float btnHeight = 60;
    float startX = (1200 - btnWidth) / 2;
    float startY = 900;
    float gap = 350;

    buttons.emplace_back(startX, startY, btnWidth, btnHeight, "Confirm", [this]() { m_switch_to_select = true; });
    buttons.emplace_back(startX - gap, startY, btnWidth, btnHeight, "Last", []() { cout << "Clicked Last" << endl; });
    buttons.emplace_back(startX + gap, startY, btnWidth, btnHeight, "Next", []() { cout << "Clicked Next" << endl; });
    buttons.emplace_back(50, 50, 200, 50, "Back", [this]() { m_switch_to_menu = true; });
}

void CharacterSelectionScene::Update(float dt)
{
    for (auto& btn : buttons)
    {
        btn.Update();
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        m_switch_to_menu = true;
    }

    if (m_switch_to_select)
    {
        cout << "Character Confirmed!" << endl;
        manager->SwitchTo(SceneName::Level);
        m_switch_to_select = false;
    }

    if (m_switch_to_menu)
    {
        manager->SwitchTo(SceneName::Menu);
        m_switch_to_menu = false;
    }
}

void CharacterSelectionScene::Draw()
{
    string t = "Select character...";
    int w = MeasureText(t.c_str(), 60);
    DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);

    for (auto& btn : buttons)
    {
        btn.Draw();
    }
}
