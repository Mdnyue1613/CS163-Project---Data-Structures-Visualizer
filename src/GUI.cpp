#include "../header/GUI.h"
#include "../header/HGraphVisualize.h"
#include "../header/BOX.h"
#include "../header/LInputBox.h"
#include "../header/AVL.h"
#include "../header/DS2.h"
#include <iostream>
void GUI::startProgram() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1200, 800, "Hello Raylib");
    SetTargetFPS(60);

    Init();
    linkedListVisualizer.prepare();
    hashtableVisualizer.prepare();
    ds3.prepare();

    while(isOpenDS[0] || isOpenDS[1] || isOpenDS[2] || isOpenDS[3] || isOpenMenu) {
        drawMenu();
        drawDS1();
        drawDS2();
        drawDS3();
        drawDS4();
    }

    UnInit();
    CloseWindow();
}

void GUI::drawMenu() {
    while(GUI::isOpenMenu == true) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw back ground
        float scale = max(GetScreenWidth() / (float)BackGround[ColorMode].width, GetScreenHeight() / (float)BackGround[ColorMode].height);
        DrawTextureEx(BackGround[ColorMode], {0, 0}, 0, scale, WHITE);

        // Modify position of ColorModeButton and draw it
        ColorModeButton[0].rec.x = ColorModeButton[1].rec.x = TopicBox.rec.x + TopicBox.rec.width + 20;
        ColorModeButton[0].rec.y = ColorModeButton[1].rec.y = TopicBox.rec.y + (TopicBox.rec.height - ColorModeButton[0].rec.height)/2;
        CustomColorMode();

        // Draw rectangle of the topic
        if (ColorMode == 0)
        {
            DrawRectangleRounded(TopicBox.rec, 0.3f, 10, BABYBLUE);
        }
        else DrawRectangleRounded(TopicBox.rec, 0.3f, 10, SKYCYAN);

        // Draw name of topic with center align
        Vector2 pos = {
            TopicBox.rec.x + (TopicBox.rec.width - MeasureTextEx(font, TopicBox.text, TopicBox.fontSize, 0).x)/2,
            TopicBox.rec.y + (TopicBox.rec.height - MeasureTextEx(font, TopicBox.text, TopicBox.fontSize, 0).y)/2,
        };
        DrawTextEx(font, TopicBox.text, pos, TopicBox.fontSize, 0, BackGroundColor[ColorMode ^ 1]);

        // Draw menu
        for (int i = 0; i < 4; i++)
        {
            // Find the position of image of data structure
            pos = {
                Menu[i].rec.x + (Menu[i].rec.width - Menu[i].img.width * Menu[i].scale) / 2,
                Menu[i].rec.y + (Menu[i].rec.height - Menu[i].img.height * Menu[i].scale) / 2,
            };
            // Identify bounded color for each color mode
            Color color = BLACK;
            if (ColorMode == 1) color = GRAY;

            // Draw image of data structure
            DrawRectangleRounded(Menu[i].rec, 0.3f, 10, WHITE);
            DrawTextureEx(Menu[i].img, pos, 0, Menu[i].scale, WHITE);
            DrawRectangleRoundedLinesEx(Menu[i].rec, 0.3f, 10, 3, color);

            // Find position, identify text color and draw name of data structure
            pos = {
                Title[i].rec.x + (Title[i].rec.width - MeasureTextEx(font, Title[i].text, Title[i].fontSize, 0).x)/2,
                Title[i].rec.y + (Title[i].rec.height - MeasureTextEx(font, Title[i].text, Title[i].fontSize, 0).y)/2,
            };
            DrawTextEx(font, Title[i].text, pos, Title[i].fontSize, 0, BackGroundColor[ColorMode ^ 1]);

            // Choose data structure
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, Menu[i].rec))
            {
                DrawRectangleRoundedLinesEx(Menu[i].rec, 0.3f, 10, 3, LIGHTGRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    DrawRectangleRoundedLinesEx(Menu[i].rec, 0.3f, 10, 3, DARKGRAY);
                    isOpenDS[i] = 1;
                    isOpenMenu = 0;

                    ColorModeButton[0].rec.x = ColorModeButton[1].rec.x = BackButton.rec.x - ColorModeButton[0].rec.width - 17;
                    ColorModeButton[0].rec.y = ColorModeButton[1].rec.y = 17;
                }
            }
        }

        EndDrawing();
        if(WindowShouldClose()) {
            isOpenMenu = 0;
            break;
        }
    }
}

