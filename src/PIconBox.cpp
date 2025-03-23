#include "../header/PIconBox.h"

PIconBox::PIconBox(void) {}

PIconBox::PIconBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, string iconDestination) :
    PBOX(pos, size, outThickness, inColor, outColor), iconDestination(iconDestination) {
}

PIconBox::~PIconBox(void) {
}

void PIconBox::draw(void) {
    PBOX::draw();
    // float scale = rec.y / icon.height;
    // DrawTexture(icon, 0, 0, WHITE);
    // DrawTextureV(icon, Vector2{0, 512}, WHITE);
    // DrawTextureEx(icon, Vector2{512, 0}, 0, 1.0f, WHITE);
    // DrawTextureEx(icon, Vector2{rec.x, rec.y}, 0.f, scale, WHITE);
}