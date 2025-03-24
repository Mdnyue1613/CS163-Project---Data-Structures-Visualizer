#include "raylib.h"
// #include "tinyfiledialogs.h"
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
    static NavigateButton leftButton;
    static NavigateButton rightButton;
    static Graph G;
    static void GraphVisualize();
    static void InitializeBackGround();
    static void DrawBackGround();
    static void DrawFunction();

    static void DrawCustomizeGraphType();
    static void DrawTitleFunction(TextBox &title, const char* name);
    static void NavigationButton(TextBox functionTitle);

    static void DrawInitializeFunction(TextBox title);
    static void DrawAddFunction();
    static void DrawDeleteFunction();
    static void DrawUpdateFunction();
    static void DrawSearchFunction();
    static void DrawShortedPathFunction();

};


