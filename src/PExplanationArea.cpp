#include "../header/PExplanationArea.h"

PExplanationArea::PExplanationArea(void) :
    background({PConstants::PExplanationArea::pos.x, PConstants::PExplanationArea::pos.y, PConstants::PExplanationArea::size.x, PConstants::PExplanationArea::size.y}) {}

void PExplanationArea::update(void) {

}

void PExplanationArea::draw(void) {
    // Draw background
    Color color = PConstants::PExplanationArea::backgroundColor;
    DrawRectangleRec(background, color);
}