void GUI::drawDS1() {
    while (GUI::isOpenDS[0]) {
        BeginDrawing();
        ClearBackground(WHITE);
        // Update the data structure before rendering it
        linkedListVisualizer.update();
        // Render the data structure
        linkedListVisualizer.draw();
        BACK();
        CustomColorMode();
        EndDrawing();
        if(WindowShouldClose()) {
            isOpenDS[0] = 0;
            break;
        }
    }
}

void GUI::drawDS2() {
    DS2 Hashtable;
    while (GUI::isOpenDS[1]) {
        BeginDrawing();
        ClearBackground(WHITE);
        hashtableVisualizer.update();
        hashtableVisualizer.draw();
        BACK();
        CustomColorMode();
        EndDrawing();
        if(WindowShouldClose()) {
            isOpenDS[1] = 0;
            break;
        }
    }
}

void GUI::drawDS3() {
    while (GUI::isOpenDS[2]) {
        BeginDrawing();
        ClearBackground(WHITE);
        ds3.draw();
        BACK();
        CustomColorMode();
        EndDrawing();
        if(WindowShouldClose()) {
            isOpenDS[2] = 0;
            break;
        }
    }
}

void GUI::drawDS4() {
    GraphGUI::GraphVisualize();
}

void GUI::BACK() {
    BackButton.draw();
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, BackButton.rec))
    {
        DrawRectangleRoundedLinesEx(BackButton.rec, 0.3f, 10, 2, BLACK);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            DrawRectangleRoundedLinesEx(BackButton.rec, 0.3f, 10, 2, RED);
            isOpenMenu = 1;
            isOpenDS[0] = isOpenDS[1] = isOpenDS[2] = isOpenDS[3] = 0;
        }
    }
}

void GUI::CustomColorMode()
{
    ColorModeButton[ColorMode].draw();
    Vector2 mouse = GetMousePosition();

    if (CheckCollisionPointRec(mouse, ColorModeButton[ColorMode].rec))
    {
        Color color = BLACK;
        if (ColorMode == 1) color = GRAY;
        DrawRectangleRoundedLinesEx(ColorModeButton[ColorMode].rec, 0.3f, 10, 2, color);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            DrawRectangleRoundedLinesEx(ColorModeButton[ColorMode].rec, 0.3f, 10, 2, RED);
            ColorMode ^= 1;
        }
    }
}

