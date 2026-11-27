#pragma once

#include <unordered_map>

#include "Scene.h"
#include "SceneName.h"

using namespace std;

class SceneManager
{
private:
    unordered_map<SceneName, Scene*> sceneDict;
    Scene* currentScene = nullptr;
public:
    int check();

    void RegisterScene(const SceneName& name, Scene* scene);

    bool SwitchTo(const SceneName& name);

    void Update(float dt);

    void Draw();
};
