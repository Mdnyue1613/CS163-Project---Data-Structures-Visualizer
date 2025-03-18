#include "raylib.h"
#include <vector>


using namespace std;

struct GUI {
    static bool isOpenMenu;
    static bool isOpenDS1;
    static bool isOpenDS2;
    static bool isOpenDS3;
    static bool isOpenDS4;
    static void startProgram();
    static void drawMenu();
    static void drawDS1();
    static void drawDS2();
    static void drawDS3();
    static void drawDS4();
    static void BACK();
};