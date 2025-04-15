#include "../header/PStepByStepMenu.h"

PStepByStepMenu::PStepByStepMenu(void) {}

PStepByStepMenu::PStepByStepMenu(Vector2 pos, Vector2 size) :
    background({pos.x, pos.y, size.x, size.y}) {
    Vector2 buttonSize{PConstants::PStepByStepMenu::iconWidth, PConstants::PStepByStepMenu::iconHeight};;
    Vector2 skipBackwardPos{pos.x + PConstants::PStepByStepMenu::skipBackwardCenter.x - buttonSize.x / 2, pos.y + PConstants::PStepByStepMenu::skipBackwardCenter.y - buttonSize.y / 2};
    Vector2 undoPos{pos.x + PConstants::PStepByStepMenu::undoCenter.x - buttonSize.x / 2, pos.y + PConstants::PStepByStepMenu::undoCenter.y - buttonSize.y / 2};
    Vector2 playPos{pos.x + PConstants::PStepByStepMenu::playCenter.x - buttonSize.x / 2, pos.y + PConstants::PStepByStepMenu::playCenter.y - buttonSize.y / 2};
    Vector2 redoPos{pos.x + PConstants::PStepByStepMenu::redoCenter.x - buttonSize.x / 2, pos.y + PConstants::PStepByStepMenu::redoCenter.y - buttonSize.y / 2};
    Vector2 skipForwardPos{pos.x + PConstants::PStepByStepMenu::skipForwardCenter.x - buttonSize.x / 2, pos.y + PConstants::PStepByStepMenu::skipForwardCenter.y - buttonSize.y / 2};
    
    skipBackward = PIconButton(skipBackwardPos, buttonSize, "Assets/Images/PSkipBackward.png");
    undo = PIconButton(undoPos, buttonSize, "Assets/Images/PUndo.png");
    play = PIconButton(playPos, buttonSize, "Assets/Images/PPlay.png");
    redo = PIconButton(redoPos, buttonSize, "Assets/Images/PRedo.png");
    skipForward = PIconButton(skipForwardPos, buttonSize, "Assets/Images/PSkipForward.png");

    isOperating = false;
    mode = NoRequest;
}

void PStepByStepMenu::prepare(void) {
    skipBackward.prepare();
    undo.prepare();
    play.prepare();
    redo.prepare();
    skipForward.prepare();
}

void PStepByStepMenu::update(void) {
    
}

void PStepByStepMenu::draw(void) {
    DrawRectangleRec(background, PConstants::PStepByStepMenu::regionColor);
    skipBackward.draw();
    undo.draw();
    play.draw();
    redo.draw();
    skipForward.draw();
}

int PStepByStepMenu::getRequest(void) {
    if(skipBackward.isClicked()) {
        return SkipBackward; // Skip backward
    }
    else if(undo.isClicked()) {
        return GoBackward; // Undo
    }
    else if(play.isClicked()) {
        return Play; // Play
    }
    else if(redo.isClicked()) {
        return GoForward; // Redo
    }
    else if(skipForward.isClicked()) {
        return SkipForward; // Skip forward
    }
    return NoRequest; // No request
}