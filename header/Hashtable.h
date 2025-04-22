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
    float scale;
    Color outlineColor = BLACK;
    bool highlightSearch;
    bool highlight;
    bool visited; // true if the square is visited
    bool deleted;
    bool isOn; // true if the square is on the mouse
    bool isChoosen; // true if the square is chosen
    
    AnimatedSquare() : x(0), y(0), value(-1), scale(0.5f), 
    highlight(false), highlightSearch(false), visited(false), deleted(false), isOn(false), isChoosen(false){} // Default constructor

    AnimatedSquare(int _x, int _y, int _value);
    
    void draw();
    void setPosition(int x, int y);
    bool isMove();
    bool isClick();
    void update();
};

struct Hashtable{
    PRandom rd;
    vector<AnimatedSquare> table;
    int n;
    int key, originalKey;

    AnimatedSquare * chosenSquare;
    AnimatedSquare * querySquare;

    Hashtable();
    void draw();
    void update();
    void random(int number, int size);
    void build(vector<int>& vi);

};