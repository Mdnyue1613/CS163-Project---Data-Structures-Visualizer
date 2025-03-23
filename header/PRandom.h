#pragma once
#include <random>
using namespace std;

struct PRandom {
    random_device rd;
    mt19937 gen;

    PRandom(void);
    int random(int From, int To);
};