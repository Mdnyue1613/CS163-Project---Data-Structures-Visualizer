#include "../header/GUI.h"
#include "../header/HGraphVisualize.h"

TextBox GraphGUI::header;
TextBox GraphGUI::graphTypeBG;
TextBox GraphGUI::functionBG;
TextBox GraphGUI::guideBG;
TextBox GraphGUI::explainBG;
int GraphGUI::margin = 5;
bool GraphGUI::freeze = 0;
TextBox GraphGUI::notification;
int GraphGUI::currentFunction = 0;
vector <const char*> GraphGUI::listFunction = {"Initialize", "Add", "Delete", "Shorted Path"};
TextBox GraphGUI::undirectedButton;
TextBox GraphGUI::directedButton;
NavigateButton GraphGUI::leftNavigationButton;
NavigateButton GraphGUI::rightNavigationButton;
TextBox GraphGUI::functionTitle;
TextBox GraphGUI::chooseFileButton;
TextBox GraphGUI::randomButton;
InputBox GraphGUI::inputBox;
InputBox GraphGUI::addBox;
InputBox GraphGUI::deleteBox;
TextBox GraphGUI::GoButton;
Graph GraphGUI::G;

void GraphGUI::GraphVisualize()
{
    InitializeObject();   

    while (GUI::isOpenDS4)
    {
        BeginDrawing();
        DrawBackGround();
        G.DrawGraph();
        DrawFunction();

        GUI::BACK();
        EndDrawing();
        if(WindowShouldClose()) 
        {
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
    inputBox.defaultPos.width = round((functionBG.rec.width - margin*2*2)); 
    inputBox.defaultPos.height = round(functionBG.rec.height/8 * inputBox.displayedLines);
    inputBox.defaultPos.x = round(functionBG.rec.x + margin*2);
    inputBox.defaultPos.y = round(functionTitle.rec.y + functionTitle.rec.height + randomButton.rec.height + margin*2*2);
    inputBox.box.rec = inputBox.defaultPos;
    inputBox.box.recColor = WHITE;
    inputBox.box.thick = 2;
    inputBox.box.outlineColor = BLACK;
    inputBox.box.text = (char*)(const char*)"Enter your data";
    inputBox.box.fontSize = inputBox.box.rec.height/3 * 3/5;
    inputBox.box.textColor = GRAY;
    inputBox.userInput.resize(1);
    inputBox.fontSize = inputBox.box.fontSize;
    inputBox.lineSpacing = (inputBox.box.rec.height - inputBox.fontSize * inputBox.displayedLines) / (inputBox.displayedLines + 1);
    inputBox.maxLenPerLine = inputBox.box.rec.width - inputBox.lineSpacing*2;
    inputBox.inputColor = BLACK;

    addBox.displayedLines = 3;
    addBox.defaultPos.width = round((functionBG.rec.width - margin*2*2)); 
    addBox.defaultPos.height = round(functionBG.rec.height/8 * addBox.displayedLines);
    addBox.defaultPos.x = round(functionBG.rec.x + margin*2);
    addBox.defaultPos.y = round(functionTitle.rec.y + functionTitle.rec.height + margin*2);
    addBox.box.rec = addBox.defaultPos;
    addBox.box.recColor = WHITE;
    addBox.box.thick = 2;
    addBox.box.outlineColor = BLACK;
    addBox.box.text = (char*)(const char*)"Enter your data";
    addBox.box.fontSize = addBox.box.rec.height/3 * 3/5;
    addBox.box.textColor = GRAY;
    addBox.userInput.resize(1);
    addBox.fontSize = addBox.box.fontSize;
    addBox.lineSpacing = (addBox.box.rec.height - addBox.fontSize * addBox.displayedLines) / (addBox.displayedLines + 1);
    addBox.maxLenPerLine = addBox.box.rec.width - addBox.lineSpacing*2;
    addBox.inputColor = BLACK;

    deleteBox.displayedLines = 3;
    deleteBox.defaultPos.width = round((functionBG.rec.width - margin*2*2)); 
    deleteBox.defaultPos.height = round(functionBG.rec.height/8 * deleteBox.displayedLines);
    deleteBox.defaultPos.x = round(functionBG.rec.x + margin*2);
    deleteBox.defaultPos.y = round(functionTitle.rec.y + functionTitle.rec.height + margin*2);
    deleteBox.box.rec = deleteBox.defaultPos;
    deleteBox.box.recColor = WHITE;
    deleteBox.box.thick = 2;
    deleteBox.box.outlineColor = BLACK;
    deleteBox.box.text = (char*)(const char*)"Enter your data";
    deleteBox.box.fontSize = deleteBox.box.rec.height/3 * 3/5;
    deleteBox.box.textColor = GRAY;
    deleteBox.userInput.resize(1);
    deleteBox.fontSize = deleteBox.box.fontSize;
    deleteBox.lineSpacing = (deleteBox.box.rec.height - deleteBox.fontSize * deleteBox.displayedLines) / (deleteBox.displayedLines + 1);
    deleteBox.maxLenPerLine = deleteBox.box.rec.width - deleteBox.lineSpacing*2;
    deleteBox.inputColor = BLACK;

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
        DrawShortedPathFunction();
        break;
    }
}

void GraphGUI::DrawCustomizeGraphType()
{
    undirectedButton.draw();
    directedButton.draw();

    Vector2 mouse = GetMousePosition();
    if (!freeze && CheckCollisionPointRec(mouse, undirectedButton.rec) && G.type == 1)
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
    else if (!freeze && CheckCollisionPointRec(mouse, directedButton.rec) && G.type == 0)
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
    if (!freeze && CheckCollisionPointRec(mouse, leftNavigationButton.rec))
    {
        leftNavigationButton.color = LIGHTGRAY;
        leftNavigationButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            currentFunction--;
            if (currentFunction < 0) currentFunction += listFunction.size();
        }
        leftNavigationButton.color = WHITE;
    }
    else if (!freeze && CheckCollisionPointRec(mouse, rightNavigationButton.rec))
    {
        rightNavigationButton.color = LIGHTGRAY;
        rightNavigationButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            currentFunction++;
            if (currentFunction == listFunction.size()) currentFunction = 0;
        }
        rightNavigationButton.color = WHITE; 
    }
}

