#pragma once
#include "raylib.h"
#include "HOBJECT.h"
#include "PConstants.h"
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

struct PNotification {
    TextBox notification;
    TextBox confirmButton;
    string notificationText;

    PNotification(void);

    void draw(void);
    void update(void);

    // Converting functions
    vector<int> stringToVectorInt(string& s, int min, int max);
    int getOneNum(string& s, int min, int max);
};