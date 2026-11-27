#pragma once

#include <string>
#include <vector>

#include "Scene.h"
#include "Button.h"

using namespace std;

class SceneManager;

class PlaceholderLevelScene : public Scene
{
private:
    bool m_switch_to_level = false;
    vector<Button> buttons;
    SceneManager* manager;
    string title;
public:
    PlaceholderLevelScene(SceneManager* sm, const string& t);

    void OnEnter() override;

    void Update(float dt) override;

    void Draw() override;

    void OnExit() override;
};
