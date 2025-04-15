#pragma once
#include <raylib.h>
#include <cmath>
#include <string> // Add string include
#include "PTitleBox.h" // Assuming PTitleBox is the base or related
#include "PConstants.h"

using namespace std; // Add using namespace std

struct DInputBox : public PTitleBox { // Assuming PTitleBox is the base
    // ... (BlinkingCursor struct definition) ...
     struct BlinkingCursor {
        Vector2 pos;
        int height;

        BlinkingCursor(void);
        BlinkingCursor(Vector2 pos, int height);
        void draw(void);
        void setX(int x);
    };

    BlinkingCursor cursor;
    bool isChosen;
    string text; // Use std::string

    DInputBox(void);
    DInputBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, string name, int nameSize);
    void draw(void);
    void DrawInputSymbol(void); // ADDED BACK declaration
    void update(void);
    bool hasContent(void) const;
    string extract(void); // Use std::string
    void changeTitle(string newTitle); // Use std::string
};