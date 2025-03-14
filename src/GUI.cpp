#include "../header/GUI.h"
#include "../header/BOX.h"
#include <iostream>

void GUI::startProgram() {
    InitWindow(1200, 800, "Hello Raylib");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();
        drawMenu();
        drawDS1();
        drawDS2();
        drawDS3();
        drawDS4();
        EndDrawing();
    }

    CloseWindow();
}

void GUI::drawMenu() {
    if(GUI::isOpenMenu == false) return;
    // divide screen
    ClearBackground(RAYWHITE);
    float space_x = GetScreenWidth() / 10;
    float space_y = GetScreenHeight() / 7;

    // set menu size
    float MenuWidth = space_x * 3;
    float MenuHeight = space_y * 2;
    vector<Rectangle> MENU;
    Rectangle Menu1 = {space_x, space_y, MenuWidth, MenuHeight}; MENU.push_back(Menu1);
    Rectangle Menu2 = {space_x, space_y + MenuHeight + space_y * 2, MenuWidth, MenuHeight}; MENU.push_back(Menu2);
    Rectangle Menu3 = {space_x + MenuWidth + space_x * 2, space_y, MenuWidth, MenuHeight}; MENU.push_back(Menu3);
    Rectangle Menu4 = {space_x + MenuWidth + space_x * 2, space_y + MenuHeight + space_y * 2, MenuWidth, MenuHeight}; MENU.push_back(Menu4);

    vector<BOX> menu(4);
    for(int i = 0; i < 4; i++) {
        menu[i].setRec(MENU[i]);
        menu[i].setOutline(BLACK);
        if (menu[i].isMove()) menu[i].setColor(Color(GRAY));
        else menu[i].setColor(WHITE);
        menu[i].draw();
    }

    if (menu[0].isClick()) {
        isOpenDS1 = 1;
        isOpenMenu = 0;
    }
    if (menu[1].isClick()) {
        isOpenDS2 = 1;
        isOpenMenu = 0;
    }
    if (menu[2].isClick()) {
        isOpenDS3 = 1;
        isOpenMenu = 0;
    }
    if (menu[3].isClick()) {
        isOpenDS4 = 1;
        isOpenMenu = 0;
    }
}


void GUI::drawDS1() {
    if (isOpenDS1 == false) return;
    ClearBackground(YELLOW);
    BACK();
}

void GUI::drawDS2() {
    if (isOpenDS2 == false) return;
    ClearBackground(RED);
    BACK();
}

void GUI::drawDS3() {
    if (isOpenDS3 == false) return;
    ClearBackground(BLUE);
    BACK();
}

void GUI::drawDS4() {
    if (isOpenDS4 == false) return;
    ClearBackground(PINK);
    BACK();
}

void GUI::BACK() {
    Rectangle BackButton = {(float)GetScreenWidth() - 100, 0, 50, 50};
    DrawRectangleRec(BackButton, GRAY);
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, BackButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        isOpenMenu = 1;
        isOpenDS1 = isOpenDS2 = isOpenDS3 = isOpenDS4 = 0;
    }
}