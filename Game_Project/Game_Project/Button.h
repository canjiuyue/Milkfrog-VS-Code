#pragma once

#include <functional>
#include <string>

#include <raylib.h>

using namespace std;

class Button
{
public:
    Rectangle rect;
    string text;
    function<void()> onClick;
    bool isHovered = false;

    Button(float x, float y, float w, float h, string t, function<void()> callback);

    void Update();

    void Draw();
};
