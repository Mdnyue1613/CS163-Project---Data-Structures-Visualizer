#include "../header/PSlider.h"
#include "../header/PConstants.h"

PSlider::PSlider(void) {}
PSlider::PSlider(Vector2 pos, Vector2 size) {
    Slider::bar = Rectangle({pos.x, pos.y, size.x, size.y});
    Slider::thumb = Rectangle({pos.x - size.y, pos.y, size.y * 2, size.y});
    thumb.x = bar.x + bar.width / 2.f - thumb.width / 2.f;
}
void PSlider::update(void) {
    if(Slider::isClick && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        float toX = max(min(GetMousePosition().x, bar.x + bar.width), bar.x);
        thumb.x = toX - thumb.width / 2.f;
    }
    else if(CheckCollisionPointRec(GetMousePosition(), Slider::thumb)) {
        thumbColor = PConstants::PSlider::thumbHighlightColor;
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Slider::isClick = true;
        }
        else {
            Slider::isClick = false;
        }
    }
    else {
        Slider::isClick = false;
        thumbColor = PConstants::PSlider::thumbColor;
    }
}
void PSlider::draw(void) {
    Color barColor = PConstants::PSlider::barColor;
    DrawRectangleRounded(bar, 1, 10, barColor);
    DrawRectangleRounded(thumb, 1, 10, thumbColor);

    string text = "Speed: ";
    string speed = to_string(getPercentage()) + "x";
    float textWidth = MeasureText(text.c_str(), bar.height);
    DrawText(text.c_str(), bar.x - textWidth - 5.f, bar.y, bar.height, PConstants::PNode::informationTextColor);
    DrawText(speed.c_str(), thumb.x - textWidth / 2.f, bar.y - bar.height - 5.f, bar.height, PConstants::PNode::informationTextColor);
}
float PSlider::getPercentage(void) {
    return ((thumb.x + thumb.width / 2.f) - bar.x) / (bar.width / 2.f);
}