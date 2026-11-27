#include "SceneManager.h"

int SceneManager::check() { return sceneDict.size(); }

void SceneManager::RegisterScene(const SceneName& name, Scene* scene)
{
    sceneDict[name] = scene;
}

bool SceneManager::SwitchTo(const SceneName& name)
{
    auto findIt = sceneDict.find(name);
    if (findIt == sceneDict.end())
    {
        return false;
    }
    if (currentScene != nullptr)
    {
        currentScene->OnExit();
    }
    currentScene = findIt->second;
    currentScene->OnEnter();
    return true;
}

void SceneManager::Update(float dt)
{
    if (currentScene)
        currentScene->Update(dt);
}

void SceneManager::Draw()
{
    if (currentScene)
        currentScene->Draw();
}