void GraphGUI::DrawInitializeFunction()
{
    Vector2 mouse = GetMousePosition();

    chooseFileButton.draw();
    if (!freeze && CheckCollisionPointRec(mouse, chooseFileButton.rec))
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
            {
                G.LoadFromFile(selectedFile);
                G.SynchronizeData(inputBox);
            }
        }   
        chooseFileButton.recColor = WHITE;
    }

    randomButton.draw();
    if (!freeze && CheckCollisionPointRec(mouse, randomButton.rec))
    {
        randomButton.recColor = LIGHTGRAY;
        randomButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            randomButton.recColor = DARKGRAY;
            randomButton.draw();
            G.RandomData();
            G.SynchronizeData(inputBox);
        }
        randomButton.recColor = WHITE;
    }

    if (inputBox.box.rec.x != G.workspace.x && inputBox.box.rec.y != G.workspace.y)
    {
        GoButton.rec.x = round(functionBG.rec.x + margin*2);
        GoButton.rec.y = round(inputBox.box.rec.y + inputBox.box.rec.height + margin*2);
        GoButton.rec.width = round((functionBG.rec.width - margin*2*2)); 
        GoButton.rec.height = round(functionBG.rec.height / 8);
        GoButton.fontSize = GoButton.rec.height * 3/5;
    }
        
    inputBox.draw();
    ZoomInputArea(inputBox);
    if (!freeze) inputBox.activate();
    GoButton.draw();
    if (!freeze && CheckCollisionPointRec(mouse, GoButton.rec))
    {
        GoButton.recColor = LIGHTGRAY;
        GoButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            GoButton.recColor = DARKGRAY;
            GoButton.draw();
            G.LoadFromKeyBoard(inputBox.userInput);
            
            if (!freeze)
            {
                if (inputBox.box.rec.x == G.workspace.x && inputBox.box.rec.y == G.workspace.y)
                {
                    inputBox.displayedLines = 3;
                    inputBox.box.rec = inputBox.defaultPos;
                    inputBox.maxLenPerLine = inputBox.box.rec.width - inputBox.lineSpacing*2;
                    inputBox.box.outlineColor = BLACK;
                }
            }
        }
        GoButton.recColor = WHITE;
    }

    if (freeze) Notify((char *)(const char*)"");
}

void GraphGUI::DrawAddFunction()
{
    Vector2 mouse = GetMousePosition();

    if (addBox.box.rec.x != G.workspace.x && addBox.box.rec.y != G.workspace.y)
    {
        GoButton.rec.x = round(functionBG.rec.x + margin*2);
        GoButton.rec.y = round(addBox.box.rec.y + addBox.box.rec.height + margin*2);
        GoButton.rec.width = round((functionBG.rec.width - margin*2*2)); 
        GoButton.rec.height = round(functionBG.rec.height / 8);
        GoButton.fontSize = GoButton.rec.height * 3/5;
    }

    addBox.draw();
    ZoomInputArea(addBox);
    if (!freeze) addBox.activate();
    GoButton.draw();
    if (!freeze && CheckCollisionPointRec(mouse, GoButton.rec))
    {
        GoButton.recColor = LIGHTGRAY;
        GoButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            GoButton.recColor = DARKGRAY;
            GoButton.draw();
            G.Add(addBox.userInput);
            G.SynchronizeData(inputBox);
            if (!freeze) 
            {
                addBox.clear();
                if (addBox.box.rec.x == G.workspace.x && addBox.box.rec.y == G.workspace.y)
                {
                    addBox.displayedLines = 3;
                    addBox.box.rec = addBox.defaultPos;
                    addBox.maxLenPerLine = addBox.box.rec.width - addBox.lineSpacing*2;
                    addBox.box.outlineColor = BLACK;
                }
            }
        }
        GoButton.recColor = WHITE;
    }

    if (freeze) Notify((char *)(const char*)"");
}

