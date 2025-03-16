#include "../header/TEXTBOX.h"

void TEXTBOX::draw()
{
    DrawRectangle(rec.x, rec.y, rec.width, rec.height, recColor);
    DrawLineEx((Vector2){0, 0}, (Vector2){rec.width, 0}, this->upperline, outlineColor); // Draw upper line
    DrawLineEx((Vector2){0, rec.height}, (Vector2){rec.width, rec.height}, this->lowerline, outlineColor); // Draw lower line
    DrawLineEx((Vector2){0, 0}, (Vector2){0, rec.height}, this->leftline, outlineColor); // Draw left line
    DrawLineEx((Vector2){rec.width, 0}, (Vector2){rec.width, rec.height}, this->rightline, outlineColor); // Draw right line
    DrawText(text, (rec.width - MeasureText(text, fontSize))/2, (rec.height - fontSize)/2, fontSize, textColor);
}