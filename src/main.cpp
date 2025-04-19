#include "../header/GUI.h"
#include "../header/AVL.h"
#include <iostream>
#include <queue>

bool GUI::isOpenMenu = true;
vector <bool> GUI::isOpenDS = {0, 0, 0, 0};
Font GUI::font;
bool GUI::ColorMode = 0;
ImageButton GUI::BackButton;
vector <ImageButton> GUI::ColorModeButton;
vector <Texture2D> GUI::BackGround;
vector <Color> GUI::BackGroundColor;
vector <ImageButton> GUI::Menu;
TextBox GUI::TopicBox;
vector <TextBox> GUI::Title;

DS1 GUI::linkedListVisualizer;
DS2 GUI::hashtableVisualizer;
DS3 GUI::ds3;

int main() {
    GUI::startProgram();
    return 0;
}
