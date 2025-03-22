#include "raylib.h"
#include <string>
using namespace std;

struct TEXTBOX
{
    Rectangle rec;
    Color recColor;
    int upperline;
    int lowerline;
    int leftline;
    int rightline;
    Color outlineColor;
    char *text;
    int fontSize;
    Color textColor;
    void draw();
};