void GUI::Init()
{
    font = LoadFont("Assets/Font/Lato-Black.ttf");

    BackButton.img = LoadTexture("Assets/Images/Back.png");
    BackButton.scale = 0.09f;
    BackButton.rotation = 0;
    BackButton.rec.width = BackButton.img.width * BackButton.scale;
    BackButton.rec.height = BackButton.img.height * BackButton.scale;
    BackButton.rec.x = GetScreenWidth() - BackButton.rec.width - 17;
    BackButton.rec.y = 17;

    ColorModeButton.resize(2);

    ColorModeButton[0].img = LoadTexture("Assets/Images/DayMode.png");
    ColorModeButton[0].scale = 0.09f;
    ColorModeButton[0].rotation = 0;
    ColorModeButton[0].rec.width = ColorModeButton[0].img.width * ColorModeButton[0].scale;
    ColorModeButton[0].rec.height = ColorModeButton[0].img.height * ColorModeButton[0].scale;

    ColorModeButton[1] = ColorModeButton[0];
    ColorModeButton[1].img = LoadTexture("Assets/Images/NightMode.png");

    BackGround.resize(2);
    BackGround[0] = LoadTexture("Assets/Images/LightBackground.png");
    BackGround[1] = LoadTexture("Assets/Images/DarkBackground.png");

    BackGroundColor.resize(2);
    BackGroundColor[0] = WHITE;
    BackGroundColor[1] = BLACK;

    float space = round(GetScreenHeight() / 7);
    float width = round(GetScreenWidth() / 4);
    float height = round(GetScreenHeight() / 4);
    
    Menu.resize(4);

    Menu[0].img = LoadTexture("Assets/Images/LinkListBackground.png");
    Menu[0].rec.width = width;
    Menu[0].rec.height = height;
    Menu[0].rec.x = (GetScreenWidth() - width*2 - space) / 2;
    Menu[0].rec.y = 180;
    Menu[0].rotation = 0;
    Menu[0].scale = min(width / Menu[0].img.width, height / Menu[0].img.height);

    Menu[1].img = LoadTexture("Assets/Images/HashBackground.png");
    Menu[1].rec.width = width;
    Menu[1].rec.height = height;
    Menu[1].rec.x = Menu[0].rec.x + width + space;
    Menu[1].rec.y = Menu[0].rec.y;
    Menu[1].rotation = 0;
    Menu[1].scale = min(width / Menu[1].img.width, height / Menu[1].img.height);

    Menu[2].img = LoadTexture("Assets/Images/AVLTreeBackground.png");
    Menu[2].rec.width = width;
    Menu[2].rec.height = height;
    Menu[2].rec.x = Menu[0].rec.x;
    Menu[2].rec.y = Menu[0].rec.y + height + space;
    Menu[2].rotation = 0;
    Menu[2].scale = min(width / Menu[2].img.width, height / Menu[2].img.height);

    Menu[3].img = LoadTexture("Assets/Images/GraphBackground.png");
    Menu[3].rec.width = width;
    Menu[3].rec.height = height;
    Menu[3].rec.x = Menu[1].rec.x;
    Menu[3].rec.y = Menu[2].rec.y;
    Menu[3].rotation = 0;
    Menu[3].scale = min(width / Menu[3].img.width, height / Menu[3].img.height);

    TopicBox.text = "Data Structure Visualizers";
    TopicBox.fontSize = 60;
    TopicBox.rec.width = MeasureTextEx(font, TopicBox.text, TopicBox.fontSize, 0).x + 20;
    TopicBox.rec.height = MeasureTextEx(font, TopicBox.text, TopicBox.fontSize, 0).y + 20;
    TopicBox.rec.x = (GetScreenWidth() - TopicBox.rec.width) / 2;
    TopicBox.rec.y = 50;

    Title.resize(4);

    Title[0].text = "Doubly Linked List";
    Title[1].text = "Hash Table";
    Title[2].text = "AVL Tree";
    Title[3].text = "Graph";
    for (int i = 0; i < 4; i++)
    {
        Title[i].fontSize = TopicBox.fontSize * 2/3;
        Title[i].rec.width = MeasureTextEx(font, Title[i].text, Title[i].fontSize, 0).x + 15;
        Title[i].rec.height = MeasureTextEx(font, Title[i].text, Title[i].fontSize, 0).y + 15;
        Title[i].rec.x = Menu[i].rec.x - (Title[i].rec.width - Menu[i].rec.width)/2;
        Title[i].rec.y = Menu[i].rec.y + Menu[i].rec.height + 15;
    }
}

void GUI::UnInit()
{
    UnloadFont(font);
    UnloadTexture(BackButton.img);
    UnloadTexture(ColorModeButton[0].img);
    UnloadTexture(ColorModeButton[1].img);
    UnloadTexture(BackGround[0]);
    UnloadTexture(BackGround[1]);
    for (int i = 0; i < 4; i++)
        UnloadTexture(Menu[i].img);
}