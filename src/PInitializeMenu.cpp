#include "../header/PInitializeMenu.h"

PInitializeMenu::PInitializeMenu(void) {}

PInitializeMenu::~PInitializeMenu(void) {}

PInitializeMenu::PInitializeMenu(int x, int y, int width, int height) :
    x(x), y(y), width(width), height(height) {
    Mode = PSwitchBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + PConstants::PFunctionArea::boxHeight + 2 * PConstants::PFunctionArea::spaceY}, 
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor, 
        {"Random", "Input"}, PConstants::PFunctionArea::textSize);
    InputBox = PInputBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 2 * PConstants::PFunctionArea::boxHeight + 3 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "Number of nodes", PConstants::PFunctionArea::textSize);
    InputFileBox = PIconBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 3 * PConstants::PFunctionArea::boxHeight + 4 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::iconBoxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "Assets/Images/PFileIcon.png");
    GO = PTitleBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + height - PConstants::PFunctionArea::spaceY - PConstants::PFunctionArea::boxHeight}, 
        Vector2{width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::GOColor, 
        "GO", 
        PConstants::PFunctionArea::textSize);
}

PInitializeMenu::PInitializeMenu(Vector2 pos, Vector2 size) :
    x(pos.x), y(pos.y), width(size.x), height(size.y) {
    Mode = PSwitchBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + PConstants::PFunctionArea::boxHeight + 2 * PConstants::PFunctionArea::spaceY}, 
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::outlineBoxColor, 
        {"Random", "Input"}, PConstants::PFunctionArea::textSize);
    InputBox = PInputBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 2 * PConstants::PFunctionArea::boxHeight + 3 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "Number of nodes", PConstants::PFunctionArea::textSize);
    InputFileBox = PIconBox(Vector2{1.f * x + PConstants::PFunctionArea::spaceX, 1.f * y + 3 * PConstants::PFunctionArea::boxHeight + 4 * PConstants::PFunctionArea::spaceY},
        Vector2{1.f * width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight},
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::iconBoxColor,
        PConstants::PFunctionArea::outlineBoxColor,
        "Assets/Images/PFileIcon.png");
    GO = PTitleBox(Vector2{x + PConstants::PFunctionArea::spaceX, y + height - PConstants::PFunctionArea::spaceY - PConstants::PFunctionArea::boxHeight}, 
        Vector2{width - 2 * PConstants::PFunctionArea::spaceX, PConstants::PFunctionArea::boxHeight}, 
        PConstants::PFunctionArea::boxOutlineThickness, 
        PConstants::PFunctionArea::boxColor, 
        PConstants::PFunctionArea::GOColor, 
        "GO", 
        PConstants::PFunctionArea::textSize);
}

void PInitializeMenu::draw(void) {
    // Draw mode button
    Mode.draw();

    // Change title of the input box for each corresponding mode
    InputBox.changeTitle(inputBoxTitle[currentMode]);
    // Draw input box
    InputBox.draw();
    
    // Draw input from file box
    if(currentMode == ModeID::Input) {
        InputFileBox.draw();
    }

    // Draw GO button
    GO.draw();
}

vector<string> PInitializeMenu::update(void) {
    currentMode = Mode.update();

    // Current mode: Random
    if(currentMode == ModeID::Random) {
        /* 
        When the input box has content and user press enter or click GO button
            Return request: input + content
        */
        if(InputBox.hasContent() && 
            (GO.isClick() || (InputBox.isChosen && IsKeyPressed(KEY_ENTER)))) {
            return {"random", InputBox.extract()};
        }
        // Else no input + click go = return random
        else if(GO.isClick()) {
            return {"random"};
        }
    }
    // Current mode: Input
    else if(currentMode == ModeID::Input) {
        /* 
        When the input box has content and user press enter or click GO button
            Return request: input + content
        */
        if(InputBox.hasContent() && 
            (GO.isClick() || (InputBox.isChosen && IsKeyPressed(KEY_ENTER)))) {
            return {"input", InputBox.extract()};
        }
        /*
        When user click on the load input from file box
            Return request: input + file + content
        */
        if(InputFileBox.isClick()) {
            char const * inputTypeFilter[] = {"*.*"};
            char* fileDestination = tinyfd_openFileDialog("Open file", NULL, 1, inputTypeFilter, NULL, 0);
            if(fileDestination) {
                fstream inp(fileDestination, ios::in | ios::binary | ios::ate);

                ifstream::pos_type fileSize = inp.tellg();
                inp.seekg(0, ios::beg);

                vector<char> data(fileSize);
                inp.read(data.data(), fileSize);
                inp.close();
                data.push_back('\0');
                return {"input", data.data()};
            }
        }
    }
    return {"nothing"};
}

void PInitializeMenu::prepare(void) {
    InputFileBox.prepare();
}