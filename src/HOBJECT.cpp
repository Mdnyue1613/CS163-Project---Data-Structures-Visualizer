#include "raylib.h"
#include "../header/HOBJECT.h"
#include "../header/HGRAPH.h"
#include "../header/HGraphVisualize.h"

void TextBox::draw()
{
    DrawRectangle(rec.x, rec.y, rec.width, rec.height, recColor);
    DrawRectangleLinesEx(rec, thick, outlineColor);
    DrawText(text, rec.x + (rec.width - MeasureText(text, fontSize))/2, rec.y + (rec.height - fontSize)/2, fontSize, textColor);
}

void NavigateButton::draw()
{
    DrawTextureEx(img, Vector2{rec.x, rec.y}, rotation, scale, color);
}

void InputBox::draw()
{
    DrawRectangle(box.rec.x, box.rec.y, box.rec.width, box.rec.height, box.recColor);
    DrawRectangleLinesEx(box.rec, box.thick, box.outlineColor);

    if (userInput[0].empty())
    {
        DrawText(box.text, box.rec.x + (box.rec.width - MeasureText(box.text, box.fontSize))/2, box.rec.y + (box.rec.height - box.fontSize)/2, box.fontSize, box.textColor);
    }
    else
    {
        Vector2 textPos = Vector2{box.rec.x + lineSpacing, box.rec.y + lineSpacing};
        
        for (int i = firstLine; i <= firstLine + displayedLines - 1; i++)
            if (i < userInput.size() && !userInput[i].empty() && firstChar < userInput[i].size())
            {
                int length = findDisplayedLength(userInput[i], firstChar);
                DrawText(userInput[i].substr(firstChar, length).c_str(), textPos.x, textPos.y + (i - firstLine) * (fontSize + lineSpacing), fontSize, inputColor);
            }
    }
    
    if (isActive && fmod(GetTime(), 0.8f) < 0.4f)
    {
        Vector2 textPos = Vector2{box.rec.x + lineSpacing, box.rec.y + lineSpacing};

        Vector2 start;
        start.x = textPos.x + (cursorPos.second == 0 ? 0 : MeasureText(userInput[cursorPos.first].substr(firstChar, cursorPos.second - firstChar).c_str(), fontSize));
        start.y = textPos.y + (cursorPos.first - firstLine) * (fontSize + lineSpacing);
        Vector2 end = Vector2{start.x, start.y + fontSize};
        DrawLineEx(start, end, box.thick, RED);
    }
}

void InputBox::activate()
{
    Vector2 mousePos = GetMousePosition();

    if (isActive == 0 && CheckCollisionPointRec(mousePos, box.rec))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            isActive = 1;
    }
    else if (isActive == 1 && !CheckCollisionPointRec(mousePos, box.rec))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            isActive = 0;
    }

    if (isActive) 
    {
        int key = GetCharPressed();
        while (key > 0) 
        {
            if (isdigit(key) || (char)key == ' ') 
            {
                userInput[cursorPos.first].insert(cursorPos.second, 1, (char)key);
                cursorPos.second++;

                firstChar = findFirstChar(userInput[cursorPos.first], cursorPos.second - 1);
            }
            key = GetCharPressed();
        }

        ENTER();
        BACKSPACE();
        NAVIGATION();
    }
}

