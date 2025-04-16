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
vector <const char*> GraphGUI::listFunction = {"Initialize", "Add", "Delete", "Dijkstra"};
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
TextBox GraphGUI::guideTitle;
Vector2 GraphGUI::guidePos;
float GraphGUI::guideFontSize;
float GraphGUI::guideLineSpacing;
vector <string> GraphGUI::guideInitialize;
vector <string> GraphGUI::guideAdd;
vector <string> GraphGUI::guideDelete;
Graph GraphGUI::G;
DijkstraVisualize GraphGUI::Dijkstra;

void GraphGUI::GraphVisualize()
{
    InitObject();   

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

void GraphGUI::InitObject()
{
    InitBackGround();
    InitCustomizeGraphTypeFunction();
    InitTitleNavigationFunction();
    InitInitializeFunction();
    InitAddFunction();
    InitDeleteFunction();

    GoButton.recColor = WHITE;
    GoButton.thick = 2;
    GoButton.outlineColor = BLACK;
    GoButton.text = (const char*)"GO!";
    GoButton.textColor = RED;

    guideTitle.rec = undirectedButton.rec;
    guideTitle.rec.y = guideBG.rec.y + (guideBG.rec.height - guideTitle.rec.height)/2;
    guideTitle.rec.width = guideBG.rec.width - margin*2*2;
    guideTitle.recColor = WHITE;
    guideTitle.thick = 2;
    guideTitle.outlineColor = BLACK;
    guideTitle.text = (const char*)"User Manual";
    guideTitle.fontSize = guideTitle.rec.height * 2/3;
    guideTitle.textColor = BLACK;
    guidePos = {explainBG.rec.x + margin*3, explainBG.rec.y + margin*3};
    guideFontSize = 17;
    guideLineSpacing = 7;

    InitShortedPathFunction();
    
    G.Initialize();
    G.workspace = Rectangle{
        graphTypeBG.rec.x + graphTypeBG.rec.width, 
        header.rec.y + header.rec.height, 
        GetScreenWidth() - (graphTypeBG.rec.x + graphTypeBG.rec.width), 
        GetScreenHeight() - (header.rec.y + header.rec.height)
    };
}

void GraphGUI::InitBackGround()
{
    header.rec = Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()/10};
    header.recColor = SEASHELL;
    header.thick = 4;
    header.outlineColor = BLACK;
    header.text = (const char*)"Graph";
    header.fontSize = header.rec.height * 3/5;
    header.textColor = BLACK;

    graphTypeBG.rec = Rectangle{header.thick, header.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight()/16};
    graphTypeBG.recColor = MINTGREEN;
    graphTypeBG.thick = 0;
    graphTypeBG.outlineColor = BLACK;
    graphTypeBG.text = (const char*)"";
    graphTypeBG.fontSize = 0;
    graphTypeBG.textColor = BLACK;

    functionBG.rec = Rectangle{header.thick, graphTypeBG.rec.y + graphTypeBG.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight()/3};
    functionBG.recColor = MAYABLUE;
    functionBG.thick = 0;
    functionBG.outlineColor = BLACK;
    functionBG.text = (const char*)"";
    functionBG.fontSize = 0;
    functionBG.textColor = BLACK;
    functionBG.draw();

    guideBG.rec = Rectangle{header.thick, functionBG.rec.y + functionBG.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight()/16};
    guideBG.recColor = TURQUOISE;
    guideBG.thick = 0;
    guideBG.outlineColor = BLACK;
    guideBG.text = (const char*)"";
    guideBG.fontSize = 0;
    guideBG.textColor = BLACK;

    explainBG.rec = Rectangle{header.thick, guideBG.rec.y + guideBG.rec.height + margin, (float)GetScreenWidth()/4, (float)GetScreenHeight() - guideBG.rec.x - guideBG.rec.height};
    explainBG.recColor = PASTELGREEN;
    explainBG.thick = 0;
    explainBG.outlineColor = BLACK;
    explainBG.text = (const char*)"";
    explainBG.fontSize = 0;
    explainBG.textColor = BLACK;
}

