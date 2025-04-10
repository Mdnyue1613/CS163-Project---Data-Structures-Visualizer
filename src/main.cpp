#include "../header/GUI.h"
#include "../header/AVL.h"
#include <iostream>
#include <queue>

bool GUI::isOpenMenu = true;
bool GUI::isOpenDS1 = false;
bool GUI::isOpenDS2 = false;
bool GUI::isOpenDS3 = false;
bool GUI::isOpenDS4 = false;
DS1 GUI::linkedListVisualizer;
DS3 GUI::ds3;

int main() {
    GUI::startProgram();
    return 0;
}
