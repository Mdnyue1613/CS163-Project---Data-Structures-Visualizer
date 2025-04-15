#include "../header/PExplanationArea.h"

PExplanationArea::PExplanationArea(void) :
    background({PConstants::PExplanationArea::pos.x, PConstants::PExplanationArea::pos.y, PConstants::PExplanationArea::size.x, PConstants::PExplanationArea::size.y}) {}

void PExplanationArea::update(string text) {
    content = text;
}

void PExplanationArea::draw(void) {
    // Draw background
    Color color = PConstants::PExplanationArea::backgroundColor;
    DrawRectangleRec(background, color);

    // Draw text
    float posX = background.x + PConstants::PExplanationArea::spaceX;
    float posY = background.y + PConstants::PExplanationArea::spaceY;
    float fontSize = PConstants::PExplanationArea::fontSize;
    Color textColor = PConstants::PExplanationArea::textColor;
    DrawText(content.c_str(), posX, posY, fontSize, textColor);
}