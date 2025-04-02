#include <raylib.h>
#include "PRandom.h"
#include <random>
using namespace std;
struct AnimatedSquare {
    int x, y;
    int value;
    int id;
    float scale;
    bool appearing;
    AnimatedSquare() : x(0), y(0), value(0), scale(1.0f), appearing(false) {} // Constructor mặc định

    AnimatedSquare(int _x, int _y, int _value);
    
    void update();
    void draw();
    void build (vector<int>& b);
    void setPosition(int x, int y);
};

struct Hashtable{
    PRandom rd;
    vector<AnimatedSquare> table;
    void draw();
    void random(int number);
    void build(vector<int>& vi);
};