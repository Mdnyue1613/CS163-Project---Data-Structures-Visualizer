#include "../header/DInputBox.h"
#include <iostream>
#include <cstring> // For strcpy, strlen etc. if PTitleBox uses char[]
#include <string>  // For std::string operations
#include <raymath.h>
// --- PInputBox::BlinkingCursor Implementation ---
// ... (keep BlinkingCursor implementation as before) ...
DInputBox::BlinkingCursor::BlinkingCursor(void) {}

DInputBox::BlinkingCursor::BlinkingCursor(Vector2 pos, int height) :
    pos(Vector2{pos.x + PConstants::PCursor::leftSpace, pos.y}), height(height) {}

void DInputBox::BlinkingCursor::draw(void) {
    DrawLine(pos.x, pos.y, pos.x, pos.y + height, BLACK);
}

void DInputBox::BlinkingCursor::setX(int x) {
    pos.x = x;
}

// --- PInputBox Implementation ---
DInputBox::DInputBox(void) : isChosen(false) {}

DInputBox::DInputBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, string name, int nameSize) :
    PTitleBox(pos, size, outThickness, inColor, outColor, name, nameSize), // Call PTitleBox constructor
    cursor(pos, size.y),
    isChosen(false) {}

// ADDED BACK: Definition for the custom cursor drawing function
void DInputBox::DrawInputSymbol(void) {
    HideCursor(); // Hide system cursor when drawing the custom one
    int x = GetMouseX();
    int y = GetMouseY();
    // Clamp coordinates to prevent drawing off-screen (optional but good practice)
    x = Clamp(x, 0.0f, (float)GetScreenWidth() - PConstants::PCursor::width / 2.0f);
    y = Clamp(y, 0.0f, (float)GetScreenHeight() - PConstants::PCursor::height);

    DrawLine(x, y, x, y + PConstants::PCursor::height, BLACK); // Vertical line
    // Upper horizontal line
    DrawLine(x - PConstants::PCursor::width / 2, y, x + PConstants::PCursor::width / 2, y, BLACK);
    // Lower horizontal line
    DrawLine(x - PConstants::PCursor::width / 2, y + PConstants::PCursor::height, x + PConstants::PCursor::width / 2, y + PConstants::PCursor::height, BLACK);
}


// MODIFIED draw function to include custom cursor logic
void DInputBox::draw(void) {
    update(); // Update state first

    // Draw background and outline using base class method
    PBOX::draw(); // Assuming PBOX is the ultimate base with the rectangle drawing

    // Draw title or input text
    if (text.empty() && !isChosen) {
        int textWidth = MeasureText(title, titleSize); // Assuming title is still char[] from PTitleBox
        DrawText(title, rec.x + (rec.width - textWidth) / 2, rec.y + (rec.height - titleSize) / 2, titleSize, PConstants::PInputBox::titleColor);
    } else {
        DrawText(text.c_str(), rec.x + PConstants::PCursor::leftSpace, rec.y + (rec.height - titleSize) / 2, titleSize, PConstants::PInputBox::inputColor);
    }

    // --- MODIFIED CURSOR HANDLING ---
    if (isMove()) { // If mouse is hovering over the box
        DrawInputSymbol(); // Draw the custom cursor (which also hides the system one)
    } else {
        // Only show cursor if no other input element has focus (more robust)
        // For simplicity now, just ensure it shows when mouse moves out
         if (!isChosen) { // Show system cursor if outside AND not selected
             ShowCursor();
         } else {
             // If it IS chosen but mouse moved out, keep system cursor hidden
             // because the blinking cursor should be active inside.
             // We might still see the system cursor briefly if mouse moves fast.
         }
    }
    // --- END MODIFIED CURSOR HANDLING ---

    // Draw blinking cursor if chosen
    if (isChosen) {
        if (fmod(GetTime(), PConstants::PCursor::fullTime) < PConstants::PCursor::onTime)
            cursor.draw();
         // Ensure system cursor is hidden when blinking cursor is active
         HideCursor();
    } else {
         // If not chosen and mouse is not over it, ensure system cursor is shown
         if (!isMove()) {
             ShowCursor();
         }
    }
}


// MODIFIED update function to allow spaces and leading/trailing minus for list input
void DInputBox::update(void) {
     // Handle choosing/unchoosing the box
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (isMove()) {
            isChosen = true;
        } else {
            isChosen = false;
        }
    }

    if (isChosen) {
        // Get character input
        int inputKey = GetCharPressed();
        while (inputKey > 0) {
            // Allow digits, space, and minus under specific conditions
            if ( text.length() < PConstants::PLimit::maxInputLength + 50 ) // Increased limit for lists
            {
                if ((inputKey >= '0' && inputKey <= '9') || // Allow digits
                    (inputKey == KEY_SPACE && !text.empty() && text.back() != ' ') || // Allow space if not first/double
                    (inputKey == '-' && (text.empty() || text.back() == ' ')))      // Allow minus if first or after space
                {
                     // Prevent leading space
                     if (!(inputKey == KEY_SPACE && text.empty())) {
                          text.push_back((char)inputKey);
                     }
                }
            }
            inputKey = GetCharPressed(); // Get next char in the queue for this frame
        }

        // Handle backspace
        if (IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE)) {
            if (!text.empty()) {
                text.pop_back();
            }
        }

        // Update blinking cursor position
        cursor.setX(rec.x + PConstants::PCursor::leftSpace + MeasureText(text.c_str(), titleSize));
    }
}

// hasContent - Keep as is (with const)
bool DInputBox::hasContent(void) const{
    return !text.empty();
}

// extract - Keep as is
string DInputBox::extract(void) {
    string res = text;
    text.clear();
    isChosen = false;
    cursor.setX(rec.x + PConstants::PCursor::leftSpace);
    return res;
}

// changeTitle - Keep as is
void DInputBox::changeTitle(string newTitle) {
    if (newTitle.length() < 50) {
        strcpy(title, newTitle.c_str());
    } else {
        strncpy(title, newTitle.c_str(), 49);
        title[49] = '\0';
    }
}