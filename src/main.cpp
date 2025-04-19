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
DS2 GUI::hashtableVisualizer;
DS3 GUI::ds3;
bool GUI::isBackButtonOn = false;

int main() {
    GUI::startProgram();
    return 0;
}
