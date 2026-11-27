#pragma once

#include <vector>

#include "Scene.h"
#include "Button.h"

using namespace std;

class SceneManager;

class LevelScene : public Scene
{
private:
    bool m_switch_to_character = false;
    bool m_switch_to_level_1 = false;
    bool m_switch_to_level_2 = false;
    bool m_switch_to_level_3 = false;
    vector<Button> buttons;
    SceneManager* manager;
public:
    LevelScene(SceneManager* sm);

    void OnEnter() override;

    void Update(float dt) override;

    void Draw() override;
};
