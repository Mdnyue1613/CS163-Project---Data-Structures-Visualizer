#include "..\header\GUI.h"

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
    Rectangle Menu1 = {space_x, space_y, MenuWidth, MenuHeight};
    Rectangle Menu2 = {space_x, space_y + MenuHeight + space_y * 2, MenuWidth, MenuHeight};
    Rectangle Menu3 = {space_x + MenuWidth + space_x * 2, space_y, MenuWidth, MenuHeight};
    Rectangle Menu4 = {space_x + MenuWidth + space_x * 2, space_y + MenuHeight + space_y * 2, MenuWidth, MenuHeight};

    DrawRectangle(space_x, space_y, MenuWidth, MenuHeight, YELLOW);
    DrawRectangle(space_x, space_y + MenuHeight + space_y * 2, MenuWidth, MenuHeight, RED );
    DrawRectangle(space_x + MenuWidth + space_x * 2, space_y, MenuWidth, MenuHeight, BLUE);
    DrawRectangle(space_x + MenuWidth + space_x * 2, space_y + MenuHeight + space_y * 2, MenuWidth, MenuHeight, PINK );

    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, Menu1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isOpenDS1 = 1;
        isOpenMenu = 0;
    }
    if (CheckCollisionPointRec(mouse, Menu2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isOpenDS2 = 1;
        isOpenMenu = 0;
    }
    if (CheckCollisionPointRec(mouse, Menu3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isOpenDS3 = 1;
        isOpenMenu = 0;
    }
    if (CheckCollisionPointRec(mouse, Menu4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
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