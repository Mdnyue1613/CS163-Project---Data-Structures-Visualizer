#include "../header/HOBJECT.h"

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
        float lineSpacing = (box.rec.height - fontSize * displayedLines) / (displayedLines + 1);
        float indentation = MeasureText(to_string(0).c_str(), fontSize);
        Vector2 textPos = Vector2{box.rec.x + indentation, box.rec.y + lineSpacing};
        
        for (int i = firstLine; i <= firstLine + displayedLines - 1; i++)
            if (i < userInput.size() && !userInput[i].empty() && firstChar < userInput[i].size())
            {
                int length = findDisplayedLength(userInput[i], firstChar);
                DrawText(userInput[i].substr(firstChar, length).c_str(), textPos.x, textPos.y + (i - firstLine) * (fontSize + lineSpacing), fontSize, inputColor);
            }
    }
    
    if (isActive && fmod(GetTime(), 0.8f) < 0.4f)
    {
        float lineSpacing = (box.rec.height - fontSize * displayedLines) / (displayedLines + 1);
        float indentation = MeasureText(to_string(0).c_str(), fontSize);
        Vector2 textPos = Vector2{box.rec.x + indentation, box.rec.y + lineSpacing};

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
        }
        if (cursorPos.second > 0)
        {
            userInput[cursorPos.first].erase(cursorPos.second - 1, 1);
            cursorPos.second--;
        }

        firstChar = findFirstChar(userInput[cursorPos.first], cursorPos.second - 1);
        if (firstLine > 0)
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
