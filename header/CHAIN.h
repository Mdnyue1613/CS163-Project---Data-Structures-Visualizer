#include "raylib.h"
#include <vector>

using namespace std;
struct CHAIN {
    struct Node {
        const int innerRadius = 26;
        const int outerRadius = 30;
        const int characterSize = 20;
        const int lineThickness = 4;
        const int arrowWidth = 6;
        const int arrowHeight = 8;
    };

    void draw(void); // draw the entire list
    void random(int n); // randomize with number of elements
    void removeAll(void); // remove all table
void insert(int x); // insert a new number                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    void erase(int x); // erase a number in the table
    void search(int x); // search a specific number in the table 


};