void GraphGUI::InitCustomizeGraphTypeFunction()
{
    undirectedButton.rec.width = round((graphTypeBG.rec.width - margin*2*3) / 2); 
    undirectedButton.rec.height = round(graphTypeBG.rec.height * 2/3);
    undirectedButton.rec.x = round(graphTypeBG.rec.x + margin*2);
    undirectedButton.rec.y = round(graphTypeBG.rec.y + (graphTypeBG.rec.height - undirectedButton.rec.height)/2);
    undirectedButton.recColor = GRAY;
    undirectedButton.thick = 2;
    undirectedButton.outlineColor = BLACK;
    undirectedButton.text = (const char*)"Undirected";
    undirectedButton.fontSize = undirectedButton.rec.height * 3/5;
    undirectedButton.textColor = BLACK;

    directedButton.rec.width = round((graphTypeBG.rec.width - margin*2*3) / 2); 
    directedButton.rec.height = round(graphTypeBG.rec.height * 2/3);
    directedButton.rec.x = round(graphTypeBG.rec.x + undirectedButton.rec.width + margin*2*2);
    directedButton.rec.y = round(graphTypeBG.rec.y + (graphTypeBG.rec.height - undirectedButton.rec.height)/2);
    directedButton.recColor = WHITE;
    directedButton.thick = 2;
    directedButton.outlineColor = BLACK;
    directedButton.text = (const char*)"Directed";
    directedButton.fontSize = directedButton.rec.height * 3/5;
    directedButton.textColor = BLACK;
}

void GraphGUI::InitTitleNavigationFunction()
{
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
}

void GraphGUI::InitInitializeFunction()
{
    chooseFileButton.rec.width = round((functionBG.rec.width - margin*2*3) / 2); 
    chooseFileButton.rec.height = round(functionBG.rec.height / 8);
    chooseFileButton.rec.x = round(functionBG.rec.x + margin*2);
    chooseFileButton.rec.y = round(functionTitle.rec.y + functionTitle.rec.height + margin*2);
    chooseFileButton.recColor = WHITE;
    chooseFileButton.thick = 2;
    chooseFileButton.outlineColor = BLACK;
    chooseFileButton.text = (const char*)"From File";
    chooseFileButton.fontSize = chooseFileButton.rec.height * 3/5;
    chooseFileButton.textColor = BLACK;

    randomButton.rec.width = round((functionBG.rec.width - margin*2*3) / 2); 
    randomButton.rec.height = round(functionBG.rec.height / 8);
    randomButton.rec.x = round(functionBG.rec.x + randomButton.rec.width + margin*2*2);
    randomButton.rec.y = round(functionTitle.rec.y + functionTitle.rec.height + margin*2);
    randomButton.recColor = WHITE;
    randomButton.thick = 2;
    randomButton.outlineColor = BLACK;
    randomButton.text = (const char*)"Random";
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
    inputBox.box.text = (const char*)"Enter your data";
    inputBox.box.fontSize = inputBox.box.rec.height / inputBox.displayedLines * 3/5;
    inputBox.box.textColor = GRAY;
    inputBox.userInput.resize(1);
    inputBox.fontSize = inputBox.box.fontSize;
    inputBox.lineSpacing = (inputBox.box.rec.height - inputBox.fontSize * inputBox.displayedLines) / (inputBox.displayedLines + 1);
    inputBox.maxLenPerLine = inputBox.box.rec.width - inputBox.lineSpacing*2;
    inputBox.inputColor = BLACK;

    guideInitialize.clear();
    guideInitialize.push_back("Input format:");
    guideInitialize.push_back("    1. Adjacency list");
    guideInitialize.push_back("       n m");
    guideInitialize.push_back("       u(1) v(1) w(1)");
    guideInitialize.push_back("          ...");
    guideInitialize.push_back("       u(m) v(m) w(m)");
    guideInitialize.push_back("");
    guideInitialize.push_back("    2. Adjacency matrix");
    guideInitialize.push_back("       n");
    guideInitialize.push_back("       a(1,1) a(1,2) ... a(1,n)");
    guideInitialize.push_back("                     ...");
    guideInitialize.push_back("       a(n,1) a(n,2) ... a(n,n)");
}

