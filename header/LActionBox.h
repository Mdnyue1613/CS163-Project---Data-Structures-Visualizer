#pragma once
#include<raylib.h>

#include<vector>
#include<string>
#include<cstring>

using namespace std;

struct LActionBox {
    Rectangle ActionBox;
    Rectangle ModeBox;
    int action;
};