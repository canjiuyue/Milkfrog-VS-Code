#include <iostream>

#include <raylib.h>

#include "SceneName.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "CharacterSelectionScene.h"
#include "LevelScene.h"
#include "LoadScene.h"
#include "OptionsScene.h"
#include "PlaceholderLevelScene.h"

using namespace std;

static SceneManager SM;

MenuScene Menu(&SM);
CharacterSelectionScene CharacterSelection(&SM);
LevelScene Level(&SM);
LoadScene Load(&SM);
OptionsScene Options(&SM);
PlaceholderLevelScene Level1(&SM, "Level 1");
PlaceholderLevelScene Level2(&SM, "Level 2");
PlaceholderLevelScene Level3(&SM, "Level 3");

int main()
{
    SetTraceLogLevel(LOG_ALL);
    SM.RegisterScene(SceneName::Menu, &Menu);
    SM.RegisterScene(SceneName::CharacterSelection, &CharacterSelection);
    SM.RegisterScene(SceneName::Level, &Level);
    SM.RegisterScene(SceneName::Load, &Load);
    SM.RegisterScene(SceneName::Options, &Options);
    SM.RegisterScene(SceneName::Level1, &Level1);
    SM.RegisterScene(SceneName::Level2, &Level2);
    SM.RegisterScene(SceneName::Level3, &Level3);

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
