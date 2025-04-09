#pragma once

#include "raylib.h"
#include "tinyfiledialogs.h"
#include "HOBJECT.h"
#include "HGRAPH.h"

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

    static Graph G;
    static void GraphVisualize();
    static void InitializeObject();
    static void DrawBackGround();
    static void DrawFunction();

    static void DrawCustomizeGraphType();
    static void DrawTitleFunction(const char* name);
    static void DrawNavigationButton();

    static void DrawInitializeFunction();
    static void DrawAddFunction();
    static void DrawDeleteFunction();
    static void DrawShortedPathFunction();

    static void Notify(char *message);
    static void ZoomInputArea(InputBox &inputArea);
    static void DrawZoomInputAreaButton(Rectangle &zoomButton, InputBox &inputArea, Color color);
};


