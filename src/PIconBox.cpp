#include "../header/PIconBox.h"
#include "../header/PConstants.h"

PIconBox::PIconBox(void) : icon() {}

PIconBox::PIconBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, string iconDestination) :
    PBOX(pos, size, outThickness, inColor, outColor), 
    iconDestination(iconDestination) ,
    icon() {
}

PIconBox::~PIconBox(void) {
    UnloadTexture(icon);
}

void PIconBox::prepare(void) {
    icon = LoadTexture(iconDestination.c_str());
}

void PIconBox::draw(void) {
    PBOX::draw();
    float scale = min(PConstants::PIconBox::height / (float)icon.height, 
                    PConstants::PIconBox::width / (float)icon.width);
    // DrawTexture(icon, 0, 0, WHITE);
    // DrawTextureV(icon, Vector2{0, 512}, WHITE);
    DrawTextureEx(icon, Vector2{rec.x + (rec.width - icon.width * scale) / 2.f, 
        rec.y + (rec.height - icon.height * scale) / 2.f}, 0.f, scale, WHITE);
}