int InputBox::findDisplayedLength(string &s, int start)
{
    int ans;
    int l = start;
    int r = s.size() - 1;
    while (l <= r)
    {
        int mid = (l+r) >> 1;
        int length = MeasureText(s.substr(start, mid - start + 1).c_str(), fontSize);
        if (length <= maxLenPerLine)
        {
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    return ans - start + 1;
}

int InputBox::findFirstChar(string &s, int end)
{
    int ans = 0;
    int l = 0;
    int r = end;
    while (l <= r)
    {
        int mid = (l+r) >> 1;
        int length = MeasureText(s.substr(mid, end - mid + 1).c_str(), fontSize);
        if (length <= maxLenPerLine)
        {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return ans;
}

void InputBox::ENTER()
{
    if (IsKeyPressed(KEY_ENTER)) 
    {    
        userInput[cursorPos.first].insert(cursorPos.second, "\n");
        userInput.push_back("");
        cursorPos.first++;
        cursorPos.second = 0;
        
        firstChar = 0;
        if (cursorPos.first - firstLine + 1 > displayedLines)
            firstLine++;
    }   
}

void InputBox::BACKSPACE()
{
    if (IsKeyPressed(KEY_BACKSPACE) || (IsKeyDown(KEY_BACKSPACE) && GetTime() - startPress >= periodHold))
    {
        if (cursorPos.second == 0 && cursorPos.first > 0)
        {
            userInput.pop_back();
            cursorPos.first--;
            cursorPos.second = userInput[cursorPos.first].size();
            
            if (firstLine > 0)
                firstLine--;
        }
        if (cursorPos.second > 0)
        {
            userInput[cursorPos.first].erase(cursorPos.second - 1, 1);
            cursorPos.second--;
        }

        firstChar = findFirstChar(userInput[cursorPos.first], cursorPos.second - 1);
        if (cursorPos.first < firstLine)
            firstLine--;
        
        startPress = GetTime();
    }   
}

void InputBox::NAVIGATION()
{
    if (IsKeyPressed(KEY_LEFT) || (IsKeyDown(KEY_LEFT) && GetTime() - startPress >= periodHold))
    {
        if (cursorPos.second > 0)
        {
            cursorPos.second--;
        }
        else if (cursorPos.first > 0)
        {
            cursorPos.first--;
            cursorPos.second = userInput[cursorPos.first].size();
        }

        firstChar = findFirstChar(userInput[cursorPos.first], cursorPos.second - 1);
        if (cursorPos.first < firstLine)
            firstLine--;
        
        startPress = GetTime();
    }

    if (IsKeyPressed(KEY_RIGHT) || (IsKeyDown(KEY_RIGHT) && GetTime() - startPress >= periodHold))
    {
        if (cursorPos.second < userInput[cursorPos.first].size())
        {
            cursorPos.second++;
        }
        else if (cursorPos.first < userInput.size() - 1)
        {
            cursorPos.first++;
            cursorPos.second = 0;
        }

        firstChar = findFirstChar(userInput[cursorPos.first], cursorPos.second - 1);
        if (cursorPos.first - firstLine + 1 > displayedLines)
            firstLine++;
        
        startPress = GetTime();
    }

    if (IsKeyPressed(KEY_UP) || (IsKeyDown(KEY_UP) && GetTime() - startPress >= periodHold))
    {
        if (cursorPos.first > 0)
        {
            cursorPos.first--;
            cursorPos.second = min(cursorPos.second, (int)userInput[cursorPos.first].size());
        }
        else 
        {
            cursorPos.second = 0;
        }

        firstChar = findFirstChar(userInput[cursorPos.first], cursorPos.second - 1);
        if (cursorPos.first < firstLine)
            firstLine--;
        
        startPress = GetTime();
    }

    if (IsKeyPressed(KEY_DOWN) || (IsKeyDown(KEY_DOWN) && GetTime() - startPress >= periodHold))
    {
        if (cursorPos.first < userInput.size() - 1)
        {
            cursorPos.first++;
            cursorPos.second = min(cursorPos.second, (int)userInput[cursorPos.first].size());
        }
        else 
        {
            cursorPos.second = userInput[cursorPos.first].size();
        }

        firstChar = findFirstChar(userInput[cursorPos.first], cursorPos.second - 1);
        if (cursorPos.first - firstLine + 1 > displayedLines)
            firstLine++;
        
        startPress = GetTime();
    }
}

void InputBox::clear()
{
    userInput.clear();
    userInput.push_back("");
    firstLine = 0;
    firstChar = 0;
    cursorPos = {0, 0};
}

void PauseButton::draw(Color color)
{
    Vector2 point1 = {rec.x + (rec.width / 4), rec.y};
    Vector2 point2 = {rec.x + (rec.width / 4), rec.y + rec.height};
    Vector2 point3 = {rec.x + (rec.width * 3/4), rec.y};
    Vector2 point4 = {rec.x + (rec.width * 3/4), rec.y + rec.height};

    DrawLineEx(point1, point2, 4, color);
    DrawLineEx(point3, point4, 4, color);
}

bool PauseButton::activate()
{
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, rec))
    {
        draw(LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            draw(DARKGRAY);
            return 1;
        }
    }
    return 0;
}

void NextButton::draw(Color color)
{
    float height = rec.width * sqrt(3) / 2;
    Vector2 point1 = {rec.x + (rec.width - height)/2, rec.y};
    Vector2 point2 = {rec.x + (rec.width - height)/2, rec.y + rec.height};
    Vector2 point3 = {rec.x + (rec.width - height)/2 + height, rec.y + rec.height/2};

    DrawTriangle(point1, point2, point3, color);
}

bool NextButton::activate()
{
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, rec))
    {
        draw(LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            draw(DARKGRAY);
            return 1;
        }
    }
    return 0;
}

