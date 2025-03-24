#include "../header/HOBJECT.h"

void TextBox::draw()
{
    DrawRectangle(rec.x, rec.y, rec.width, rec.height, recColor);
    DrawRectangleLinesEx(rec, thick, outlineColor);
    DrawText(text, rec.x + (rec.width - MeasureText(text, fontSize))/2, rec.y + (rec.height - fontSize)/2, fontSize, textColor);
}

void NavigateButton::draw()
{
    DrawTextureEx(img, Vector2{rec.x, rec.y}, rotation, scale, color);
}