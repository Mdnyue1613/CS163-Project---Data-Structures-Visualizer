#pragma once

#include "raylib.h"
#include "tinyfiledialogs.h"
#include "HOBJECT.h"
#include "HGRAPH.h"
#include "HGRAPHALGO.h"

using namespace std;

struct GraphGUI
{
    static TextBox header;
    static TextBox graphTypeBG;
    static TextBox functionBG;
    static TextBox guideBG;
    static TextBox explainBG;
    static int margin;
    static bool freeze;
    static TextBox notification;
    static int currentFunction;
    static vector <const char*> listFunction;
    static TextBox undirectedButton;
    static TextBox directedButton;
    static NavigateButton leftNavigationButton;
    static NavigateButton rightNavigationButton;
    static TextBox functionTitle;
    static TextBox chooseFileButton;
    static TextBox randomButton;
    static InputBox inputBox;
    static InputBox addBox;
    static InputBox deleteBox;
    static TextBox GoButton;
    static TextBox guideTitle;
    static Vector2 guidePos;
    static float guideFontSize;
    static float guideLineSpacing;
    static vector <string> guideInitialize;
    static vector <string> guideAdd;
    static vector <string> guideDelete;
    static Graph G;
    static DijkstraVisualize Dijkstra;

    static void GraphVisualize();

    static void InitObject();
    static void InitBackGround();
    static void InitCustomizeGraphTypeFunction();
    static void InitTitleNavigationFunction();
    static void InitInitializeFunction();
    static void InitAddFunction();
    static void InitDeleteFunction();
    static void InitShortedPathFunction();

    static void DrawBackGround();
    static void DrawFunction();
    static void DrawCustomizeGraphTypeFunction();
    static void DrawTitle(const char* name);
    static void DrawNavigationButton();
    static void DrawGuide(vector <string> &guide);
    static void DrawInitializeFunction();
    static void DrawAddFunction();
    static void DrawDeleteFunction();
    static void DrawShortedPathFunction();

    static void Notify(const char *message);
    static void ZoomInputArea(InputBox &inputArea);
    static void DrawZoomInputAreaButton(Rectangle &zoomButton, InputBox &inputArea, Color color);
};


