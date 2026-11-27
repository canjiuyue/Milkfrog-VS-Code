#pragma once

#include <vector>

#include "Scene.h"
#include "Button.h"

using namespace std;

class SceneManager;

class OptionsScene : public Scene
{
private:
    bool m_switch_to_menu = false;
    vector<Button> buttons;
    SceneManager* manager;
public:
    OptionsScene(SceneManager* sm);

    void OnEnter() override;

    void Update(float dt) override;

    void Draw() override;

    void OnExit() override;
};
