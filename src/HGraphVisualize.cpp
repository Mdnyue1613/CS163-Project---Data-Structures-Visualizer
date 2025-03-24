#include "../header/GUI.h"
#include "../header/HGraphVisualize.h"

TextBox GraphGUI::header;
TextBox GraphGUI::graphTypeBG;
TextBox GraphGUI::functionBG;
TextBox GraphGUI::guideBG;
TextBox GraphGUI::explainBG;
int GraphGUI::margin = 5;
int GraphGUI::currentFunction = 0;
vector <const char*> GraphGUI::listFunction = {"Initialize", "Add", "Delete", "Update", "Search", "Shorted Path"};
NavigateButton GraphGUI::leftButton;
NavigateButton GraphGUI::rightButton;
Graph GraphGUI::G;

void GraphGUI::GraphVisualize()
{
    leftButton.img = LoadTexture("Assets/LeftArrow.png");
    rightButton.img = LoadTexture("Assets/RightArrow.png");

    InitializeBackGround();
    G.Initialize();
    G.workspace = Rectangle{
        graphTypeBG.rec.x + graphTypeBG.rec.width, 
        header.rec.y + header.rec.height, 
        GetScreenWidth() - (graphTypeBG.rec.x + graphTypeBG.rec.width), 
        GetScreenHeight() - (header.rec.y + header.rec.height)
    };

    while (GUI::isOpenDS4)
    {
        BeginDrawing();
        DrawBackGround();
        DrawFunction();
        G.DrawGraph();

        GUI::BACK();
        EndDrawing();
        if(WindowShouldClose()) {
            GUI::isOpenDS4 = 0;
            break;
        }
    }
    
    UnloadTexture(leftButton.img);
    UnloadTexture(rightButton.img);
}

void GraphGUI::InitializeBackGround()
{
    header.rec = Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()/10};
    header.recColor = Color({248, 240, 240, 255});
    header.thick = 4;
    header.outlineColor = BLACK;
    header.text = (char*)(const char*)"Graph";
    header.fontSize = 40;
    header.textColor = BLACK;

    graphTypeBG.rec = Rectangle{header.thick, header.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight()/10};
    graphTypeBG.recColor = Color({151, 219, 174, 255});
    graphTypeBG.thick = 0;
    graphTypeBG.outlineColor = BLACK;
    graphTypeBG.text = (char*)(const char*)"";
    graphTypeBG.fontSize = 0;
    graphTypeBG.textColor = BLACK;

    functionBG.rec = Rectangle{header.thick, graphTypeBG.rec.y + graphTypeBG.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight()/4};
    functionBG.recColor = Color({117, 189, 241, 255});
    functionBG.thick = 0;
    functionBG.outlineColor = BLACK;
    functionBG.text = (char*)(const char*)"";
    functionBG.fontSize = 0;
    functionBG.textColor = BLACK;
    functionBG.draw();

    guideBG.rec = Rectangle{header.thick, functionBG.rec.y + functionBG.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight()/10};
    guideBG.recColor = Color({120, 209, 210, 255});
    guideBG.thick = 0;
    guideBG.outlineColor = BLACK;
    guideBG.text = (char*)(const char*)"";
    guideBG.fontSize = 0;
    guideBG.textColor = BLACK;

    explainBG.rec = Rectangle{header.thick, guideBG.rec.y + guideBG.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight() - guideBG.rec.x - guideBG.rec.height};
    explainBG.recColor = Color({205, 228, 173, 255});
    explainBG.thick = 0;
    explainBG.outlineColor = BLACK;
    explainBG.text = (char*)(const char*)"";
    explainBG.fontSize = 0;
    explainBG.textColor = BLACK;
}

void GraphGUI::DrawBackGround()
{
    ClearBackground(WHITE);
    header.draw();
    graphTypeBG.draw();
    functionBG.draw();
    guideBG.draw();
    explainBG.draw();
}

void GraphGUI::DrawFunction()
{
    DrawCustomizeGraphType();

    TextBox title;
    DrawTitleFunction(title, listFunction[currentFunction]);

    switch (currentFunction)
    {
    case 0:
        DrawInitializeFunction(title);
        break;
    
    case 1:
        DrawAddFunction();
        break;
    
    case 2:
        DrawDeleteFunction();
        break;
    
    case 3:
        DrawUpdateFunction();
        break;
    
    case 4:
        DrawUpdateFunction();
        break;
    
    case 5:
        DrawSearchFunction();
        break;
    
    case 6:
        DrawShortedPathFunction();
        break;
    }
}