void GraphGUI::DrawDeleteFunction()
{
    Vector2 mouse = GetMousePosition();

    if (deleteBox.box.rec.x != G.workspace.x && deleteBox.box.rec.y != G.workspace.y)
    {
        GoButton.rec.x = round(functionBG.rec.x + margin*2);
        GoButton.rec.y = round(deleteBox.box.rec.y + deleteBox.box.rec.height + margin*2);
        GoButton.rec.width = round((functionBG.rec.width - margin*2*2)); 
        GoButton.rec.height = round(functionBG.rec.height / 8);
        GoButton.fontSize = GoButton.rec.height * 3/5;
    }

    deleteBox.draw();
    ZoomInputArea(deleteBox);
    if (!freeze) deleteBox.activate();
    GoButton.draw();
    if (!freeze && CheckCollisionPointRec(mouse, GoButton.rec))
    {
        GoButton.recColor = LIGHTGRAY;
        GoButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            GoButton.recColor = DARKGRAY;
            GoButton.draw();
            G.Delete(deleteBox.userInput);
            G.SynchronizeData(inputBox);
            if (!freeze) 
            {
                deleteBox.clear();
                if (deleteBox.box.rec.x == G.workspace.x && deleteBox.box.rec.y == G.workspace.y)
                {
                    deleteBox.displayedLines = 3;
                    deleteBox.box.rec = deleteBox.defaultPos;
                    deleteBox.maxLenPerLine = deleteBox.box.rec.width - deleteBox.lineSpacing*2;
                    deleteBox.box.outlineColor = BLACK;
                }
            }
        }
        GoButton.recColor = WHITE;
    }

    if (freeze) Notify((char *)(const char*)"");
}

void GraphGUI::DrawShortedPathFunction()
{
    
}

void GraphGUI::Notify(char *message)
{
    freeze = 1;

    notification.rec.height = round(GetScreenHeight() / 10);
    notification.fontSize = notification.rec.height / 4;
    if (strlen(message) > 0)
        notification.text = message;
    notification.rec.width = MeasureText(notification.text, notification.fontSize) + notification.fontSize * 2;
    notification.rec.x = round(G.workspace.x + (G.workspace.width - notification.rec.width) / 2);
    notification.rec.y = round(G.workspace.y + (G.workspace.height - notification.rec.height) / 2);
    notification.recColor = WHITE;
    notification.thick = 2;
    notification.outlineColor = BLACK;
    notification.textColor = RED;

    TextBox confirmButton;
    confirmButton.rec.width = round(notification.rec.width / 4);
    confirmButton.rec.height = round(notification.rec.height / 3);
    confirmButton.rec.x = round(notification.rec.x + (notification.rec.width - confirmButton.rec.width)/2);
    confirmButton.rec.y = round(notification.rec.y + notification.rec.height + confirmButton.rec.height);
    confirmButton.recColor = WHITE;
    confirmButton.thick = 2;
    confirmButton.outlineColor = BLACK;
    confirmButton.text = (char*)(const char*)"OK";
    confirmButton.fontSize = confirmButton.rec.height * 3/5;
    confirmButton.textColor = BLACK;

    notification.draw();
    confirmButton.draw();

    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, confirmButton.rec))
    {
        confirmButton.recColor = LIGHTGRAY;
        confirmButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            confirmButton.recColor = DARKGRAY;
            confirmButton.draw();
            freeze = 0;
        }
        confirmButton.recColor = WHITE;
    }
}

