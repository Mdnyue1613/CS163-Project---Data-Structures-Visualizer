#pragma once
#include <vector>
#include <string>
#include "PIconButton.h"
#include "PConstants.h"

/*
    Display step by step menu and take request from user:
        I. After initializing the window, use function "prepare()" to prepare the menu.
        II. To draw the step by step menu, use function "draw()".
        III. If user clicks on the button, function "getRequest()" returns a number representing the request:
            0 = No request
            1 = Skip backward
            2 = Undo
            3 = Play
            4 = Redo
            5 = Skip forward
*/

struct PStepByStepMenu {
    Rectangle background; // background rectangle
    PIconButton skipBackward; // skip backward button
    PIconButton undo; // undo button
    PIconButton play; // play button
    PIconButton redo; // redo button
    PIconButton skipForward; // skip forward button

    bool isOperating;
    int mode;

    enum requestID {
        NoRequest,
        SkipBackward,
        GoBackward,
        Play,
        GoForward,
        SkipForward
    };

    PStepByStepMenu(void);
    PStepByStepMenu(Vector2 pos, Vector2 size); // initialize with parameters: using Vector2

    void prepare(void);
    void update(void);
    void draw(void);
    int getRequest(void);
};