void GraphGUI::InitAddFunction()
{
    addBox.displayedLines = 3;
    addBox.defaultPos.width = round((functionBG.rec.width - margin*2*2)); 
    addBox.defaultPos.height = round(functionBG.rec.height/8 * addBox.displayedLines);
    addBox.defaultPos.x = round(functionBG.rec.x + margin*2);
    addBox.defaultPos.y = round(functionTitle.rec.y + functionTitle.rec.height + margin*2);
    addBox.box.rec = addBox.defaultPos;
    addBox.box.recColor = WHITE;
    addBox.box.thick = 2;
    addBox.box.outlineColor = BLACK;
    addBox.box.text = (const char*)"Enter your data";
    addBox.box.fontSize = addBox.box.rec.height / addBox.displayedLines * 3/5;
    addBox.box.textColor = GRAY;
    addBox.userInput.resize(1);
    addBox.fontSize = addBox.box.fontSize;
    addBox.lineSpacing = (addBox.box.rec.height - addBox.fontSize * addBox.displayedLines) / (addBox.displayedLines + 1);
    addBox.maxLenPerLine = addBox.box.rec.width - addBox.lineSpacing*2;
    addBox.inputColor = BLACK;

    guideAdd.clear();
    guideAdd.push_back("Input format:");
    guideAdd.push_back("    1. Add vertex: u");
    guideAdd.push_back("    2. Add edge: u v w");
    guideAdd.push_back("* You can add several edges or");
    guideAdd.push_back("  vertices in a single operation");
}

void GraphGUI::InitDeleteFunction()
{
    deleteBox.displayedLines = 3;
    deleteBox.defaultPos.width = round((functionBG.rec.width - margin*2*2)); 
    deleteBox.defaultPos.height = round(functionBG.rec.height/8 * deleteBox.displayedLines);
    deleteBox.defaultPos.x = round(functionBG.rec.x + margin*2);
    deleteBox.defaultPos.y = round(functionTitle.rec.y + functionTitle.rec.height + margin*2);
    deleteBox.box.rec = deleteBox.defaultPos;
    deleteBox.box.recColor = WHITE;
    deleteBox.box.thick = 2;
    deleteBox.box.outlineColor = BLACK;
    deleteBox.box.text = (const char*)"Enter your data";
    deleteBox.box.fontSize = deleteBox.box.rec.height / deleteBox.displayedLines * 3/5;
    deleteBox.box.textColor = GRAY;
    deleteBox.userInput.resize(1);
    deleteBox.fontSize = deleteBox.box.fontSize;
    deleteBox.lineSpacing = (deleteBox.box.rec.height - deleteBox.fontSize * deleteBox.displayedLines) / (deleteBox.displayedLines + 1);
    deleteBox.maxLenPerLine = deleteBox.box.rec.width - deleteBox.lineSpacing*2;
    deleteBox.inputColor = BLACK;

    guideDelete.clear();
    guideDelete.push_back("Input format:");
    guideDelete.push_back("    1. Delete vertex: u");
    guideDelete.push_back("    2. Delete edge: u v w");
    guideDelete.push_back("* You can delete several edges");
    guideDelete.push_back("  or vertices in a single operation");
}

