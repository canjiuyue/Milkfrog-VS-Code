#include <iostream>

#include "PlaceholderLevelScene.h"
#include "SceneManager.h"

using namespace std;

PlaceholderLevelScene::PlaceholderLevelScene(SceneManager* sm, const string& t) : manager(sm), title(t) {}

void PlaceholderLevelScene::OnEnter()
{
    cout << title << " Entered" << endl;
    buttons.clear();

    buttons.emplace_back(50, 50, 200, 50, "Back", [this]() { m_switch_to_level = true; });
}

void PlaceholderLevelScene::Update(float dt)
{
    for (auto& btn : buttons)
    {
        btn.Update();
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        m_switch_to_level = true;
    }

    if (m_switch_to_level)
    {
        manager->SwitchTo(SceneName::Level);
        m_switch_to_level = false;
    }
}

void PlaceholderLevelScene::Draw()
{
    string t = title;
    int w = MeasureText(t.c_str(), 60);
    DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);
    const char* tip = "Gameplay goes here...";
    DrawText(tip, 400, 400, 30, WHITE);

    for (auto& btn : buttons)
    {
        btn.Draw();
    }
}

void PlaceholderLevelScene::OnExit() {}
