#include "../header/PConstants.h"
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

Vector2 PConstants::PTitleBar::pos = {0, 0};
Vector2 PConstants::PTitleBar::size = {1200, 83};
int PConstants::PTitleBar::outlineThickness = 6;
int PConstants::PTitleBar::textSize = 30;
Color PConstants::PTitleBar::boxColor = {248, 240, 240, 255};
Color PConstants::PTitleBar::outlineColor = BLACK;
Vector2 PConstants::PFunctionArea::pos = {0, 86};
Vector2 PConstants::PFunctionArea::size = {307, 296};
int PConstants::PFunctionArea::boxHeight = 45;
int PConstants::PFunctionArea::boxWidth = 143;
float PConstants::PFunctionArea::boxHalfWidth = 146;
int PConstants::PFunctionArea::boxOutlineThickness = 2;
int PConstants::PFunctionArea::textSize = 20;
float PConstants::PFunctionArea::spaceX = 5.f;
float PConstants::PFunctionArea::spaceY = 5.f;
Color PConstants::PFunctionArea::regionColor = {75, 189, 224, 255};
Color PConstants::PFunctionArea::boxColor = WHITE;
Color PConstants::PFunctionArea::iconBoxColor = {238, 238, 238, 255};
Color PConstants::PFunctionArea::outlineBoxColor = BLACK;
Color PConstants::PFunctionArea::GOColor = RED;
Vector2 PConstants::PStepByStepMenu::pos = {0, 387};
Vector2 PConstants::PStepByStepMenu::skipBackwardCenter = {53, 34};
Vector2 PConstants::PStepByStepMenu::undoCenter = {103, 34};
Vector2 PConstants::PStepByStepMenu::playCenter = {153, 34};
Vector2 PConstants::PStepByStepMenu::redoCenter = {203, 34};
Vector2 PConstants::PStepByStepMenu::skipForwardCenter = {253, 34};
Vector2 PConstants::PStepByStepMenu::size = {307, 69};
float PConstants::PStepByStepMenu::iconHeight = 25.f;
float PConstants::PStepByStepMenu::iconWidth = 25.f;
Color PConstants::PStepByStepMenu::regionColor = {120, 209, 210, 255};
Vector2 PConstants::PExplanationArea::pos = {0, 461};
Vector2 PConstants::PExplanationArea::size = {500, 65};
Color PConstants::PExplanationArea::backgroundColor = {151, 219, 174, 255};
float PConstants::PExplanationArea::spaceX = 5.f;
float PConstants::PExplanationArea::spaceY = 5.f;
float PConstants::PExplanationArea::fontSize = 20.f;
Color PConstants::PExplanationArea::textColor = BLACK;
Vector2 PConstants::PseudoCodeArea::pos = {0, 522.8};
Vector2 PConstants::PseudoCodeArea::size = {500, 278.2};
Color PConstants::PseudoCodeArea::backgroundColor = {205, 228, 173, 255};
Color PConstants::PseudoCodeArea::highlightCodeColor = {235, 147, 93, 255};
float PConstants::PseudoCodeArea::spaceX = 5.f;
float PConstants::PseudoCodeArea::spaceY = 5.f;
float PConstants::PseudoCodeArea::fontSize = 20.f;
Color PConstants::PseudoCodeArea::textColor = BLACK;
float PConstants::PSwitchBox::arrowHeadWidth = 22.f;
float PConstants::PSwitchBox::arrowHeadHeight = 12.5f;
float PConstants::PSwitchBox::arrowHeadSpace = 10.f;
Color PConstants::PSwitchBox::arrowColor1 = BLACK;
Color PConstants::PSwitchBox::arrowColor2 = {150, 150, 150, 255};
float PConstants::PSwitchBox::fontSize = 20.f;
Color PConstants::PSwitchBox::textColor = BLACK;
Color PConstants::PInputBox::titleColor = {150, 150, 150, 255};
Color PConstants::PInputBox::inputColor = BLACK;
float PConstants::PCursor::leftSpace = 10.f;
float PConstants::PCursor::fullTime = 1.f;
float PConstants::PCursor::onTime = 0.5f;
float PConstants::PBOX::emphasizeThickness = 0.5f;
int PConstants::PLimit::intData = (int)1e9;
int PConstants::PLimit::maxInputLength = 9;
float PConstants::PIconBox::height = 41;
float PConstants::PIconBox::width = 139;
float PConstants::DS1::speed = 600.f;
Vector2 PConstants::DS1::headPosition = {400, 200};
Color PConstants::DS1::backgroundColor = WHITE;
float PConstants::PNode::innerRadius = 20.f;
float PConstants::PNode::outerRadius = 23.f;
float PConstants::PNode::characterSize = 20.f;
float PConstants::PNode::informationSize = 20.f;
float PConstants::PNode::lineThickness = 3.f;
float PConstants::PNode::lineLength = 100.f;
float PConstants::PNode::textSpace = 5.f;
float PConstants::PNode::newNodeSpace = 40.f;
float PConstants::PNode::arrowWidth = 12.f;
float PConstants::PNode::arrowHeight = 8.f;
Color PConstants::PNode::innerColor = WHITE;
Color PConstants::PNode::outerColor = BLACK;
Color PConstants::PNode::textColor = BLACK;
Color PConstants::PNode::innerHighlightColor = {255, 138, 39, 255};
Color PConstants::PNode::outerHighlightColor = {255, 138, 39, 255};
Color PConstants::PNode::textHighlightColor = WHITE;
Color PConstants::PNode::informationTextColor = BLACK;
Color PConstants::PNodeLine::color = BLACK;
Color PConstants::PNodeLine::highlightColor = {255, 138, 39, 255};
float PConstants::PAnimation::waitTime = 1.0f;

DS1 GUI::linkedListVisualizer;
DS2 GUI::hashtableVisualizer;
DS3 GUI::ds3;

int main() {
    GUI::startProgram();
    return 0;
}