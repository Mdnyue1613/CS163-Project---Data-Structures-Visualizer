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
    static void DrawUpdateFunction();
    static void DrawSearchFunction();
    static void DrawShortedPathFunction();

};


