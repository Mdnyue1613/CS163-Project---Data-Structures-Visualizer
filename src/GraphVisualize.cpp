#include "../header/GUI.h"
#include "../header/GraphVisualize.h"
#include "../header/TEXTBOX.h"

void GraphVisualize()
{
    while (GUI::isOpenDS4)
    {
        BeginDrawing();
        DrawBackGround();
        GUI::BACK();
        EndDrawing();
        if(WindowShouldClose()) {
            GUI::isOpenDS4 = 0;
            break;
        }
    }
}

void DrawBackGround()
{
    ClearBackground(WHITE);

    // Draw header
    TEXTBOX header;
    header.rec = Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()/10};
    header.recColor = Color({248, 240, 240, 255});
    header.upperline = 8;
    header.lowerline = 4;
    header.leftline = 0;
    header.rightline = 0;
    header.outlineColor = BLACK;
    header.text = "Graph";
    header.fontSize = 40;
    header.textColor = BLACK;
    header.draw();

    // Draw direction background
    TEXTBOX directionBG;
    directionBG.rec = Rectangle{0, header.rec.height + header.lowerline/2 + 5, (float)GetScreenWidth()/4, (float)GetScreenHeight()/10};
    directionBG.recColor = Color({151, 219, 174, 255});
    directionBG.upperline = 0;
    directionBG.lowerline = 0;
    directionBG.leftline = 0;
    directionBG.rightline = 0;
    directionBG.outlineColor = BLACK;
    directionBG.text = "";
    directionBG.fontSize = 0;
    directionBG.textColor = BLACK;
    directionBG.draw();

    // Draw function background
    TEXTBOX functionBG;
    functionBG.rec = Rectangle{0, directionBG.rec.y + directionBG.rec.height + 5, (float)GetScreenWidth()/4, (float)GetScreenHeight()/4};
    functionBG.recColor = Color({117, 189, 241, 255});
    functionBG.upperline = 0;
    functionBG.lowerline = 0;
    functionBG.leftline = 0;
    functionBG.rightline = 0;
    functionBG.outlineColor = BLACK;
    functionBG.text = "";
    functionBG.fontSize = 0;
    functionBG.textColor = BLACK;
    functionBG.draw();

    // Draw guide background
    TEXTBOX guideBG;
    guideBG.rec = Rectangle{0, functionBG.rec.y + functionBG.rec.height + 5, (float)GetScreenWidth()/4, (float)GetScreenHeight()/10};
    guideBG.recColor = Color({120, 209, 210, 255});
    guideBG.upperline = 0;
    guideBG.lowerline = 0;
    guideBG.leftline = 0;
    guideBG.rightline = 0;
    guideBG.outlineColor = BLACK;
    guideBG.text = "";
    guideBG.fontSize = 0;
    guideBG.textColor = BLACK;
    guideBG.draw();

    // Draw explain background
    TEXTBOX explainBG;
    explainBG.rec = Rectangle{0, guideBG.rec.y + guideBG.rec.height + 5, (float)GetScreenWidth()/4, (float)GetScreenHeight() - guideBG.rec.x - guideBG.rec.height};
    explainBG.recColor = Color({205, 228, 173, 255});
    explainBG.upperline = 0;
    explainBG.lowerline = 0;
    explainBG.leftline = 0;
    explainBG.rightline = 0;
    explainBG.outlineColor = BLACK;
    explainBG.text = "";
    explainBG.fontSize = 0;
    explainBG.textColor = BLACK;
    explainBG.draw();
}