void BackButton::draw(Color color)
{
    float height = rec.width * sqrt(3) / 2;
    Vector2 point1 = {rec.x + rec.width - (rec.width - height)/2, rec.y + rec.height};
    Vector2 point2 = {rec.x + rec.width - (rec.width - height)/2, rec.y};
    Vector2 point3 = {rec.x + (rec.width - height)/2, rec.y + rec.height/2};

    DrawTriangle(point1, point2, point3, color);
}

bool BackButton::activate()
{
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, rec))
    {
        draw(LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            draw(DARKGRAY);
            return 1;
        }
    }
    return 0;
}

void SkipToEndButton::draw(Color color)
{
    float height = rec.width/2 * sqrt(3) / 2;
    Vector2 point1 = {rec.x + (rec.width - height*2)/2, rec.y};
    Vector2 point2 = {rec.x + (rec.width - height*2)/2, rec.y + rec.height};
    Vector2 point3 = {rec.x + (rec.width - height*2)/2 + height, rec.y + rec.height/2};

    DrawTriangle(point1, point2, point3, color);

    point1 = Vector2Add(point1, {height, 0});
    point2 = Vector2Add(point2, {height, 0});
    point3 = Vector2Add(point3, {height, 0});

    DrawTriangle(point1, point2, point3, color);
}

bool SkipToEndButton::activate()
{
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, rec))
    {
        draw(LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            draw(DARKGRAY);
            return 1;
        }
    }
    return 0;
}

void BackToStartButton::draw(Color color)
{
    float height = rec.width/2 * sqrt(3) / 2;
    Vector2 point1 = {rec.x + (rec.width - height*2)/2 + height, rec.y + rec.height};
    Vector2 point2 = {rec.x + (rec.width - height*2)/2 + height, rec.y};
    Vector2 point3 = {rec.x + (rec.width - height*2)/2, rec.y + rec.height/2};

    DrawTriangle(point1, point2, point3, color);

    point1 = Vector2Add(point1, {height, 0});
    point2 = Vector2Add(point2, {height, 0});
    point3 = Vector2Add(point3, {height, 0});

    DrawTriangle(point1, point2, point3, color);
}

bool BackToStartButton::activate()
{
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, rec))
    {
        draw(LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            draw(DARKGRAY);
            return 1;
        }
    }
    return 0;
}

void Slider::draw(Color barColor, Color thumbColor)
{
    DrawRectangleRounded(bar, 1, 10, barColor);
    DrawRectangleRounded(thumb, 1, 10, thumbColor);
}

Vector2 Slider::activate()
{
    Vector2 mouse = GetMousePosition();

    if (CheckCollisionPointRec(mouse, thumb))
    {
        draw(SEASHELL, LIGHTGRAY);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            draw(SEASHELL, DARKGRAY);
            isClick = 1;
            lastMousePos = mouse;
        }
        return {0, 0};
    }
    else if (isClick && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        draw(SEASHELL, DARKGRAY);
        Vector2 displacement = Vector2Subtract(mouse, lastMousePos);
        int units = displacement.x / (unit / 2);
        if (units != 0) 
            lastMousePos = mouse;
        
        return displacement;
    }
    else 
    {
        isClick = 0;
        return {0, 0};
    }
}

void ControlPanel::draw()
{
    pauseButton.draw(BLACK);
    nextButton.draw(BLACK);
    backButton.draw(BLACK);
    skipToEndButton.draw(BLACK);
    backToStartButton.draw(BLACK);
    statusSlider.draw(SEASHELL, BLACK);
    speedSlider.draw(SEASHELL, BLACK);
}

