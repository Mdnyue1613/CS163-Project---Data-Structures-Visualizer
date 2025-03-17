#include <raylib.h>
#include <random>
using namespace std;

struct DoublyLinkedList {
    struct Node {
        const int innerRadius = 26;
        const int outerRadius = 30;
        const int characterSize = 20;
        const int lineThickness = 4;
        const int arrowWidth = 6;
        const int arrowHeight = 8;

        Vector2 center; // Center of the circle
        Vector2 arrowStart, arrowEnd;  // End points of the line
        Vector2 arrowHeadStart1, arrowHeadStart2, arrowHeadStart3; // Coordinates of the arrow head 1
        Vector2 arrowHeadEnd1, arrowHeadEnd2, arrowHeadEnd3; // Coordinates of the arrow head 2
        int direction;
        int data;
        char label[5];
        int labelLength;

        Node *pNext, *pPrev;
        Node(void);
        void draw(void); // draw node and the line (if it exists)
        void makeLabel(void); // make label
        void makeNodeAndLine(void); // make node and line
    };
    
    int n;
    Node *head, *tail;

    DoublyLinkedList(void);
    ~DoublyLinkedList(void);
    void draw(void); // draw the entire list
    void random(int n); // randomize with number of nodes
    void removeAll(void); // remove all nodes
    void insert(int x); // insert a new node
};