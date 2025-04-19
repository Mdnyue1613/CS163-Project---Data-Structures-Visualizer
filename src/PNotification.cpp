#include "../header/PNotification.h"
#include "../header/PConstants.h"

PNotification::PNotification(void) {}

void PNotification::prepare(void) {
    workspaceX = PConstants::PFunctionArea::pos.x + PConstants::PFunctionArea::size.x;
    workspaceY = PConstants::PTitleBar::pos.y + PConstants::PTitleBar::size.y;
    workspaceWidth = GetScreenWidth() - workspaceX;
    workspaceHeight = GetScreenHeight() - workspaceY;

    notification.rec.height = round(GetScreenHeight() / 10);
    notification.fontSize = notification.rec.height / 4;
    notification.rec.y = round(workspaceY + (workspaceHeight - notification.rec.height) / 2);
    notification.recColor = WHITE;
    notification.thick = 2;
    notification.outlineColor = BLACK;
    notification.textColor = RED;

    confirmButton.rec.height = round(notification.rec.height / 3);
    confirmButton.rec.y = round(notification.rec.y + notification.rec.height + confirmButton.rec.height);
    confirmButton.recColor = WHITE;
    confirmButton.thick = 2;
    confirmButton.outlineColor = BLACK;
    confirmButton.text = (char*)(const char*)"OK";
    confirmButton.fontSize = confirmButton.rec.height * 3/5;
    confirmButton.textColor = BLACK;
}

void PNotification::draw(void) {
    // Draw the notification box
    notification.text = (char *)notificationText.c_str();
    notification.rec.width = MeasureText(notification.text, notification.fontSize) + notification.fontSize * 2;
    notification.rec.x = round(workspaceX + (workspaceWidth - notification.rec.width) / 2);

    confirmButton.rec.width = round(notification.rec.width / 4);
    confirmButton.rec.x = round(notification.rec.x + (notification.rec.width - confirmButton.rec.width)/2);

    notification.draw();
    confirmButton.draw();
}

void PNotification::update(void) {
    // Get the mouse position
    Vector2 mouse = GetMousePosition();
    
    // Check if the mouse is over the confirm button
    if (CheckCollisionPointRec(mouse, confirmButton.rec)) {
        confirmButton.recColor = LIGHTGRAY;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            confirmButton.recColor = DARKGRAY;
            confirmButton.draw();
            notificationText.clear();
        }
    }
    else {
        confirmButton.recColor = WHITE;
    }
}

vector<int> PNotification::stringToVectorInt(string& s, int min, int max) {
    /*
        Convert a string into a vertor of integers
    */

    // Store result
    vector<int> res(0);
    // Check if characters are: space, plus, minus, or digit
    for(char c : s) {
        if(c != ' ' && c != '+' && c != '-' && !isdigit(c)) {
            notificationText = "Please input \' \', \'+\', \'-\' or digit only!";
            return res;
        }
    }
    // Trim all duplicate spaces
    string trimmed;
    for(int i = 0; i < (int)s.size(); i++) {
        if(s[i] != ' ') {
            trimmed += s[i];
        }
        else if(i > 0 && s[i-1] != ' ') {
            trimmed += s[i];
        }
    }
    while(trimmed.size() > 0 && trimmed.back() == ' ') {
        trimmed.pop_back();
    }
    // Convert string to vector of integers
    for(int i = 0; i < (int)s.size(); i++) {
        if(i > 0 && (trimmed[i] == '-' || trimmed[i] == '+') && (trimmed[i - 1] != ' ')) {
            notificationText = "Please input integers separated by spaces!";
            return vector<int>(0);
        }
        // Check if the character is a digit
        if(isdigit(trimmed[i])) {
            // Convert to integer and add to the vector
            int value = 0;
            while(i < (int)trimmed.size() && isdigit(trimmed[i])) {
                if(10LL * value + (trimmed[i] - '0') > 1LL * PConstants::PLimit::intData) {
                    notificationText = "The input integer is too large!";
                    return vector<int>(0);
                }
                value = value * 10 + (trimmed[i] - '0');
                i++;
            }
            res.push_back(value);
        }
        // Check if the character is a plus sign
        else if(trimmed[i] == '+') {
            i++;
            int value = 0;
            while(i < (int)trimmed.size() && isdigit(trimmed[i])) {
                if(10LL * value + (trimmed[i] - '0') > 1LL * PConstants::PLimit::intData) {
                    notificationText = "The input integer is too large!";
                    return vector<int>(0);
                }
                value = value * 10 + (trimmed[i] - '0');
                i++;
            }
            i--;
            res.push_back(value);
        }
        // Check if the character is a minus sign
        else if(trimmed[i] == '-') {
            i++;
            int value = 0;
            while(i < (int)trimmed.size() && isdigit(trimmed[i])) {
                if(10LL * value + (trimmed[i] - '0') > 1LL * PConstants::PLimit::intData) {
                    notificationText = "The input integer is too small!";
                    return vector<int>(0);
                }
                value = value * 10 + (trimmed[i] - '0');
                i++;
            }
            i--;
            res.push_back(-value);
        }
    }
    if(trimmed.empty()) {
        notificationText = "Please input at least one integer!";
        return vector<int>(0);
    }
    for(int val : res) {
        if(val < min || val > max) {
            notificationText = "Please input values between " + to_string(min) + " and " + to_string(max) + "!";
            return vector<int>(0);
        }
    }
    notificationText = "Valid";
    return res;
}

int PNotification::getOneNum(string& s, int min, int max) {
    vector<int> data = stringToVectorInt(s, min, max);
    if(notificationText == "Valid") {
        if(data.size() > 1)
            notificationText = "Please input a number only!";
        else
            return data[0];
    }
    return PConstants::PLimit::intData + 1;
}