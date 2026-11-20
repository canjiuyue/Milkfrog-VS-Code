#include <iostream>
#include <vector>
#include <string>
#include <raylib.h>
#include <functional>

using namespace std;

enum class SceneName
{
    None, Menu, CharacterSelection, Load, Options
};

class Scene//��Ϸ��������
{
public:
    virtual ~Scene() = default;
    virtual void OnEnter() {}//�������أ���ʼ�������ڵ�Ԫ��
    virtual void Update(float dt) {}//�����߼����£��������֡��Ӱ����߼�
    virtual void Draw() {}//������Ⱦ������Ԫ��
    virtual void OnExit() {}//�����˳��ص���������Դ
};

class SceneManager//����������
{
private:
    unordered_map<SceneName, Scene*>sceneDict;
    Scene* currentScene = nullptr;
public:
    void RegisterScene(const SceneName& name, Scene* scene)//ע�᳡��
    {
        sceneDict[name] = scene;
    }

    bool SwitchTo(const SceneName& name)//ͨ�����������л�����
    {
        auto findIt = sceneDict.find(name);
        if (findIt == sceneDict.end())
        {
            //cout << "not find scene" << name << endl;
            return false;
        }
        if (currentScene != nullptr)//�ɳ����˳�
        {
            currentScene->OnExit();
        }
        currentScene = findIt->second;//�³�������
        currentScene->OnExit();
        return true;
    }

    void Update(float dt)//���µ�ǰ����
    {
        if (currentScene)
            currentScene->Update(dt);
    }

    void Draw()//��Ⱦ��ǰ����
    {
        if (currentScene)
            currentScene->Draw();
    }
};

class MenuScene;
class CharacterSelectionScene;
class LoadScene ;
class OptionsScene;

class Button//UI������ť
{
public:
    Rectangle rect;//�洢��ť��λ�úʹ�С
    string text;//��ť����ʾ���ı�
    function<void()> onClick;//��ť�����ʱ�����Ļص�����
    bool isHovered = false;//�������Ƿ���ͣ�ڰ�ť��

    Button(float x, float y, float w, float h, string t, function<void()> callback) : rect{ x, y, w, h }, text(t), onClick(callback) {}

    void Update()//���°�ť״̬
    {
        Vector2 mousePos = GetMousePosition();
        isHovered = CheckCollisionPointRec(mousePos, rect);

        if (isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (onClick) onClick();
        }
    }

    void Draw()//���ư�ť
    {
        cout << "BTN\n";
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
class MenuScene : public Scene//���˵�����
{
private:
    vector<Button> buttons;
    bool m_switch_to_character_selection = false;
    bool m_switch_to_load = false;
    bool m_switch_to_options = false;
    SceneManager* manager;
public:
    MenuScene(SceneManager* sm) :manager(sm) {}
    void OnEnter() override
    {
        cout << "MenuScene Loaded" << endl;
        buttons.clear();

        bool m_switch_to_character_selection = false;
        bool m_switch_to_load = false;
        bool m_switch_to_options = false;

        float btnWidth = 300;
        float btnHeight = 60;
        float startX = (1200 - btnWidth) / 2;
        float startY = 400;
        float gap = 80;

        buttons.emplace_back(startX, startY, btnWidth, btnHeight, "Start Game", [this, &m_switch_to_character_selection]() { m_switch_to_character_selection = true; });
        buttons.emplace_back(startX, startY + gap, btnWidth, btnHeight, "Select Save File", [this, &m_switch_to_load]() {m_switch_to_load = true; });
        buttons.emplace_back(startX, startY + gap * 2, btnWidth, btnHeight, "Game Settings", [this, &m_switch_to_options]() { m_switch_to_options = true; });
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

    void Draw() override//������Ϸ��������а�ť
    {
        string t = "Touhou Red Magic Castle";
        int w = MeasureText(t.c_str(), 60);
        DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);

        for (auto& btn : buttons)
        {
            btn.Draw();
        }
    }

    void OnExit() override
    {
        buttons.clear();
    }
};
class CharacterSelectionScene :public Scene//��ɫѡ�񳡾�
{
private:
    bool m_switchtoselect = false;
    vector<Button>buttons;
public:
    void OnEnter() override
    {
        cout << "Character Selection" << endl;
        buttons.clear();

        float btnWidth = 300;
        float btnHeight = 60;
        float startX = (1200 - btnWidth) / 2;
        float startY = 900;
        float gap = 100;
        buttons.emplace_back(
            startX, startY, btnWidth, btnHeight, "Confirm",
            [this]() { m_switchtoselect = true; });

        buttons.emplace_back(
            startX - gap, startY, btnWidth, btnHeight, "Last", []() {cout << "Clicked Last" << endl; }
        );

        buttons.emplace_back(
            startX + gap, startY, btnWidth, btnHeight, "Next", []() {cout << "Clicked Next" << endl; }
        );
    }

    void Update(float dt) override
    {
        for (auto& btn : buttons)
        {
            btn.Update();
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            m_switchtoselect = true;
        }
    }

    void Draw() override//������Ϸ��������а�ť
    {
        string t = "Select character...";
        int w = MeasureText(t.c_str(), 60);
        DrawText(t.c_str(), (1200 - w) / 2, 200, 60, RED);

        for (auto& btn : buttons)
        {
            btn.Draw();
        }
    }

    //Scene* Next()
    //{
    //    if (m_switchtoselect)
    //    {
    //        m_switchtoselect = false; // ���ñ�־
    //        return &Title;           // �������˵�
    //    }
    //    return nullptr; // û���л�����
    //}

};
class LoadScene: public Scene{};
class OptionsScene : public Scene {};
static SceneManager SM;


//Menu,CharacterSelection,Load,Options
MenuScene Menu(&SM);
CharacterSelectionScene CharacterSelection;
LoadScene Load;
OptionsScene Options;





int main()
{
    SetTraceLogLevel(LOG_ALL);
    SM.RegisterScene(SceneName::Menu, &Menu);
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