#pragma once

class Scene
{
public:
    virtual ~Scene();
    virtual void OnEnter() {}
    virtual void Update(float dt) {}
    virtual void Draw() {}
    virtual void OnExit() {}
};
