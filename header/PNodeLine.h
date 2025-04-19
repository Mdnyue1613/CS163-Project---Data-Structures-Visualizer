#pragma once
#include<iostream>
#include<raylib.h>
#include<raymath.h>
using namespace std;

struct PNodeLine {
    Vector2 start, end;
    Vector2 head1, head2, head3; // Coordinates of the arrow head: head1 = forward, head2 = left, head3 = right
    bool highlight;

    // Constructor
    PNodeLine(void);

    // Set
    void setDirection(Vector2 start, Vector2 end); // Set the direction of the line
    void setHighlight(bool on); // Set the highlight state

    // Update
    void update(void);

    // Draw
    void draw(void);
};