void ControlPanel::drawSpeed(Rectangle bar, float margin, float fontSize)
{
    DrawText((const char*)"Speed:", bar.x - margin - MeasureText((const char*)"Speed:", fontSize), bar.y - (fontSize - bar.height)/2, fontSize, BLACK);
    
    Vector2 pos = {
        bar.x + (bar.width - MeasureText(TextFormat("%.2fx", speed), fontSize))/2,
        bar.y - fontSize
    };
    DrawText(TextFormat("%.2fx", speed), pos.x, pos.y, fontSize, BLACK);
}

void ControlPanel::activateSpeedSilder(float &duration, int current, vector <State> &states)
{
    Vector2 displacement = speedSlider.activate();
    int units = displacement.x / (speedSlider.unit / 2);
    speedSlider.thumb.x += units * speedSlider.unit;
    speedSlider.thumb.x = max(speedSlider.thumb.x, speedSlider.bar.x);
    speedSlider.thumb.x = min(speedSlider.thumb.x, speedSlider.bar.x + speedSlider.bar.width - speedSlider.thumb.width);

    float newSpeed = speedSlider.minValue * ((speedSlider.thumb.x - speedSlider.bar.x) / speedSlider.unit + 1);
    float newDuration = duration * speed / newSpeed;

    if (states.size())
    {
        float percent = states[current].animationProcess / duration;
        states[current].animationProcess = percent * newDuration;
    }
    
    speed = newSpeed;
    duration = newDuration;
}

void ControlPanel::activateStatusSlider(int &current, vector <State> &states, float duration)
{
    if (states[current].isDone) states[current].animationProcess = duration;

    statusSlider.thumb.x = statusSlider.bar.x + statusSlider.unit * (current + states[current].animationProcess / duration);

    Vector2 mouse = GetMousePosition();
    Vector2 displacement = {0, 0};

    if (CheckCollisionPointRec(mouse, statusSlider.thumb))
    {
        statusSlider.draw(SEASHELL, LIGHTGRAY);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            statusSlider.draw(SEASHELL, DARKGRAY);
            statusSlider.isClick = 1;
            statusSlider.lastMousePos = mouse;
        }
        else statusSlider.isClick = 0;
    }
    else if (statusSlider.isClick && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        statusSlider.draw(SEASHELL, DARKGRAY);
        displacement = Vector2Subtract(mouse, statusSlider.lastMousePos);
        if (abs(displacement.x) >= statusSlider.thumb.width / 2) 
            statusSlider.lastMousePos = mouse;
    }
    else statusSlider.isClick = 0;
    
    if (abs(displacement.x) >= statusSlider.thumb.width / 2)
    {
        statusSlider.thumb.x += (int)(displacement.x*2 / statusSlider.thumb.width) * statusSlider.unit;
        statusSlider.thumb.x = max(statusSlider.thumb.x, statusSlider.bar.x);
        statusSlider.thumb.x = min(statusSlider.thumb.x, statusSlider.bar.x + statusSlider.bar.width - statusSlider.thumb.width);

        float tmp = (statusSlider.thumb.x - statusSlider.bar.x) / statusSlider.unit;
        int newCurrent = (int)tmp;

        if (newCurrent < current)
        {
            for (int i = current; i > newCurrent; i--)
            {
                states[i].startTime = 0;
                states[i].animationProcess = 0;
            }
        }
        else 
        {
            for (int i = current; i < newCurrent; i++)
            {
                states[i].startTime = GetTime() - duration;
                states[i].animationProcess = duration;;
            }
        }

        if (newCurrent == states.size())
        {
            current = newCurrent - 1;
            states[current].animationProcess = duration;
            states[current].startTime = GetTime() - states[current].animationProcess;
        }
        else
        {   
            current = newCurrent;
            states[current].animationProcess = duration * (tmp - newCurrent) / statusSlider.unit;
            states[current].startTime = GetTime() - states[current].animationProcess;
        }
    }
}

void ControlPanel::activatePauseButton(bool &isStop)
{
    bool isClick = pauseButton.activate();
    isStop ^= isClick;
}

void ControlPanel::activateNextButton(int &current, vector <State> &states, float duration)
{
    bool isClick = nextButton.activate();
    if (isClick)
    {
        if (current == states.size() - 1) return;
        current++;
        states[current].startTime = 0;
        states[current - 1].startTime = GetTime() - duration;
        states[current - 1].animationProcess = duration;
    }
}

