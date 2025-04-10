#pragma once
#include <vector>
#include <string>
#include "PIconButton.h"
#include "PConstants.h"

struct PStepByStepMenu {
    Rectangle background;
    PIconButton skipBackward;
    PIconButton undo;
    PIconButton play;
    PIconButton redo;
    PIconButton skipForward;

    PStepByStepMenu(void);
    PStepByStepMenu(Vector2 pos, Vector2 size); // initialize with parameters: using Vector2

    void prepare(void);
    void draw(void);
};