void GraphGUI::DrawCustomizeGraphType()
{
    // TextBox undirectedButton;
    // TextBox directedButton;

    // undirectedButton.rec.width = (graphTypeBG.rec.width - margin*2*3) / 2; 
    // undirectedButton.rec.height = graphTypeBG.rec.height / 2;
    // undirectedButton.rec.x = graphTypeBG.rec.x + margin*2;
    // undirectedButton.rec.y = graphTypeBG.rec.y + (graphTypeBG.rec.height - undirectedButton.rec.height)/2;
    // if (G.type == 0) undirectedButton.recColor = GRAY;
    // else undirectedButton.recColor = WHITE;
    // undirectedButton.thick = 2;
    // undirectedButton.outlineColor = BLACK;
    // undirectedButton.text = (char*)(const char*)"Undirected";
    // undirectedButton.fontSize = undirectedButton.rec.height / 2;
    // undirectedButton.textColor = BLACK;
    // undirectedButton.draw();

    // directedButton.rec.width = (graphTypeBG.rec.width - margin*2*3) / 2; 
    // directedButton.rec.height = graphTypeBG.rec.height / 2;
    // directedButton.rec.x = graphTypeBG.rec.x + undirectedButton.rec.width + margin*2*2;
    // directedButton.rec.y = graphTypeBG.rec.y + (graphTypeBG.rec.height - undirectedButton.rec.height)/2;
    // if (G.type == 0) directedButton.recColor = WHITE;
    // else directedButton.recColor = GRAY;
    // directedButton.thick = 2;
    // directedButton.outlineColor = BLACK;
    // directedButton.text = (char*)(const char*)"Directed";
    // directedButton.fontSize = directedButton.rec.height / 2;
    // directedButton.textColor = BLACK;
    // directedButton.draw();

    // Vector2 mouse = GetMousePosition();
    // if (CheckCollisionPointRec(mouse, undirectedButton.rec) && G.type == 1)
    // {
    //     undirectedButton.recColor = LIGHTGRAY;
    //     undirectedButton.draw();
    //     if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    //     {
    //         G.type ^= 1;
    //     }
    //     else undirectedButton.recColor = WHITE;
    // }
    // else if (CheckCollisionPointRec(mouse, directedButton.rec) && G.type == 0)
    // {
    //     directedButton.recColor = LIGHTGRAY;
    //     directedButton.draw();
    //     if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    //     {
    //         G.type ^= 1;
    //     }
    //     else directedButton.recColor = WHITE;
    // }
}

void GraphGUI::DrawTitleFunction(TextBox &title, const char* nameFunction)
{
    title.rec.width = functionBG.rec.width - margin*2;
    title.rec.height = functionBG.rec.height / 5;
    title.rec.x = functionBG.rec.x + (functionBG.rec.width - title.rec.width)/2;
    title.rec.y = functionBG.rec.y + 5;
    title.recColor = WHITE;
    title.thick = 2;
    title.outlineColor = BLACK;
    title.text = (char*)nameFunction;
    title.fontSize = title.rec.height / 10 * 6;
    title.textColor = BLACK;
    title.draw();
    NavigationButton(title);
}

void GraphGUI::NavigationButton(TextBox functionTitle)
{
    leftButton.scale = functionTitle.rec.height / leftButton.img.height;
    leftButton.rec = Rectangle{functionTitle.rec.x, functionTitle.rec.y, leftButton.img.width * leftButton.scale, leftButton.img.height * leftButton.scale};
    leftButton.rotation = 0;
    leftButton.color = WHITE;

    rightButton.scale = functionTitle.rec.height / rightButton.img.height;
    rightButton.rec = Rectangle{functionTitle.rec.x + functionTitle.rec.width - rightButton.rec.width, functionTitle.rec.y, rightButton.img.width * rightButton.scale, rightButton.img.height * rightButton.scale};
    rightButton.rotation = 0;
    rightButton.color = WHITE;

    leftButton.draw();
    rightButton.draw();

    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, leftButton.rec))
    {
        leftButton.color = LIGHTGRAY;
        leftButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            currentFunction--;
            if (currentFunction < 0) currentFunction += 6;
        }
        leftButton.color = WHITE;
    }
    else if (CheckCollisionPointRec(mouse, rightButton.rec))
    {
        rightButton.color = LIGHTGRAY;
        rightButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            currentFunction++;
            if (currentFunction > 5) currentFunction = 0;
        }
        rightButton.color = WHITE; 
    }
}

void GraphGUI::DrawInitializeFunction(TextBox title)
{
    Vector2 mouse = GetMousePosition();

    TextBox chooseFile;
    chooseFile.rec.width = (functionBG.rec.width - margin*2*3) / 2; 
    chooseFile.rec.height = functionBG.rec.height / 6;
    chooseFile.rec.x = functionBG.rec.x + margin*2;
    chooseFile.rec.y = title.rec.y + title.rec.height + margin*2;
    chooseFile.recColor = WHITE;
    chooseFile.thick = 2;
    chooseFile.outlineColor = BLACK;
    chooseFile.text = (char*)(const char*)"From File";
    chooseFile.fontSize = chooseFile.rec.height / 10 * 6;
    chooseFile.textColor = BLACK;
    chooseFile.draw();

    if (CheckCollisionPointRec(mouse, chooseFile.rec))
    {
        chooseFile.recColor = LIGHTGRAY;
        chooseFile.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            chooseFile.recColor = DARKGRAY;
            chooseFile.draw();
            const char *filters[] = { "*.txt", "*.inp", "*.out" };
            const char *selectedFile = tinyfd_openFileDialog("Select a file", "", 3, filters, NULL, 0);

            if (selectedFile)
                G.LoadFromFile(selectedFile);
            
        }   
    }

    TextBox random;
    random.rec.width = (functionBG.rec.width - margin*2*3) / 2; 
    random.rec.height = functionBG.rec.height / 6;
    random.rec.x = functionBG.rec.x + random.rec.width + margin*2*2;
    random.rec.y = title.rec.y + title.rec.height + margin*2;
    random.recColor = WHITE;
    random.thick = 2;
    random.outlineColor = BLACK;
    random.text = (char*)(const char*)"Random";
    random.fontSize = random.rec.height / 10 * 6;
    random.textColor = BLACK;
    random.draw();

    if (CheckCollisionPointRec(mouse, random.rec))
    {
        random.recColor = LIGHTGRAY;
        random.draw();
        random.recColor = WHITE;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            random.recColor = DARKGRAY;
            random.draw();
            G.RandomData();
        }   
    }
}

void GraphGUI::DrawAddFunction()
{
    
}

void GraphGUI::DrawDeleteFunction()
{
    
}

void GraphGUI::DrawUpdateFunction()
{
    
}

void GraphGUI::DrawSearchFunction()
{
    
}

void GraphGUI::DrawShortedPathFunction()
{
    
}
