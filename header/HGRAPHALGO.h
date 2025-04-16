#pragma once

#include "raylib.h"
#include "HOBJECT.h"
#include "HGRAPH.h"
#include <vector>

using namespace std;

struct DijkstraVisualize
{
    bool isDone;
    bool isStop;
    bool isStatusSilderWork;
    bool descriptionMode;
    float descriptionFontSize;
    float descriptionLineSpacing;
    Vector2 descriptionPos;
    float duration;
    bool mode;
    int startVertex;
    int endVertex;
    int current;
    vector <State> states;
    TextBox autoButton;
    TextBox stepByStepButton;
    InputBox inputBox;
    ControlPanel controlPanel;
    TextBox guideButton;
    TextBox pseudoButton;
    vector <string> guide;
    vector <string> pseudo;
    ScrollingTable trackingTable;
    void chooseMode();
    void chooseDescription();
    void drawDescription();
    bool loadData(vector <string> &userInput, Graph &G);
    void run(Graph &G);
    void initTrackingTable(Graph &G);
    void updateTrackingTable();
    void view(Graph &G, State &state);
    void Step0(Graph &G, State &state);
    void Step1(Graph &G, State &state);
    void Step2(Graph &G, State &state);
    void Step3(Graph &G, State &state);
    void Step4(Graph &G, State &state);
    void Step5(Graph &G, State &state);
    void Step6(Graph &G, State &state);
    void clear();
};

