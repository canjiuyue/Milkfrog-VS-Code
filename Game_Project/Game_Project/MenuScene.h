#pragma once

#include <vector>

#include "Scene.h"
#include "Button.h"

using namespace std;

class SceneManager;

class MenuScene : public Scene
{
private:
    vector<Button> buttons;
    bool m_switch_to_character_selection = false;
    bool m_switch_to_load = false;
    bool m_switch_to_options = false;
    SceneManager* manager;
public:
    MenuScene(SceneManager* sm);

    void OnEnter() override;

    void Update(float dt) override;

    void Draw() override;

    void OnExit() override;
};
