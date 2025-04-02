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
TextBox GraphGUI::undirectedButton;
TextBox GraphGUI::directedButton;
NavigateButton GraphGUI::leftNavigationButton;
NavigateButton GraphGUI::rightNavigationButton;
TextBox GraphGUI::functionTitle;
TextBox GraphGUI::chooseFileButton;
TextBox GraphGUI::randomButton;
InputBox GraphGUI::inputBox;
TextBox GraphGUI::GoButton;
Graph GraphGUI::G;

void GraphGUI::GraphVisualize()
{
    InitializeObject();   

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
    
    UnloadTexture(leftNavigationButton.img);
    UnloadTexture(rightNavigationButton.img);
}

void GraphGUI::InitializeObject()
{
    header.rec = Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()/10};
    header.recColor = Color({248, 240, 240, 255});
    header.thick = 4;
    header.outlineColor = BLACK;
    header.text = (char*)(const char*)"Graph";
    header.fontSize = header.rec.height * 3/5;
    header.textColor = BLACK;

    graphTypeBG.rec = Rectangle{header.thick, header.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight()/16};
    graphTypeBG.recColor = Color({151, 219, 174, 255});
    graphTypeBG.thick = 0;
    graphTypeBG.outlineColor = BLACK;
    graphTypeBG.text = (char*)(const char*)"";
    graphTypeBG.fontSize = 0;
    graphTypeBG.textColor = BLACK;

    functionBG.rec = Rectangle{header.thick, graphTypeBG.rec.y + graphTypeBG.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight()/3};
    functionBG.recColor = Color({117, 189, 241, 255});
    functionBG.thick = 0;
    functionBG.outlineColor = BLACK;
    functionBG.text = (char*)(const char*)"";
    functionBG.fontSize = 0;
    functionBG.textColor = BLACK;
    functionBG.draw();

    guideBG.rec = Rectangle{header.thick, functionBG.rec.y + functionBG.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight()/16};
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

    undirectedButton.rec.width = round((graphTypeBG.rec.width - margin*2*3) / 2); 
    undirectedButton.rec.height = round(graphTypeBG.rec.height * 2/3);
    undirectedButton.rec.x = round(graphTypeBG.rec.x + margin*2);
    undirectedButton.rec.y = round(graphTypeBG.rec.y + (graphTypeBG.rec.height - undirectedButton.rec.height)/2);
    undirectedButton.recColor = GRAY;
    undirectedButton.thick = 2;
    undirectedButton.outlineColor = BLACK;
    undirectedButton.text = (char*)(const char*)"Undirected";
    undirectedButton.fontSize = undirectedButton.rec.height * 3/5;
    undirectedButton.textColor = BLACK;

    directedButton.rec.width = round((graphTypeBG.rec.width - margin*2*3) / 2); 
    directedButton.rec.height = round(graphTypeBG.rec.height * 2/3);
    directedButton.rec.x = round(graphTypeBG.rec.x + undirectedButton.rec.width + margin*2*2);
    directedButton.rec.y = round(graphTypeBG.rec.y + (graphTypeBG.rec.height - undirectedButton.rec.height)/2);
    directedButton.recColor = WHITE;
    directedButton.thick = 2;
    directedButton.outlineColor = BLACK;
    directedButton.text = (char*)(const char*)"Directed";
    directedButton.fontSize = directedButton.rec.height * 3/5;
    directedButton.textColor = BLACK;

    functionTitle.rec.width = round(functionBG.rec.width - margin*2);
    functionTitle.rec.height = round(functionBG.rec.height / 7);
    functionTitle.rec.x = round(functionBG.rec.x + (functionBG.rec.width - functionTitle.rec.width)/2);
    functionTitle.rec.y = round(functionBG.rec.y + margin);
    functionTitle.recColor = WHITE;
    functionTitle.thick = 2;
    functionTitle.outlineColor = BLACK;
    functionTitle.fontSize = functionTitle.rec.height * 3/5;
    functionTitle.textColor = BLACK;

    leftNavigationButton.img = LoadTexture("Assets/LeftArrow.png");
    leftNavigationButton.scale = functionTitle.rec.height / leftNavigationButton.img.height;
    leftNavigationButton.rec.width = leftNavigationButton.img.width * leftNavigationButton.scale;
    leftNavigationButton.rec.height = leftNavigationButton.img.height * leftNavigationButton.scale;
    leftNavigationButton.rec.x = functionTitle.rec.x;
    leftNavigationButton.rec.y = functionTitle.rec.y;
    leftNavigationButton.rotation = 0;
    leftNavigationButton.color = WHITE;
    
    rightNavigationButton.img = LoadTexture("Assets/RightArrow.png");
    rightNavigationButton.scale = functionTitle.rec.height / rightNavigationButton.img.height;
    rightNavigationButton.rec.width = rightNavigationButton.img.width * rightNavigationButton.scale;
    rightNavigationButton.rec.height = rightNavigationButton.img.height * rightNavigationButton.scale;
    rightNavigationButton.rec.x = functionTitle.rec.x + functionTitle.rec.width - rightNavigationButton.rec.width;
    rightNavigationButton.rec.y = functionTitle.rec.y;
    rightNavigationButton.rotation = 0;
    rightNavigationButton.color = WHITE;

    chooseFileButton.rec.width = round((functionBG.rec.width - margin*2*3) / 2); 
    chooseFileButton.rec.height = round(functionBG.rec.height / 8);
    chooseFileButton.rec.x = round(functionBG.rec.x + margin*2);
    chooseFileButton.rec.y = round(functionTitle.rec.y + functionTitle.rec.height + margin*2);
    chooseFileButton.recColor = WHITE;
    chooseFileButton.thick = 2;
    chooseFileButton.outlineColor = BLACK;
    chooseFileButton.text = (char*)(const char*)"From File";
    chooseFileButton.fontSize = chooseFileButton.rec.height * 3/5;
    chooseFileButton.textColor = BLACK;

    randomButton.rec.width = round((functionBG.rec.width - margin*2*3) / 2); 
    randomButton.rec.height = round(functionBG.rec.height / 8);
    randomButton.rec.x = round(functionBG.rec.x + randomButton.rec.width + margin*2*2);
    randomButton.rec.y = round(functionTitle.rec.y + functionTitle.rec.height + margin*2);
    randomButton.recColor = WHITE;
    randomButton.thick = 2;
    randomButton.outlineColor = BLACK;
    randomButton.text = (char*)(const char*)"Random";
    randomButton.fontSize = randomButton.rec.height * 3/5;
    randomButton.textColor = BLACK;

    inputBox.displayedLines = 3;
    inputBox.box.rec.width = round((functionBG.rec.width - margin*2*2)); 
    inputBox.box.rec.height = round(functionBG.rec.height/8 * inputBox.displayedLines);
    inputBox.box.rec.x = round(functionBG.rec.x + margin*2);
    inputBox.box.rec.y = round(functionTitle.rec.y + functionTitle.rec.height + randomButton.rec.height + margin*2*2);
    inputBox.box.recColor = WHITE;
    inputBox.box.thick = 2;
    inputBox.box.outlineColor = BLACK;
    inputBox.box.text = (char*)(const char*)"Enter your graph";
    inputBox.box.fontSize = inputBox.box.rec.height/3 * 3/5;
    inputBox.box.textColor = GRAY;
    inputBox.userInput.resize(1);
    inputBox.fontSize = inputBox.box.fontSize;
    inputBox.maxLenPerLine = inputBox.box.rec.width - MeasureText(to_string(0).c_str(), inputBox.fontSize)*2;
    inputBox.inputColor = BLACK;

    GoButton.recColor = WHITE;
    GoButton.thick = 2;
    GoButton.outlineColor = BLACK;
    GoButton.text = (char*)(const char*)"GO!";
    GoButton.textColor = RED;

    G.Initialize();
    G.workspace = Rectangle{
        graphTypeBG.rec.x + graphTypeBG.rec.width, 
        header.rec.y + header.rec.height, 
        GetScreenWidth() - (graphTypeBG.rec.x + graphTypeBG.rec.width), 
        GetScreenHeight() - (header.rec.y + header.rec.height)
    };
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
    DrawTitleFunction(listFunction[currentFunction]);

    switch (currentFunction)
    {
    case 0:
        DrawInitializeFunction();
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
    undirectedButton.draw();
    directedButton.draw();

    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, undirectedButton.rec) && G.type == 1)
    {
        undirectedButton.recColor = LIGHTGRAY;
        undirectedButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            G.ChangeGraphType();
            undirectedButton.recColor = GRAY;
            directedButton.recColor = WHITE;
        }
        else undirectedButton.recColor = WHITE;
    }
    else if (CheckCollisionPointRec(mouse, directedButton.rec) && G.type == 0)
    {
        directedButton.recColor = LIGHTGRAY;
        directedButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            G.ChangeGraphType();
            directedButton.recColor = GRAY;
            undirectedButton.recColor = WHITE;
        }
        else directedButton.recColor = WHITE;
    }
}