void GraphGUI::ZoomInputArea(InputBox &inputArea)
{
    Rectangle zoomButton = Rectangle{
        round(inputArea.box.rec.x + inputArea.box.rec.width - inputArea.box.rec.width/20 - inputArea.lineSpacing),
        round(inputArea.box.rec.y + inputArea.box.rec.height - inputArea.box.rec.width/20 - inputArea.lineSpacing),
        round(inputArea.box.rec.width / 20),
        round(inputArea.box.rec.width / 20)
    };

    DrawZoomInputAreaButton(zoomButton, inputArea, BLACK);
   
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, zoomButton))
    {
        DrawZoomInputAreaButton(zoomButton, inputArea, LIGHTGRAY);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            DrawZoomInputAreaButton(zoomButton, inputArea, DARKGRAY);

            if (inputArea.box.rec.x != G.workspace.x && inputArea.box.rec.y != G.workspace.y)
            {
                inputArea.box.rec = G.workspace;
                inputArea.displayedLines = (inputArea.box.rec.height - inputArea.lineSpacing) / (inputArea.fontSize + inputArea.lineSpacing);
                inputArea.maxLenPerLine = inputArea.box.rec.width - inputArea.lineSpacing*2;
                inputArea.box.outlineColor = WHITE;
            }
            else
            {
                inputArea.displayedLines = 3;
                inputArea.box.rec = inputArea.defaultPos;
                inputArea.maxLenPerLine = inputArea.box.rec.width - inputArea.lineSpacing*2;
                inputArea.box.outlineColor = BLACK;
            }
        }
    }
}

void GraphGUI::DrawZoomInputAreaButton(Rectangle &zoomButton, InputBox &inputArea, Color color)
{
    float length = round(zoomButton.width / 3);
    DrawRectangle(zoomButton.x, zoomButton.y, zoomButton.width, zoomButton.height, WHITE);

    if (inputArea.box.rec.x != G.workspace.x && inputArea.box.rec.y != G.workspace.y)
    {
        DrawLineEx(Vector2{zoomButton.x, zoomButton.y}, Vector2{zoomButton.x, zoomButton.y + length}, inputArea.box.thick, color);
        DrawLineEx(Vector2{zoomButton.x, zoomButton.y}, Vector2{zoomButton.x + length, zoomButton.y}, inputArea.box.thick, color);
        
        DrawLineEx(Vector2{zoomButton.x + zoomButton.width, zoomButton.y}, Vector2{zoomButton.x + zoomButton.width, zoomButton.y + length}, inputArea.box.thick, color);
        DrawLineEx(Vector2{zoomButton.x + zoomButton.width, zoomButton.y}, Vector2{zoomButton.x + zoomButton.width - length, zoomButton.y}, inputArea.box.thick, color);
        
        DrawLineEx(Vector2{zoomButton.x, zoomButton.y + zoomButton.height}, Vector2{zoomButton.x + length, zoomButton.y + zoomButton.height}, inputArea.box.thick, color);
        DrawLineEx(Vector2{zoomButton.x, zoomButton.y + zoomButton.height}, Vector2{zoomButton.x, zoomButton.y + zoomButton.height - length}, inputArea.box.thick, color);
        
        DrawLineEx(Vector2{zoomButton.x + zoomButton.width, zoomButton.y + zoomButton.height}, Vector2{zoomButton.x + zoomButton.width - length, zoomButton.y + zoomButton.height}, inputArea.box.thick, color);
        DrawLineEx(Vector2{zoomButton.x + zoomButton.width, zoomButton.y + zoomButton.height}, Vector2{zoomButton.x + zoomButton.width, zoomButton.y + zoomButton.height - length}, inputArea.box.thick, color);
    }
    else
    {
        DrawLineEx(Vector2{zoomButton.x + length, zoomButton.y}, Vector2{zoomButton.x + length, zoomButton.y + length}, inputArea.box.thick, color);
        DrawLineEx(Vector2{zoomButton.x + length, zoomButton.y + length}, Vector2{zoomButton.x, zoomButton.y + length}, inputArea.box.thick, color);

        DrawLineEx(Vector2{zoomButton.x + zoomButton.width - length, zoomButton.y + length}, Vector2{zoomButton.x + zoomButton.width - length, zoomButton.y}, inputArea.box.thick, color);
        DrawLineEx(Vector2{zoomButton.x + zoomButton.width - length, zoomButton.y + length}, Vector2{zoomButton.x + zoomButton.width, zoomButton.y + length}, inputArea.box.thick, color);

        DrawLineEx(Vector2{zoomButton.x + length, zoomButton.y + zoomButton.height - length}, Vector2{zoomButton.x, zoomButton.y + zoomButton.height - length}, inputArea.box.thick, color);
        DrawLineEx(Vector2{zoomButton.x + length, zoomButton.y + zoomButton.height - length}, Vector2{zoomButton.x + length, zoomButton.y + zoomButton.height}, inputArea.box.thick, color);

        DrawLineEx(Vector2{zoomButton.x + zoomButton.width - length, zoomButton.y + zoomButton.height - length}, Vector2{zoomButton.x + zoomButton.width, zoomButton.y + zoomButton.height - length}, inputArea.box.thick, color);
        DrawLineEx(Vector2{zoomButton.x + zoomButton.width - length, zoomButton.y + zoomButton.height - length}, Vector2{zoomButton.x + zoomButton.width - length, zoomButton.y + zoomButton.height}, inputArea.box.thick, color);
    }
}