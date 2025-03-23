#include "../header/PIconBox.h"

PIconBox::PIconBox(void) {}

PIconBox::PIconBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, string iconDestination) :
    PBOX(pos, size, outThickness, inColor, outColor), iconDestination(iconDestination) {
}

PIconBox::~PIconBox(void) {
}

void PIconBox::draw(void) {
    PBOX::draw();
    Texture2D icon = LoadTexture(iconDestination.c_str());
    if (icon.id == 0) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    float scale = rec.y / icon.height;
    DrawTextureV(icon, Vector2{rec.x, rec.y}, WHITE);
    // DrawTextureEx(icon, Vector2{rec.x, rec.y}, 0.f, scale, WHITE);
    UnloadTexture(icon);
}