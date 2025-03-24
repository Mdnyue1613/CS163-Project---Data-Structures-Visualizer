#include "raylib.h"

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