void GraphGUI::InitShortedPathFunction()
{
    Dijkstra.isDone = 0;
    Dijkstra.isStop = 0;
    Dijkstra.isStatusSilderWork = 0;
    Dijkstra.descriptionMode = 0;
    Dijkstra.descriptionFontSize = guideFontSize;
    Dijkstra.descriptionLineSpacing = guideLineSpacing;
    Dijkstra.descriptionPos = guidePos;
    Dijkstra.duration = 1.5f;
    Dijkstra.mode = 0;
    Dijkstra.startVertex = -1;
    Dijkstra.endVertex = -1;
    Dijkstra.current = -1;
    Dijkstra.states.clear();

    Dijkstra.autoButton.rec.width = round((functionBG.rec.width - margin*2*3) / 2); 
    Dijkstra.autoButton.rec.height = round(functionBG.rec.height / 8);
    Dijkstra.autoButton.rec.x = round(functionBG.rec.x + margin*2);
    Dijkstra.autoButton.rec.y = round(functionTitle.rec.y + functionTitle.rec.height + margin*2);
    Dijkstra.autoButton.recColor = GRAY;
    Dijkstra.autoButton.thick = 2;
    Dijkstra.autoButton.outlineColor = BLACK;
    Dijkstra.autoButton.text = (const char*)"Auto";
    Dijkstra.autoButton.fontSize = Dijkstra.autoButton.rec.height * 3/5;
    Dijkstra.autoButton.textColor = BLACK;

    Dijkstra.stepByStepButton.rec.width = round((functionBG.rec.width - margin*2*3) / 2); 
    Dijkstra.stepByStepButton.rec.height = round(functionBG.rec.height / 8);
    Dijkstra.stepByStepButton.rec.x = round(functionBG.rec.x + Dijkstra.stepByStepButton.rec.width + margin*2*2);
    Dijkstra.stepByStepButton.rec.y = round(functionTitle.rec.y + functionTitle.rec.height + margin*2);
    Dijkstra.stepByStepButton.recColor = WHITE;
    Dijkstra.stepByStepButton.thick = 2;
    Dijkstra.stepByStepButton.outlineColor = BLACK;
    Dijkstra.stepByStepButton.text = (const char*)"Step by step";
    Dijkstra.stepByStepButton.fontSize = Dijkstra.stepByStepButton.rec.height * 3/5;
    Dijkstra.stepByStepButton.textColor = BLACK;

    Dijkstra.inputBox.displayedLines = 1;
    Dijkstra.inputBox.defaultPos.width = round((functionBG.rec.width - margin*2*2)); 
    Dijkstra.inputBox.defaultPos.height = round(functionBG.rec.height/8 * Dijkstra.inputBox.displayedLines);
    Dijkstra.inputBox.defaultPos.x = round(functionBG.rec.x + margin*2);
    Dijkstra.inputBox.defaultPos.y = round(functionTitle.rec.y + functionTitle.rec.height + randomButton.rec.height + margin*2*2);
    Dijkstra.inputBox.box.rec = Dijkstra.inputBox.defaultPos;
    Dijkstra.inputBox.box.recColor = WHITE;
    Dijkstra.inputBox.box.thick = 2;
    Dijkstra.inputBox.box.outlineColor = BLACK;
    Dijkstra.inputBox.box.text = (const char*)"Enter your data";
    Dijkstra.inputBox.box.fontSize = Dijkstra.inputBox.box.rec.height / Dijkstra.inputBox.displayedLines * 3/5;
    Dijkstra.inputBox.box.textColor = GRAY;
    Dijkstra.inputBox.userInput.resize(1);
    Dijkstra.inputBox.fontSize = Dijkstra.inputBox.box.fontSize;
    Dijkstra.inputBox.lineSpacing = (Dijkstra.inputBox.box.rec.height - Dijkstra.inputBox.fontSize * Dijkstra.inputBox.displayedLines) / (Dijkstra.inputBox.displayedLines + 1);
    Dijkstra.inputBox.maxLenPerLine = Dijkstra.inputBox.box.rec.width - Dijkstra.inputBox.lineSpacing*2;
    Dijkstra.inputBox.inputColor = BLACK;

    Dijkstra.controlPanel.rec = Rectangle{
        round(functionBG.rec.x + margin*2),
        round(Dijkstra.inputBox.box.rec.y + Dijkstra.inputBox.box.rec.height + margin*2),
        round((functionBG.rec.width - margin*2*2)),
        round(functionBG.rec.height / 3.5f)
    };
    float size = Dijkstra.controlPanel.rec.height / 5;
    float space = margin*3;
    float tmp = (Dijkstra.controlPanel.rec.width - size*7 - space*4) / 2;
    Dijkstra.controlPanel.backToStartButton.rec.height = size;
    Dijkstra.controlPanel.backToStartButton.rec.width = size * 2;
    Dijkstra.controlPanel.backToStartButton.rec.x = Dijkstra.controlPanel.rec.x + tmp;
    Dijkstra.controlPanel.backToStartButton.rec.y = Dijkstra.controlPanel.rec.y + Dijkstra.controlPanel.rec.height - size;

    Dijkstra.controlPanel.backButton.rec.height = size;
    Dijkstra.controlPanel.backButton.rec.width = size;
    Dijkstra.controlPanel.backButton.rec.x = Dijkstra.controlPanel.rec.x + tmp + size*2 + space;
    Dijkstra.controlPanel.backButton.rec.y = Dijkstra.controlPanel.rec.y + Dijkstra.controlPanel.rec.height - size;

    Dijkstra.controlPanel.pauseButton.rec.height = size;
    Dijkstra.controlPanel.pauseButton.rec.width = size;
    Dijkstra.controlPanel.pauseButton.rec.x = Dijkstra.controlPanel.rec.x + tmp + size*3 + space*2;
    Dijkstra.controlPanel.pauseButton.rec.y = Dijkstra.controlPanel.rec.y + Dijkstra.controlPanel.rec.height - size;

    Dijkstra.controlPanel.nextButton.rec.height = size;
    Dijkstra.controlPanel.nextButton.rec.width = size;
    Dijkstra.controlPanel.nextButton.rec.x = Dijkstra.controlPanel.rec.x + tmp + size*4 + space*3;
    Dijkstra.controlPanel.nextButton.rec.y = Dijkstra.controlPanel.rec.y + Dijkstra.controlPanel.rec.height - size;

    Dijkstra.controlPanel.skipToEndButton.rec.height = size;
    Dijkstra.controlPanel.skipToEndButton.rec.width = size*2;
    Dijkstra.controlPanel.skipToEndButton.rec.x = Dijkstra.controlPanel.rec.x + tmp + size*5 + space*4;
    Dijkstra.controlPanel.skipToEndButton.rec.y = Dijkstra.controlPanel.rec.y + Dijkstra.controlPanel.rec.height - size;

    Dijkstra.controlPanel.statusSlider.bar.width = Dijkstra.controlPanel.rec.width;
    Dijkstra.controlPanel.statusSlider.bar.height = Dijkstra.controlPanel.rec.height / 10;
    Dijkstra.controlPanel.statusSlider.bar.x = Dijkstra.controlPanel.rec.x;
    Dijkstra.controlPanel.statusSlider.bar.y = Dijkstra.controlPanel.rec.y + Dijkstra.controlPanel.rec.height - Dijkstra.controlPanel.pauseButton.rec.height - margin*2 - Dijkstra.controlPanel.statusSlider.bar.height;
    Dijkstra.controlPanel.statusSlider.thumb = Dijkstra.controlPanel.statusSlider.bar;
    Dijkstra.controlPanel.statusSlider.thumb.width = Dijkstra.controlPanel.statusSlider.thumb.height * 2;
    Dijkstra.controlPanel.statusSlider.isClick = 0;
    Dijkstra.controlPanel.statusSlider.minValue = 0;

    float fontSize = Dijkstra.autoButton.fontSize;
    float textLen = MeasureText((const char*)"Speed:", fontSize);
    Dijkstra.controlPanel.speedSlider.bar.width = Dijkstra.controlPanel.rec.width - textLen - margin*2;
    Dijkstra.controlPanel.speedSlider.bar.height = Dijkstra.controlPanel.rec.height / 10;
    Dijkstra.controlPanel.speedSlider.bar.x = Dijkstra.controlPanel.rec.x + textLen + margin*2;
    Dijkstra.controlPanel.speedSlider.bar.y = Dijkstra.controlPanel.statusSlider.bar.y - margin*2 - (fontSize - Dijkstra.controlPanel.speedSlider.bar.height)/2 - Dijkstra.controlPanel.speedSlider.bar.height;
    Dijkstra.controlPanel.speedSlider.thumb = Dijkstra.controlPanel.speedSlider.bar;
    Dijkstra.controlPanel.speedSlider.thumb.width = Dijkstra.controlPanel.speedSlider.thumb.height * 2;
    Dijkstra.controlPanel.speedSlider.unit = (Dijkstra.controlPanel.speedSlider.bar.width - Dijkstra.controlPanel.speedSlider.thumb.width) / 7;
    Dijkstra.controlPanel.speedSlider.thumb.x = Dijkstra.controlPanel.speedSlider.bar.x + Dijkstra.controlPanel.speedSlider.unit*3;
    Dijkstra.controlPanel.speedSlider.isClick = 0;
    Dijkstra.controlPanel.speedSlider.minValue = 0.25f;

    Dijkstra.controlPanel.speed = 1;

    Dijkstra.guideButton = Dijkstra.autoButton;
    Dijkstra.guideButton.rec.y = round(guideBG.rec.y + (guideBG.rec.height - Dijkstra.guideButton.rec.height)/2);
    Dijkstra.guideButton.text = (const char*)"User Manual";
    Dijkstra.guide.clear();
    Dijkstra.guide.push_back("Input format:");
    Dijkstra.guide.push_back("    1. Find shorted path between");
    Dijkstra.guide.push_back("       two vertices: u v");
    Dijkstra.guide.push_back("    2. Find shorted path from one");
    Dijkstra.guide.push_back("       to other vertices: u");

    Dijkstra.pseudoButton = Dijkstra.guideButton;
    Dijkstra.pseudoButton.rec.x = round(Dijkstra.guideButton.rec.x + Dijkstra.guideButton.rec.width + Dijkstra.guideButton.rec.x - guideBG.rec.x);
    Dijkstra.pseudoButton.recColor = WHITE;
    Dijkstra.pseudoButton.text = (const char*)"Pseudocode";
    Dijkstra.pseudo.clear();
    Dijkstra.pseudo.push_back("for v : vertices: dist[v] = INF");
    Dijkstra.pseudo.push_back("dist[start] = 0, PQ.push({0, start})");
    Dijkstra.pseudo.push_back("while !PQ.empty() && !isFound[end]");
    Dijkstra.pseudo.push_back("    (u, d) = PQ.top(), PQ.pop()");
    Dijkstra.pseudo.push_back("    if d > dist[u]: continue");
    Dijkstra.pseudo.push_back("    for (v, w) : u.edges");
    Dijkstra.pseudo.push_back("        if dist[v] > dist[u] + w:");
    Dijkstra.pseudo.push_back("            dist[v] = dist[u] + w");
    Dijkstra.pseudo.push_back("            PQ.push({dist[v], v})");
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
    DrawCustomizeGraphTypeFunction();
    DrawTitle(listFunction[currentFunction]);

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

void GraphGUI::DrawCustomizeGraphTypeFunction()
{
    undirectedButton.draw();
    directedButton.draw();

    if (currentFunction == listFunction.size() - 1)
        return;

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

void GraphGUI::DrawTitle(const char* nameFunction)
{
    functionTitle.text = nameFunction;
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
            if (G.workspace.width != GetScreenWidth() - (graphTypeBG.rec.x + graphTypeBG.rec.width))
            {
                G.workspace.width = GetScreenWidth() - (graphTypeBG.rec.x + graphTypeBG.rec.width);
                G.stable = 0;
            }

            if (currentFunction == listFunction.size() - 1)
                Dijkstra.clear();

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
            if (G.workspace.width != GetScreenWidth() - (graphTypeBG.rec.x + graphTypeBG.rec.width))
            {
                G.workspace.width = GetScreenWidth() - (graphTypeBG.rec.x + graphTypeBG.rec.width);
                G.stable = 0;
            }

            if (currentFunction == listFunction.size() - 1)
                Dijkstra.clear();

            currentFunction++;
            if (currentFunction == listFunction.size()) currentFunction = 0;
        }
        rightNavigationButton.color = WHITE; 
    }
}

