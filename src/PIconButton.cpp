#include "../header/PIconButton.h"

PIconButton::PIconButton(void) : icon() {}

PIconButton::PIconButton(Vector2 pos, Vector2 size, string directory) :
    icon(),
    pos(pos),
    size(size),
    directory(directory), 
    rec{pos.x, pos.y, size.x, size.y} {}

PIconButton::~PIconButton(void) {
    UnloadTexture(icon);
}

void PIconButton::prepare(void) {
    icon = LoadTexture(directory.c_str());
}

void PIconButton::draw(void) {
    const float scale = size.y / icon.height;
    if(isMove())
        DrawTextureEx(icon, pos, 0.f, scale, GRAY);
    else
        DrawTextureEx(icon, pos, 0.f, scale, WHITE);
}

bool PIconButton::isMove(void) {
    return CheckCollisionPointRec(GetMousePosition(), rec);
}

bool PIconButton::isClicked(void) {
    return CheckCollisionPointRec(GetMousePosition(), rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}