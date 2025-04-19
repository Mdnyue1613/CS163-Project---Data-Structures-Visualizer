#pragma once
#include "raylib.h"
#include <vector>
#include "DS3.h"
#include "DS1.h"
#include "DS2.h"
#include "LActionBox.h"
#include "HOBJECT.h"
#include <chrono>
using namespace chrono;
using namespace std;

struct GUI {
    static bool isOpenMenu;
    static vector <bool> isOpenDS;
    static Font font;
    static bool ColorMode;
    static ImageButton BackButton;
    static vector <ImageButton> ColorModeButton;
    static vector <Texture2D> BackGround;
    static vector <Color> BackGroundColor;
    static vector <ImageButton> Menu;
    static TextBox TopicBox;
    static vector <TextBox> Title;
    static DS1 linkedListVisualizer;
    static DS2 hashtableVisualizer;
    static DS3 ds3;
    static void startProgram();
    static void drawMenu();
    static void drawDS1();
    static void drawDS2();
    static void drawDS3();
    static void drawDS4();
    static void BACK();
    static void CustomColorMode();
    static void Init();
    static void UnInit();
};