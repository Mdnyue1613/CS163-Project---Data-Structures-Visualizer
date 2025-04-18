#pragma once
#include <raylib.h>
#include "PRandom.h"
#include <random>
#include <vector>
using namespace std;
struct AnimatedSquare {
    int x, y;
    int value;
    int id;
    bool appearing;
    float scale;
    int tableSize;
    int elementCount;
    Color outlineColor = BLACK;
    bool highlightSearch;
    bool highlight;
    bool visited; // true if the square is visited
    bool deleted; // true if the square is deleted
    AnimatedSquare() : x(0), y(0), value(-1), scale(1.0f), appearing(false), highlight(false), highlightSearch(false), visited(false), deleted(false) {} // Default constructor

    AnimatedSquare(int _x, int _y, int _value);
    
    void update();
    void draw();
    void setPosition(int x, int y);
};

struct Hashtable{
    PRandom rd;
    vector<AnimatedSquare> table;
    int n;
    int key, originalKey;

    void draw();
    void random(int number, int size);
    void build(vector<int>& vi);

};