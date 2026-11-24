#include <iostream>
#include <vector>
#include <string>
#include <raylib.h>
#include <functional>
#include <unordered_map> 

using namespace std;

enum class SceneName
{
    None, Menu, CharacterSelection, Load, Options, Level,Level1,Level2,Leve3
};

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void OnEnter() {}
    virtual void Update(float dt) {}
    virtual void Draw() {}
    virtual void OnExit() {}
};

class SceneManager
{
private:
    unordered_map<SceneName, Scene*> sceneDict;
    Scene* currentScene = nullptr;
public:
    int check() { return sceneDict.size(); }

    void RegisterScene(const SceneName& name, Scene* scene)
    {
        sceneDict[name] = scene;
    }

    bool SwitchTo(const SceneName& name)
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

    void Update(float dt)
    {
        if (currentScene)
            currentScene->Update(dt);
    }

    void Draw()
    {
        if (currentScene)
            currentScene->Draw();
    }
};

class MenuScene;
class CharacterSelectionScene;
class LoadScene;
class OptionsScene;

class Button
{
public:
    Rectangle rect;
    string text;
    function<void()> onClick;
    bool isHovered = false;

    Button(float x, float y, float w, float h, string t, function<void()> callback) : rect{ x, y, w, h }, text(t), onClick(callback) {}

    void Update()
    {
        Vector2 mousePos = GetMousePosition();
        isHovered = CheckCollisionPointRec(mousePos, rect);

        if (isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (onClick) onClick();
        }
    }

    void Draw()
    {
        Color color = isHovered ? SKYBLUE : GRAY;
        float scale = isHovered ? 1.1f : 1.0f;

        float drawWidth = rect.width * scale;
        float drawHeight = rect.height * scale;
        float drawX = rect.x + (rect.width - drawWidth) / 2;
        float drawY = rect.y + (rect.height - drawHeight) / 2;

        DrawRectangleRec({ drawX, drawY, drawWidth, drawHeight }, color);

        int fontSize = 30;
        int textWidth = MeasureText(text.c_str(), fontSize);
        DrawText(text.c_str(),
            rect.x + (rect.width - textWidth) / 2,
            rect.y + (rect.height - fontSize) / 2,
            fontSize, WHITE);
    }
};

class MenuScene : public Scene
{
private:
    vector<Button> buttons;
    bool m_switch_to_character_selection = false;
    bool m_switch_to_load = false;
    bool m_switch_to_options = false;
    SceneManager* manager;
public:
    MenuScene(SceneManager* sm) : manager(sm) {}

    void OnEnter() override
    {
        cout << "MenuScene Loaded" << endl;
        buttons.clear();

        float btnWidth = 300;
        float btnHeight = 60;
        float startX = (1200 - btnWidth) / 2;
        float startY = 400;
        float gap = 80;

        buttons.emplace_back(startX, startY, btnWidth, btnHeight, "Start Game", [this]() { m_switch_to_character_selection = true; });
        buttons.emplace_back(startX, startY + gap, btnWidth, btnHeight, "Select Save File", [this]() { m_switch_to_load = true; });
        buttons.emplace_back(startX, startY + gap * 2, btnWidth, btnHeight, "Options", [this]() { m_switch_to_options = true; });
        buttons.emplace_back(startX, startY + gap * 3, btnWidth, btnHeight, "Quit", []() { CloseWindow(); });
    }

    void Update(float dt) override
    {
        for (auto& btn : buttons)
        {
            btn.Update();
        }

        if (m_switch_to_character_selection)
        {
            manager->SwitchTo(SceneName::CharacterSelection);
            m_switch_to_character_selection = false;
        }
        else if (m_switch_to_load)
        {
            manager->SwitchTo(SceneName::Load);
            m_switch_to_load = false;
        }
        else if (m_switch_to_options)
        {
            manager->SwitchTo(SceneName::Options);
            m_switch_to_options = false;
        }
    }

    void Draw() override
    {
        string t = "Touhou Red Magic Castle";
        int w = MeasureText(t.c_str(), 60);
        DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);

        for (auto& btn : buttons)
        {
            btn.Draw();
        }
    }

    void OnExit() override {}
};

class CharacterSelectionScene : public Scene
{
private:
    bool m_switch_to_select = false;
    bool m_switch_to_menu = false;
    vector<Button> buttons;
    SceneManager* manager;
public:
    CharacterSelectionScene(SceneManager* sm) : manager(sm) {}

    void OnEnter() override
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

    void Update(float dt) override
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

    void Draw() override
    {
        string t = "Select character...";
        int w = MeasureText(t.c_str(), 60);
        DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);

        for (auto& btn : buttons)
        {
            btn.Draw();
        }
    }
};

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
    LevelScene(SceneManager* sm) : manager(sm) {}

    void OnEnter() override
    {
        cout << "Level Selection" << endl;
        buttons.clear();

        float btnWidth = 300;
        float btnHeight = 60;
        float startX = (1200 - btnWidth) / 2;
        float startY = 600; 
        float gap = 100;    

        buttons.emplace_back(startX, startY, btnWidth, btnHeight, "Level 1", [this]() { m_switch_to_level_1 = true; });
        buttons.emplace_back(startX, startY + gap, btnWidth, btnHeight, "Level 2", [this]() { m_switch_to_level_2 = true; });
        buttons.emplace_back(startX, startY + gap * 2, btnWidth, btnHeight, "Level 3", [this]() { m_switch_to_level_3 = true; });
        buttons.emplace_back(50, 50, 200, 50, "Back", [this]() { m_switch_to_character = true; });
    }

    void Update(float dt) override
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
            cout << "Level 1 Confirmed!" << endl;
            m_switch_to_level_1 = false;
        }

        if (m_switch_to_level_2)
        {
            cout << "Level 2 Confirmed!" << endl;
            m_switch_to_level_2 = false;
        }

        if (m_switch_to_level_3)
        {
            cout << "Level 3 Confirmed!" << endl;
            m_switch_to_level_3 = false;
        }

        if (m_switch_to_character)
        {
            manager->SwitchTo(SceneName::CharacterSelection);
            m_switch_to_character = false;
        }
    }

    void Draw() override
    {
        string t = "Select Level...";
        int w = MeasureText(t.c_str(), 60);
        DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);

        for (auto& btn : buttons)
        {
            btn.Draw();
        }
    }
};

class LoadScene : public Scene
{
public:
    void OnEnter() override { cout << "Load Scene Entered" << endl; }
    void Update(float dt) override { if (IsKeyPressed(KEY_ESCAPE)) return; }
};

class OptionsScene : public Scene
{
public:
    void OnEnter() override { cout << "Options Scene Entered" << endl; }
    void Update(float dt) override { if (IsKeyPressed(KEY_ESCAPE)) return; }
};

static SceneManager SM;

MenuScene Menu(&SM);
CharacterSelectionScene CharacterSelection(&SM);
LevelScene Level(&SM);
LoadScene Load;
OptionsScene Options;

int main()
{
    SetTraceLogLevel(LOG_ALL);
    SM.RegisterScene(SceneName::Menu, &Menu);
    SM.RegisterScene(SceneName::CharacterSelection, &CharacterSelection);
    SM.RegisterScene(SceneName::Level, &Level); 
    SM.RegisterScene(SceneName::Load, &Load);
    SM.RegisterScene(SceneName::Options, &Options);

    InitWindow(1200, 1200, "Touhou Red Magic Castle");
    SetTargetFPS(60);

    SM.SwitchTo(SceneName::Menu);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        SM.Update(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        SM.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}