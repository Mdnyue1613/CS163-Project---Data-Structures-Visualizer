#include "raylib.h"
#include <vector>
#include <string>

using namespace std;

struct TextBox
{
    Rectangle rec;
    Color recColor;
    float thick;
    Color outlineColor;
    char *text;
    int fontSize;
    Color textColor;
    void draw();
};

struct NavigateButton
{
    Texture2D img;
    Rectangle rec;
    float scale;
    float rotation;
    Color color;
    void draw();
};

struct InputBox
{
    TextBox box;
    vector <string> userInput;
    bool isActive = 0;
    pair <int, int> cursorPos = make_pair(0, 0);
    int displayedLines;
    int maxLenPerLine;
    int firstChar = 0;
    int firstLine = 0;
    float startPress = 0;
    float periodHold = 0.16;
    int fontSize;
    Color inputColor;
    void draw();
    void activate();
    int findDisplayedLength(string &s, int start);
    int findFirstChar(string &s, int end);
    void BACKSPACE();
    void ENTER();
    void NAVIGATION();
};