#include "Button.h"

Button::Button(float x, float y, float w, float h, string t, function<void()> callback) : rect{ x, y, w, h }, text(t), onClick(callback) {}

void Button::Update()
{
    Vector2 mousePos = GetMousePosition();
    isHovered = CheckCollisionPointRec(mousePos, rect);

    if (isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (onClick) onClick();
    }
}

void Button::Draw()
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