void GraphGUI::DrawTitleFunction(const char* nameFunction)
{
    functionTitle.text = (char*)nameFunction;
    functionTitle.draw();
    DrawNavigationButton();
}

void GraphGUI::DrawNavigationButton()
{
    leftNavigationButton.draw();
    rightNavigationButton.draw();

    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, leftNavigationButton.rec))
    {
        leftNavigationButton.color = LIGHTGRAY;
        leftNavigationButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            currentFunction--;
            if (currentFunction < 0) currentFunction += 6;
        }
        leftNavigationButton.color = WHITE;
    }
    else if (CheckCollisionPointRec(mouse, rightNavigationButton.rec))
    {
        rightNavigationButton.color = LIGHTGRAY;
        rightNavigationButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            currentFunction++;
            if (currentFunction > 5) currentFunction = 0;
        }
        rightNavigationButton.color = WHITE; 
    }
}

void GraphGUI::DrawInitializeFunction()
{
    Vector2 mouse = GetMousePosition();

    chooseFileButton.draw();
    if (CheckCollisionPointRec(mouse, chooseFileButton.rec))
    {
        chooseFileButton.recColor = LIGHTGRAY;
        chooseFileButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            chooseFileButton.recColor = DARKGRAY;
            chooseFileButton.draw();
            const char *filters[] = { "*.txt", "*.inp", "*.out" };
            const char *selectedFile = tinyfd_openFileDialog("Select a file", "", 3, filters, NULL, 0);

            if (selectedFile)
                G.LoadFromFile(selectedFile);
        }   
        chooseFileButton.recColor = WHITE;
    }

    randomButton.draw();
    if (CheckCollisionPointRec(mouse, randomButton.rec))
    {
        randomButton.recColor = LIGHTGRAY;
        randomButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            randomButton.recColor = DARKGRAY;
            randomButton.draw();
            G.RandomData();
        }
        randomButton.recColor = WHITE;
    }

    GoButton.rec.x = round(functionBG.rec.x + margin*2);
    GoButton.rec.y = round(inputBox.box.rec.y + inputBox.box.rec.height + margin*2);
    GoButton.rec.width = round((functionBG.rec.width - margin*2*2)); 
    GoButton.rec.height = round(functionBG.rec.height / 8);
    GoButton.fontSize = GoButton.rec.height * 3/5;

    inputBox.draw();
    inputBox.activate();
    GoButton.draw();
    if (CheckCollisionPointRec(mouse, GoButton.rec))
    {
        GoButton.recColor = LIGHTGRAY;
        GoButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            GoButton.recColor = DARKGRAY;
            GoButton.draw();
            // G.RandomData();
        }
        GoButton.recColor = WHITE;
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
