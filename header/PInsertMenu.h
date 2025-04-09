#pragma once
#include "PSwitchBox.h"
#include "PInputBox.h"
#include "PConstants.h"

struct PInsertMenu {
    /// I. Variables
    // Cordinates and sizes
    float x, y, width, height;

    /* The "Mode" Box
    Has three modes: "Head" - insert at head, "Tail" - insert at tail,
    "Specified position" - insert at user specified position
    */
    PSwitchBox Mode;

    // "GO" Box: takes user requests
    PTitleBox GO;

    /* currentMode
        0 - Head mode
        1 - Tail mode
        2 - Specified position mode
    */
    int currentMode;
    enum ModeID {
        Head, // 0
        Tail, // 1
        SpecifiedPosition // 2
    };

    // Head insert mode variable
    PInputBox headInputBox;

    // Tail insert mode variable
    PInputBox tailInputBox;

    // Specified position insert mode variable
    PInputBox specifiedPositionInputBox;
    PInputBox specifiedValueInputBox;

    /// II. Constructors
    PInsertMenu(void);
    PInsertMenu(float x, float y, float width, float height);
    PInsertMenu(Vector2 pos, Vector2 size);

    /// III. Functions

    // Draw function
    void draw(void);

    // Update function
    /*
    @brief return user's request in format of vector of strings
    Mode = Head: return {"head", value}
    Mode = Tail: return {"tail", value}
    Mode = SpecifiedPosition: return {"specified", position, value}
    */
    vector<string> update(void);
};