void GraphGUI::DrawGuide(vector <string> &guide)
{
    guideTitle.draw();
    for (int i = 0; i < guide.size(); i++)
    {
        float posX = guidePos.x;
        float posY = guidePos.y + i * (guideFontSize + guideLineSpacing);
            
        DrawText(guide[i].c_str(), posX, posY, guideFontSize, BLACK);
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
                Dijkstra.clear();
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
            Dijkstra.clear();
        }
        randomButton.recColor = WHITE;
    }
    
    inputBox.draw();
    ZoomInputArea(inputBox);
    if (!freeze) inputBox.activate();
    
    if (inputBox.box.rec.x != G.workspace.x && inputBox.box.rec.y != G.workspace.y)
    {
        GoButton.rec.x = round(functionBG.rec.x + margin*2);
        GoButton.rec.y = round(inputBox.box.rec.y + inputBox.box.rec.height + margin*2);
        GoButton.rec.width = round((functionBG.rec.width - margin*2*2)); 
        GoButton.rec.height = round(functionBG.rec.height / 8);
        GoButton.fontSize = GoButton.rec.height * 3/5;
    }
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
            Dijkstra.clear();
            
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

    DrawGuide(guideInitialize);

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

    DrawGuide(guideAdd);

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

    DrawGuide(guideDelete);

    if (freeze) Notify((char *)(const char*)"");
}

