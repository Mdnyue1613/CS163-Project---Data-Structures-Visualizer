#pragma once
#include "PTitleBox.h"
#include "PConstants.h"
#include <vector>
#include <string>
#include <array>

struct PSwitchBox : public PTitleBox {
    /*
        This is a box with two arrows: leftward and rightward.
        When user clicks on the arrows, the current option (optionID) will change (to either the previous or the next one).
        The next option of the last option is the first one.
        The previous option of the first one is the last one.
        The box will draw content corresponding to the chosen option.
    */
    struct SwitchArrow {
        /*
            Abstract structure for the switch arrows.
            When user clicks on the rightward arrow, the optionID++.
            When user clicks on the leftward arrow, the optionID--.
        */
        array<Vector2, 3> arrowHead;

        SwitchArrow(void);
        SwitchArrow(Vector2 a, Vector2 b, Vector2 c);
        void draw(void);
        bool isMouseOn(void);
        bool isClick(void);
    };

    int optionID;
    vector<string> options;
    SwitchArrow leftArrowHead, rightArrowHead;

    PSwitchBox(void); // Default initialization
    PSwitchBox(Vector2 pos, Vector2 size, int outThickness, Color inColor, Color outColor, vector<string> options, int textSize); // Initialize with parameters
    void draw(void);
    int update(void); // Update when user interact with the box
};