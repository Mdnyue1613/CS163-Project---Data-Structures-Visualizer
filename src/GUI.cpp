#include "../header/GUI.h"
#include "../header/BOX.h"
#include "../header/LInputBox.h"
#include "../header/AVL.h"
#include <iostream>
void GUI::startProgram() {
    InitWindow(1200, 800, "Hello Raylib");
    SetTargetFPS(60);
    while(isOpenDS1 || isOpenDS2 || isOpenDS3 || isOpenDS4 || isOpenMenu) {
        drawMenu();
        drawDS1();
        drawDS2();
        drawDS3();
        drawDS4();
    }
    CloseWindow();
}
void GUI::drawMenu() {
    while(GUI::isOpenMenu == true) {
        BeginDrawing();
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
        EndDrawing();
        if(WindowShouldClose()) {
            isOpenMenu = 0;
            break;
        }
    }
}


void GUI::drawDS1() {
    DS1 linkedListVisualizer;
    while (GUI::isOpenDS1) {
        BeginDrawing();
        ClearBackground(WHITE);
        linkedListVisualizer.draw();
        BACK();
        EndDrawing();
        if(WindowShouldClose()) {
            isOpenDS1 = 0;
            break;
        }
    }
}

void GUI::drawDS2() {
    while(GUI::isOpenDS2) {
        BeginDrawing();
        ClearBackground(RED);
        BACK();
        EndDrawing();
        if(WindowShouldClose()) {
            isOpenDS2 = 0;
            break;
        }
    }
}

void GUI::drawDS3() {
    DS3 ds3;
    while (GUI::isOpenDS3) {
        BeginDrawing();
        ClearBackground(WHITE);
        ds3.draw();
        BACK();
        EndDrawing();
        if(WindowShouldClose()) {
            isOpenDS3 = 0;
            break;
        }
    }
}

void GUI::drawDS4() {
    while (isOpenDS4) {
        BeginDrawing();
        ClearBackground(PINK);
        BACK();
        EndDrawing();
        if(WindowShouldClose()) {
            isOpenDS4 = 0;
            break;
        }
    }
}

void GUI::BACK() {
    Rectangle Button = {1104, 12, 70.7, 51.7};
    BOX BackButton;
    BackButton.setRec(Button);
    const Rectangle HandCursorTexture = {0, 0, 15.5, 20};
    Rectangle HandDest = {GetMousePosition().x, GetMousePosition().y, 15.5, 20};
    if (BackButton.isMove()) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    if (BackButton.isClick()) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        isOpenMenu = 1;
        isOpenDS1 = isOpenDS2 = isOpenDS3 = isOpenDS4 = 0;
    }
}