void GraphGUI::DrawShortedPathFunction()
{
    if (Dijkstra.isDone && G.workspace.width == GetScreenWidth() - (graphTypeBG.rec.x + graphTypeBG.rec.width))
    {
        G.workspace.width -= Dijkstra.trackingTable.table.width;
        G.stable = 0;
    }

    if (Dijkstra.mode == 0)
    {
        Dijkstra.autoButton.recColor = GRAY;
        Dijkstra.stepByStepButton.recColor = WHITE;
    }
    else 
    {
        Dijkstra.autoButton.recColor = WHITE;
        Dijkstra.stepByStepButton.recColor = GRAY;
    }

    Dijkstra.autoButton.draw();
    Dijkstra.stepByStepButton.draw();
    if (!freeze) Dijkstra.chooseMode();

    Dijkstra.inputBox.draw();
    ZoomInputArea(Dijkstra.inputBox);
    if (!freeze) Dijkstra.inputBox.activate();

    Dijkstra.controlPanel.draw();
    Dijkstra.controlPanel.drawSpeed(Dijkstra.controlPanel.speedSlider.bar, margin*2, Dijkstra.autoButton.fontSize);
    if (!freeze)
    {
        Dijkstra.controlPanel.activateSpeedSilder(Dijkstra.duration, Dijkstra.current, Dijkstra.states);
        if (Dijkstra.isDone)
        {
            Dijkstra.controlPanel.statusSlider.unit = (Dijkstra.controlPanel.statusSlider.bar.width - Dijkstra.controlPanel.statusSlider.thumb.width) / Dijkstra.states.size();
            Dijkstra.controlPanel.activateStatusSlider(Dijkstra.current, Dijkstra.states, Dijkstra.duration);
            Dijkstra.isStatusSilderWork = Dijkstra.controlPanel.statusSlider.isClick;

            if (Dijkstra.mode == 0) Dijkstra.controlPanel.activatePauseButton(Dijkstra.isStop);
            else Dijkstra.isStop = 0;

            Dijkstra.controlPanel.activateNextButton(Dijkstra.current, Dijkstra.states, Dijkstra.duration);
            Dijkstra.controlPanel.activateBackButton(Dijkstra.current, Dijkstra.states);
            Dijkstra.controlPanel.activateSkipToEndButton(Dijkstra.current, Dijkstra.states, Dijkstra.duration);
            Dijkstra.controlPanel.activateBackToStartButton(Dijkstra.current, Dijkstra.states);
        }
    }

    Dijkstra.guideButton.draw();
    Dijkstra.pseudoButton.draw();
    Dijkstra.chooseDescription();
    Dijkstra.drawDescription();

    GoButton.rec.x = round(functionBG.rec.x + margin*2);
    GoButton.rec.y = round(Dijkstra.controlPanel.rec.y + Dijkstra.controlPanel.rec.height + margin*2);
    GoButton.rec.width = round((functionBG.rec.width - margin*2*2)); 
    GoButton.rec.height = round(functionBG.rec.height / 8);
    GoButton.fontSize = GoButton.rec.height * 3/5;
    
    GoButton.draw();
    Vector2 mouse = GetMousePosition();
    if (!freeze && CheckCollisionPointRec(mouse, GoButton.rec))
    {
        GoButton.recColor = LIGHTGRAY;
        GoButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            GoButton.recColor = DARKGRAY;
            GoButton.draw();
            Dijkstra.clear();
            if (!Dijkstra.loadData(Dijkstra.inputBox.userInput, G))
            {
                GraphGUI::Notify((const char*)"Please check the format and the data of input!!!");
            }
            else 
            {
                Dijkstra.run(G);
                Dijkstra.isDone = 1;
                G.workspace.width = GetScreenWidth() - (graphTypeBG.rec.x + graphTypeBG.rec.width);
                Dijkstra.initTrackingTable(G); 
                G.workspace.width -= Dijkstra.trackingTable.table.width;
                G.stable = 0;
            }
            
            if (!freeze)
            {
                if (Dijkstra.inputBox.box.rec.x == G.workspace.x && Dijkstra.inputBox.box.rec.y == G.workspace.y)
                {
                    Dijkstra.inputBox.displayedLines = 1;
                    Dijkstra.inputBox.box.rec = Dijkstra.inputBox.defaultPos;
                    Dijkstra.inputBox.maxLenPerLine = Dijkstra.inputBox.box.rec.width - Dijkstra.inputBox.lineSpacing*2;
                    Dijkstra.inputBox.box.outlineColor = BLACK;
                }
            }
        }
        GoButton.recColor = WHITE;
    }

    if (!freeze && Dijkstra.isDone)
    { 
        if (Dijkstra.mode == 0 && Dijkstra.controlPanel.statusSlider.isClick == 0 && Dijkstra.states[Dijkstra.current].animationProcess == Dijkstra.duration && !Dijkstra.isStop) 
            Dijkstra.current++;
            
        Dijkstra.current = min(Dijkstra.current, (int)Dijkstra.states.size() - 1);
        
        if (Dijkstra.states[Dijkstra.current].startTime == 0)
            Dijkstra.states[Dijkstra.current].startTime = GetTime();
        
        Dijkstra.view(G, Dijkstra.states[Dijkstra.current]);
    }

    if (freeze) Notify((char *)(const char*)"");
} 

void GraphGUI::Notify(const char *message)
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
    confirmButton.text = (const char*)"OK";
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
    if (!freeze && CheckCollisionPointRec(mouse, zoomButton))
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
