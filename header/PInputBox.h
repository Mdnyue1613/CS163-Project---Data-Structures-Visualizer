#pragma once
#include <raylib.h>
#include <cmath>
#include "PTitleBox.h"
#include "PConstants.h"

struct PInputBox : public PTitleBox {
    /*
    Box allow user to type text into it.
    When press "backspace" once, text delete the last character.

    When press "backspace" for a long time, multiple last characters are deleted. 
    The more time user presses, the more characters are deleted.
    */

    struct BlinkingCursor {
        /*
        When the box is chosen, a blinking line appears recording where new character will appear
        */
        Vector2 pos;
        int height;

        BlinkingCursor(void);
        BlinkingCursor(Vector2 pos, int height);
        void draw(void);
        void setX(int x);
    };

    BlinkingCursor cursor;
    bool isChosen;
    string text;

    PInputBox(void); // Initializer
    PInputBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, string name, int nameSize); // Initializer with parameters
    void draw(void);
    void DrawInputSymbol(void);
    void update(void);
    bool hasContent(void);
    string extract(void);
};