void ControlPanel::activateBackButton(int &current, vector <State> &states)
{
    bool isClick = backButton.activate();
    if (isClick)
    {
        states[current].startTime = 0;
        states[current].animationProcess = 0;

        if (current == 0) return;
        current--;
        states[current].startTime = 0;
        states[current].animationProcess = 0;
    }
}

void ControlPanel::activateSkipToEndButton(int &current, vector <State> &states, float duration)
{
    bool isClick = skipToEndButton.activate();
    if (isClick)
    {
        for (int i = current; i < states.size(); i++)
            states[i].startTime = GetTime() - duration;

        current = states.size() - 1;
    }
}

void ControlPanel::activateBackToStartButton(int &current, vector <State> &states)
{
    bool isClick = backToStartButton.activate();
    if (isClick)
    {
        for (int i = 0; i <= current; i++)
        {
            states[i].startTime = 0;
            states[i].animationProcess = 0;
        }

        current = 0;
    }
}

void ScrollingTable::draw()
{
    DrawRectangle(table.x, table.y, table.width, rowHeight, MAYABLUE);
        
    float tmp = 0;
    for (int i = 0; i < numColumn; i++)
    {
        DrawText(label[i].c_str(), table.x + tmp + (colWidth[i] - MeasureText(label[i].c_str(), fontSize))/2, table.y + (rowHeight - fontSize)/2, fontSize, BLACK);
        tmp += colWidth[i];
    }
    
    BeginScissorMode(scrollBox.x, scrollBox.y, scrollBox.width, scrollBox.height);
    tmp = 0;
    for (int i = 0; i < numColumn; i++)
    {   
        for (int j = 0; j < data[i].size(); j++)
        {
            if (j % 2)
            {
                DrawRectangle(scrollPoint.x + tmp, scrollPoint.y + j * rowHeight, colWidth[i], rowHeight, WHITE);
            }
            else DrawRectangle(scrollPoint.x + tmp, scrollPoint.y + j * rowHeight, colWidth[i], rowHeight, (Color){117, 189, 241, 240});

            string text = data[i][j];
            DrawText(text.c_str(), scrollPoint.x + tmp + (colWidth[i] - MeasureText(text.c_str(), fontSize))/2, scrollPoint.y + rowHeight*j + (rowHeight - fontSize)/2, fontSize, BLACK);
        }

        tmp += colWidth[i];
    }
    EndScissorMode();

    DrawRectangleLinesEx(table, 1, BLACK);
    Vector2 point1 = {table.x, table.y + rowHeight};
    Vector2 point2 = {table.x + table.width, table.y + rowHeight};
    DrawLineEx(point1, point2, 1, BLACK);

    tmp = 0;
    for (int i = 1; i < label.size(); i++)
    {
        tmp += colWidth[i-1];
        Vector2 point1 = {table.x + tmp, table.y};
        Vector2 point2 = {table.x + tmp, table.y + table.height};
        DrawLineEx(point1, point2, 1, BLACK);
    }
}

void ScrollingTable::scroll()
{

    if (CheckCollisionPointRec(GetMousePosition(), scrollBox))
    {
        float wheel = GetMouseWheelMove();
        scrollPoint.y += wheel * rowHeight / 2;
    }

    scrollPoint.y = max(scrollPoint.y, scrollBox.y - (data[0].size() - scrollBox.height / rowHeight) * rowHeight);
    scrollPoint.y = min(scrollPoint.y, scrollBox.y);
}

void ScrollingTable::focus(int vertex)
{
    scrollPoint.y = scrollBox.y - rowHeight * vertex;
    scrollPoint.y = max(scrollPoint.y, scrollBox.y - (data[0].size() - scrollBox.height / rowHeight) * rowHeight);
}

void ScrollingTable::drawImportantLine(int vertex, Color color)
{
    float posY = scrollPoint.y + vertex * rowHeight;
    BeginScissorMode(scrollBox.x, scrollBox.y, scrollBox.width, scrollBox.height);
    DrawRectangleLinesEx({scrollBox.x, posY, colWidth[0] + colWidth[1], rowHeight}, 3, color);
    EndScissorMode();
}

void ScrollingTable::clear()
{
    numColumn = 0;
    label.clear();
    data.clear();
    colWidth.clear();
}