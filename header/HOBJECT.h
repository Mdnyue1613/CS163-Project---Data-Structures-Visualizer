#pragma once

#include "raylib.h"
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

struct TextBox
{
    Rectangle rec;
    Color recColor;
    float thick;
    Color outlineColor;
    const char *text;
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
    Rectangle defaultPos;
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
    float lineSpacing;
    Color inputColor;
    void draw();
    void activate();
    int findDisplayedLength(string &s, int start);
    int findFirstChar(string &s, int end);
    void BACKSPACE();
    void ENTER();
    void NAVIGATION();
    void clear();
};

struct PauseButton
{
    Rectangle rec;
    void draw(Color color);
    bool activate();
};

struct NextButton
{
    Rectangle rec;
    void draw(Color color);
    bool activate();
};

struct BackButton
{
    Rectangle rec;
    void draw(Color color);
    bool activate();
};

struct SkipToEndButton
{
    Rectangle rec;
    void draw(Color color);
    bool activate();
};

struct BackToStartButton
{
    Rectangle rec;
    void draw(Color color);
    bool activate();
};

struct Slider
{
    Rectangle bar;
    Rectangle thumb;
    Vector2 lastMousePos;
    float unit;
    float minValue;
    bool isClick;
    void draw(Color barColor, Color thumbColor);
    Vector2 activate();
};

struct State
{
    vector <int> distance;
    vector <bool> isFound;
    vector <int> trace;
    vector <int> prevTrace;
    int u;
    int v;
    int step;
    float startTime;
    float animationProcess;
    bool isDone;
    State(vector <int> Distance, vector <bool> IsFound, vector <int> Trace, vector <int> PrevTrace, int U, int V, int Step, float StartTime, float AnimationProcess, bool IsDone)
    {
        distance = Distance;
        isFound = IsFound;
        trace = Trace;
        prevTrace = PrevTrace;
        u = U;
        v = V;
        step = Step;
        startTime = StartTime;
        animationProcess = AnimationProcess;
        isDone = IsDone;
    };
};

struct ControlPanel
{
    Rectangle rec;
    float speed;
    Slider speedSlider;
    Slider statusSlider;
    PauseButton pauseButton;
    NextButton nextButton;
    BackButton backButton;
    SkipToEndButton skipToEndButton;
    BackToStartButton backToStartButton;
    void draw();
    void drawSpeed(Rectangle bar, float margin, float fontSize);
    void activateSpeedSilder(float &duration, int current, vector <State> &states);
    void activateStatusSlider(int &current, vector <State> &states, float duration);
    void activatePauseButton(bool &isStop);
    void activateNextButton(int &current, vector <State> &states, float duration);
    void activateBackButton(int &current, vector <State> &states);
    void activateSkipToEndButton(int &current, vector <State> &states, float duration);
    void activateBackToStartButton(int &current, vector <State> &states);
};

struct ScrollingTable
{
    int numColumn;
    Rectangle table;
    Rectangle scrollBox;
    Vector2 scrollPoint;
    vector <string> label;
    vector <vector<string> > data;
    float fontSize;
    vector <float> colWidth;
    float rowHeight;
    void draw();
    void scroll();
    void focus(int vertex);
    void drawImportantLine(int vertex, Color color);
    void clear();
};

