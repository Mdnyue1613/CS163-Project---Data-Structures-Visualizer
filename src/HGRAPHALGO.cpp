#include "../header/HGRAPHALGO.h"
#include "../header/HGRAPH.h"

void DijkstraVisualize::chooseMode()
{
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, autoButton.rec) && mode == 1)
    {
        autoButton.recColor = LIGHTGRAY;
        autoButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            mode ^= 1;
            autoButton.recColor = GRAY;
            stepByStepButton.recColor = WHITE;
        }
        else autoButton.recColor = WHITE;
    }
    else if (CheckCollisionPointRec(mouse, stepByStepButton.rec) && mode == 0)
    {
        stepByStepButton.recColor = LIGHTGRAY;
        stepByStepButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            mode ^= 1;
            stepByStepButton.recColor = GRAY;
            autoButton.recColor = WHITE;
        }
        else stepByStepButton.recColor = WHITE;
    }
}

void DijkstraVisualize::chooseDescription()
{
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, guideButton.rec) && descriptionMode == 1)
    {
        guideButton.recColor = LIGHTGRAY;
        guideButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            descriptionMode ^= 1;
            guideButton.recColor = GRAY;
            pseudoButton.recColor = WHITE;
        }
        else guideButton.recColor = WHITE;
    }
    else if (CheckCollisionPointRec(mouse, pseudoButton.rec) && descriptionMode == 0)
    {
        pseudoButton.recColor = LIGHTGRAY;
        pseudoButton.draw();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            descriptionMode ^= 1;
            pseudoButton.recColor = GRAY;
            guideButton.recColor = WHITE;
        }
        else pseudoButton.recColor = WHITE;
    }
}

void DijkstraVisualize::drawDescription()
{
    if (descriptionMode == 0)
    {
        for (int i = 0; i < guide.size(); i++)
        {
            float posY = descriptionPos.y + i * (descriptionFontSize + descriptionLineSpacing);
            DrawText(guide[i].c_str(), descriptionPos.x, posY, descriptionFontSize, BLACK);
        }
    }
    else 
    {
        for (int i = 0; i < pseudo.size(); i++)
        {
            float posY = descriptionPos.y + i * (descriptionFontSize + descriptionLineSpacing);
            DrawText(pseudo[i].c_str(), descriptionPos.x, posY, descriptionFontSize, BLACK);
        }
    }
}

bool DijkstraVisualize::loadData(vector <string> &userInput, Graph &G)
{
    int cursor = 0;
    bool success = GetNumFromStr(userInput[0], cursor, startVertex);
    if (!success || startVertex < 0 || startVertex > G.numVertex || G.vertex[startVertex].real == 0) 
    {
        startVertex = -1;
        return 0;
    }
    success = GetNumFromStr(userInput[0], cursor, endVertex);
    if (!success)
    {
        endVertex = -1;
    }
    else if (endVertex < 0 || endVertex > G.numVertex || G.vertex[endVertex].real == 0)
    {
        endVertex = -1;
        return 0;
    }

    return 1;
}

void DijkstraVisualize::run(Graph &G)
{
    vector <int> distance(G.numVertex + 1, -1);
    vector <bool> isFound(G.numVertex + 1, 0);
    vector <int> trace(G.numVertex + 1, -1);
    vector <int> prevTrace(G.numVertex + 1, -1);
    priority_queue <ii, vector <ii>, greater <ii> > PQ;

    distance[startVertex] = 0;
    PQ.push(ii(0, startVertex));
    states.push_back(State(distance, isFound, trace, prevTrace, -1, -1, 0, 0, 0, 0));

    while ((endVertex != -1 && !isFound[endVertex] && PQ.size()) || (endVertex == -1 && PQ.size()))
    {
        ii u = PQ.top();
        PQ.pop();
        if (u.first > distance[u.second]) continue;
        isFound[u.second] = 1;

        if (u.second == endVertex)
        {
            states.push_back(State(distance, isFound, trace, prevTrace, u.second, -1, 1, 0, 0, 0));
            states.push_back(State(distance, isFound, trace, prevTrace, u.second, -1, 5, 0, 0, 0));
            break;
        }

        states.push_back(State(distance, isFound, trace, prevTrace, u.second, -1, 1, 0, 0, 0));
        
        for (Edge &edge : G.g[u.second])
            if (G.type == 0 || edge.real)
            {
                if (isFound[edge.to]) continue;

                states.push_back(State(distance, isFound, trace, prevTrace, u.second, edge.to, 2, 0, 0, 0));

                if (distance[edge.to] == -1 || distance[edge.to] > u.first + edge.weight)
                {
                    distance[edge.to] = u.first + edge.weight;
                    prevTrace[edge.to] = trace[edge.to];
                    trace[edge.to] = u.second;
                    PQ.push(ii(distance[edge.to], edge.to));
                    states.push_back(State(distance, isFound, trace, prevTrace, u.second, edge.to, 3, 0, 0, 0));
                }
                else states.push_back(State(distance, isFound, trace, prevTrace, u.second, edge.to, 4, 0, 0, 0));
            }
        
        states.push_back(State(distance, isFound, trace, prevTrace, u.second, -1, 5, 0, 0, 0));
    }

    if (endVertex != -1)
    {
        for (int i = 0; i <= G.numVertex; i++)
            isFound[i] = 0;

        int k = endVertex;
        while (k != -1)
        {
            isFound[k] = 1;
            k = trace[k];
        }
    }
    states.push_back(State(distance, isFound, trace, prevTrace, -1, -1, 6, 0, 0, 0));
}

void DijkstraVisualize::initTrackingTable(Graph &G)
{
    int *numColumn = &trackingTable.numColumn;
    Rectangle *table = &trackingTable.table;
    Rectangle *scrollBox = &trackingTable.scrollBox;
    Vector2 *scrollPoint = &trackingTable.scrollPoint;
    vector <string> *label = &trackingTable.label;
    vector <vector<string> > *data = &trackingTable.data;
    float *fontSize = &trackingTable.fontSize;
    vector <float> *colWidth = &trackingTable.colWidth;
    float *rowHeight = &trackingTable.rowHeight;

    if (current == 0)
    {
        *numColumn = 2;
        *rowHeight = round(G.workspace.height / 25);
        *fontSize = *rowHeight * 2/5;
        *label = vector <string>{"Vertex", "Distance"};
        (*data).clear();
        (*data).resize(*numColumn, vector <string>(G.numVertex + 1, ""));
        (*colWidth).clear();
        (*colWidth).resize((*label).size(), 0);

        (*colWidth)[0] = MeasureText((*label)[0].c_str(), *fontSize) + *rowHeight - *fontSize;
        for (int i = 0; i <= G.numVertex; i++)
        {
            (*data)[0][i] = to_string(i);
            (*colWidth)[0] = max((*colWidth)[0], MeasureText((*data)[0][i].c_str(), *fontSize) + *rowHeight - *fontSize);
        }

        (*colWidth)[1] = MeasureText((*label)[1].c_str(), *fontSize) + *rowHeight - *fontSize;
        for (State &state : states)
            for (int i = 0; i <= G.numVertex; i++)
                (*colWidth)[1] = max((*colWidth)[1], MeasureText(to_string(state.distance[i]).c_str(), *fontSize) + *rowHeight - *fontSize);
        
        table->width = round((*colWidth)[0] + (*colWidth)[1]);
        table->height = round(min(G.workspace.height, *rowHeight * (G.numVertex + 1 + 1)));
        table->x = round(G.workspace.x + G.workspace.width - table->width);
        table->y = round(G.workspace.y + (G.workspace.height - table->height)/2);

        scrollBox->width = table->width;
        scrollBox->height = round(table->height - *rowHeight);
        scrollBox->x = table->x;
        scrollBox->y = round(table->y + *rowHeight);

        *scrollPoint = {scrollBox->x, scrollBox->y};
    }
    
    for (int i = 0; i <= G.numVertex; i++)
        if (states[current].distance[i] != -1)
            (*data)[1][i] = to_string(states[current].distance[i]);
        else (*data)[1][i] = "-";
}

void DijkstraVisualize::updateTrackingTable()
{
    for (int i = 0; i < states[current].distance.size(); i++)
        if (states[current].distance[i] != -1)
            trackingTable.data[1][i] = to_string(states[current].distance[i]);
        else trackingTable.data[1][i] = "-";
}

void DijkstraVisualize::view(Graph &G, State &state)
{
    if (state.animationProcess == 0)
        updateTrackingTable();

    trackingTable.draw();
    trackingTable.scroll();

    if (state.step == 0) Step0(G, state);
    else if (state.step == 1) Step1(G, state);
    else if (state.step == 2) Step2(G, state);
    else if (state.step == 3) Step3(G, state);
    else if (state.step == 4) Step4(G, state);
    else if (state.step == 5) Step5(G, state);
    else Step6(G, state);

    state.isDone = (state.animationProcess == duration);
}

void DijkstraVisualize::Step0(Graph &G, State &state)
{
    float delta = min((float)GetTime() - state.startTime, duration);
    if (isStatusSilderWork == 0) state.animationProcess = delta;

    Color orangeFadeUp = PEACHORANGE;
    if (delta <= duration / 3) orangeFadeUp.a *= delta / (duration / 3);

    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1)
           G.DrawVertex(i, orangeFadeUp); 

    if (descriptionMode == 1)
    {
        for (int i = 0; i <= 1; i++)
        {
            float posX = descriptionPos.x;
            float posY = descriptionPos.y + i * (descriptionFontSize + descriptionLineSpacing);
            
            DrawRectangle(posX, posY, MeasureText(pseudo[i].c_str(), descriptionFontSize), descriptionFontSize, CORALRED);
            DrawText(pseudo[i].c_str(), posX, posY, descriptionFontSize, BLACK);
        }
    }
}

void DijkstraVisualize::Step1(Graph &G, State &state)
{
    int u = state.u;

    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1 && state.trace[i] != -1)
        {
            Color color = SPRINGGREEN;
            if (i == u || !state.isFound[i]) color = PEACHORANGE;

            Edge edge = G.FindEdge(state.trace[i], i);
            if (edge.real)
            {
                G.DrawEdge(G.vertex[state.trace[i]].position, G.vertex[i].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
            else
            {
                edge = G.FindEdge(i, state.trace[i]);
                G.DrawEdge(G.vertex[i].position, G.vertex[state.trace[i]].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
        }

    float delta = min((float)GetTime() - state.startTime, duration);
    if (isStatusSilderWork == 0) state.animationProcess = delta;
    
    Color greenFadeUp = SPRINGGREEN;
    Color redFadeUp = CORALRED;
    if (delta <= duration / 3)
    {
        greenFadeUp.a *= delta / (duration / 3);
        redFadeUp.a *= delta / (duration / 3);
    }
    
    if (state.trace[u] != -1)
    {
        Edge edge = G.FindEdge(state.trace[u], u);
            if (edge.real)
            {
                G.DrawEdge(G.vertex[state.trace[u]].position, G.vertex[u].position, edge.weight, G.connections[u][state.trace[u]], greenFadeUp);
            }
            else
            {
                edge = G.FindEdge(u, state.trace[u]);
                G.DrawEdge(G.vertex[u].position, G.vertex[state.trace[u]].position, edge.weight, G.connections[u][state.trace[u]], greenFadeUp);
            }
    }

    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1)
        {
            Color color = SPRINGGREEN;
            if (i == u || !state.isFound[i]) color = PEACHORANGE;

            G.DrawVertex(i, color);
        }

    G.DrawVertex(u, redFadeUp);

    trackingTable.focus(u);
    trackingTable.drawImportantLine(u, redFadeUp);

    if (descriptionMode == 1)
    {
        for (int i = 3; i <= 4; i++)
        {
            float posX = descriptionPos.x;
            float posY = descriptionPos.y + i * (descriptionFontSize + descriptionLineSpacing);
            
            DrawRectangle(posX, posY, MeasureText(pseudo[i].c_str(), descriptionFontSize), descriptionFontSize, CORALRED);
            DrawText(pseudo[i].c_str(), posX, posY, descriptionFontSize, BLACK);
        }
    }
}

void DijkstraVisualize::Step2(Graph &G, State &state)
{
    int u = state.u;
    int v = state.v;

    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1 && state.trace[i] != -1)
        {
            Color color = SPRINGGREEN;
            if (!state.isFound[i]) color = PEACHORANGE;

            Edge edge = G.FindEdge(state.trace[i], i);
            if (edge.real)
            {
                G.DrawEdge(G.vertex[state.trace[i]].position, G.vertex[i].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
            else
            {
                edge = G.FindEdge(i, state.trace[i]);
                G.DrawEdge(G.vertex[i].position, G.vertex[state.trace[i]].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
        }

    float delta = min((float)GetTime() - state.startTime, duration);
    if (isStatusSilderWork == 0) state.animationProcess = delta;

    Color redFadeUp = CORALRED;
    if (delta <= duration / 3) redFadeUp.a *= delta / (duration / 3);
    
    Edge edge = G.FindEdge(u, v);
    if (edge.real)
    {
        G.DrawEdge(G.vertex[u].position, G.vertex[v].position, edge.weight, G.connections[u][v], redFadeUp);
    }
    else
    {
        edge = G.FindEdge(v, u);
        G.DrawEdge(G.vertex[v].position, G.vertex[u].position, edge.weight, G.connections[u][v], redFadeUp);
    }
    
    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1)
        {
            Color color = SPRINGGREEN;
            if (i == u) color = CORALRED;
            else if (!state.isFound[i]) color = PEACHORANGE;

            G.DrawVertex(i, color);
        }

    G.DrawVertex(v, redFadeUp);

    trackingTable.focus(v);
    trackingTable.drawImportantLine(u, CORALRED);
    trackingTable.drawImportantLine(v, redFadeUp);

    if (descriptionMode == 1)
    {
        float posX = descriptionPos.x;
        float posY = descriptionPos.y + 6 * (descriptionFontSize + descriptionLineSpacing);
            
        DrawRectangle(posX, posY, MeasureText(pseudo[6].c_str(), descriptionFontSize), descriptionFontSize, CORALRED);
        DrawText(pseudo[6].c_str(), posX, posY, descriptionFontSize, BLACK);
    }
}

void DijkstraVisualize::Step3(Graph &G, State &state)
{
    int u = state.u;
    int v = state.v;

    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1 && state.trace[i] != -1)
        {
            Color color = SPRINGGREEN;
            if (i == v) color = CORALRED;
            else if (!state.isFound[i]) color = PEACHORANGE;

            Edge edge = G.FindEdge(state.trace[i], i);
            if (edge.real)
            {
                G.DrawEdge(G.vertex[state.trace[i]].position, G.vertex[i].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
            else
            {
                edge = G.FindEdge(i, state.trace[i]);
                G.DrawEdge(G.vertex[i].position, G.vertex[state.trace[i]].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
        }

    float delta = min((float)GetTime() - state.startTime, duration);
    if (isStatusSilderWork == 0) state.animationProcess = delta;

    Color orangeFadeUp = PEACHORANGE;
    Color orangeFadeDown = PEACHORANGE;
    if (delta <= duration / 3) orangeFadeUp.a *= delta / (duration / 3);
    orangeFadeDown.a *= (duration - delta) / duration;
    
    Edge edge = G.FindEdge(u, v);
    if (edge.real)
    {
        G.DrawEdge(G.vertex[u].position, G.vertex[v].position, edge.weight, G.connections[u][v], orangeFadeUp);
    }
    else
    {
        edge = G.FindEdge(v, u);
        G.DrawEdge(G.vertex[v].position, G.vertex[u].position, edge.weight, G.connections[u][v], orangeFadeUp);
    }
    
    int k = state.prevTrace[v];
    if (k != -1)
    {
        edge = G.FindEdge(k, v);
        if (edge.real)
        {
            G.DrawEdge(G.vertex[k].position, G.vertex[v].position, edge.weight, G.connections[k][v], orangeFadeDown);
        }
        else
        {
            edge = G.FindEdge(v, k);
            G.DrawEdge(G.vertex[v].position, G.vertex[k].position, edge.weight, G.connections[k][v], orangeFadeDown);
        }
        
        G.DrawVertex(k, PEACHORANGE);
    }

    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1)
        {
            Color color = SPRINGGREEN;
            if (i == u || i == v) color = CORALRED;
            else if (!state.isFound[i]) color = PEACHORANGE;

            G.DrawVertex(i, color);
        }

    G.DrawVertex(v, orangeFadeUp);

    trackingTable.focus(v);
    trackingTable.drawImportantLine(u, CORALRED);
    trackingTable.drawImportantLine(v, CORALRED);
    trackingTable.drawImportantLine(v, orangeFadeUp);

    if (descriptionMode == 1)
    {
        for (int i = 7; i <= 8; i++)
        {
            float posX = descriptionPos.x;
            float posY = descriptionPos.y + i * (descriptionFontSize + descriptionLineSpacing);
            
            DrawRectangle(posX, posY, MeasureText(pseudo[i].c_str(), descriptionFontSize), descriptionFontSize, CORALRED);
            DrawText(pseudo[i].c_str(), posX, posY, descriptionFontSize, BLACK);
        }
    }
}

void DijkstraVisualize::Step4(Graph &G, State &state)
{
    int u = state.u;
    int v = state.v;

    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1 && state.trace[i] != -1)
        {
            Color color = SPRINGGREEN;
            if (!state.isFound[i]) color = PEACHORANGE;

            Edge edge = G.FindEdge(state.trace[i], i);
            if (edge.real)
            {
                G.DrawEdge(G.vertex[state.trace[i]].position, G.vertex[i].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
            else
            {
                edge = G.FindEdge(i, state.trace[i]);
                G.DrawEdge(G.vertex[i].position, G.vertex[state.trace[i]].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
        }

    float delta = min((float)GetTime() - state.startTime, duration);
    if (isStatusSilderWork == 0) state.animationProcess = delta;

    Color redFadeDown = CORALRED;
    redFadeDown.a *= (duration - delta) / duration;
    
    Edge edge = G.FindEdge(u, v);
    if (edge.real)
    {
        G.DrawEdge(G.vertex[u].position, G.vertex[v].position, edge.weight, G.connections[u][v], redFadeDown);
    }
    else
    {
        edge = G.FindEdge(v, u);
        G.DrawEdge(G.vertex[v].position, G.vertex[u].position, edge.weight, G.connections[u][v], redFadeDown);
    }

    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1)
        {
            Color color = SPRINGGREEN;
            if (i == u) color = CORALRED;
            else if (!state.isFound[i]) color = PEACHORANGE;

            G.DrawVertex(i, color);
        }
    
    G.DrawVertex(v, redFadeDown);

    trackingTable.focus(v);
    trackingTable.drawImportantLine(u, CORALRED);
    trackingTable.drawImportantLine(v, redFadeDown);
}

void DijkstraVisualize::Step5(Graph &G, State &state)
{
    int u = state.u;

    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1 && state.trace[i] != -1)
        {
            Color color = SPRINGGREEN;
            if (!state.isFound[i]) color = PEACHORANGE;

            Edge edge = G.FindEdge(state.trace[i], i);
            if (edge.real)
            {
                G.DrawEdge(G.vertex[state.trace[i]].position, G.vertex[i].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
            else
            {
                edge = G.FindEdge(i, state.trace[i]);
                G.DrawEdge(G.vertex[i].position, G.vertex[state.trace[i]].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
        }
    
    for (int i = 0; i <= G.numVertex; i++)
        if (state.distance[i] != -1)
        {
            Color color = SPRINGGREEN;
            if (!state.isFound[i]) color = PEACHORANGE;

            G.DrawVertex(i, color);
        }

    float delta = min((float)GetTime() - state.startTime, duration);
    if (isStatusSilderWork == 0) state.animationProcess = delta;

    Color redFadeDown = CORALRED;
    Color greenFadeUp = SPRINGGREEN;
    redFadeDown.a *= (duration - delta) / duration;
    greenFadeUp.a *= delta / duration;
    
    G.DrawVertex(u, redFadeDown);
    
    trackingTable.focus(u);
    trackingTable.drawImportantLine(u, CORALRED);
    trackingTable.drawImportantLine(u, greenFadeUp);
}

void DijkstraVisualize::Step6(Graph &G, State &state)
{
    for (int i = 0; i <= G.numVertex; i++)
        if (state.isFound[i] && state.trace[i] != -1)
        {
            Color color = SPRINGGREEN;

            Edge edge = G.FindEdge(state.trace[i], i);
            if (edge.real)
            {
                G.DrawEdge(G.vertex[state.trace[i]].position, G.vertex[i].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
            else
            {
                edge = G.FindEdge(i, state.trace[i]);
                G.DrawEdge(G.vertex[i].position, G.vertex[state.trace[i]].position, edge.weight, G.connections[i][state.trace[i]], color);
            }
        }

    float delta = min((float)GetTime() - state.startTime, duration);
    if (isStatusSilderWork == 0) state.animationProcess = delta;

    Color greenFadeDown = SPRINGGREEN;
    greenFadeDown.a *= (duration - delta) / duration;
    
    for (int i = 0; i <= G.numVertex; i++)
        if (!state.isFound[i] && state.distance[i] != -1 && state.trace[i] != -1)
        {
            Edge edge = G.FindEdge(state.trace[i], i);
            if (edge.real)
            {
                G.DrawEdge(G.vertex[state.trace[i]].position, G.vertex[i].position, edge.weight, G.connections[i][state.trace[i]], greenFadeDown);
            }
            else
            {
                edge = G.FindEdge(i, state.trace[i]);
                G.DrawEdge(G.vertex[i].position, G.vertex[state.trace[i]].position, edge.weight, G.connections[i][state.trace[i]], greenFadeDown);
            }
        }

    for (int i = 0; i <= G.numVertex; i++)
        if (state.isFound[i])
        {
            Color color = SPRINGGREEN;
            G.DrawVertex(i, color);
        }
    
    for (int i = 0; i <= G.numVertex; i++)
        if (!state.isFound[i] && state.distance[i] != -1)
            G.DrawVertex(i, greenFadeDown);
}

void DijkstraVisualize::clear()
{
    isDone = 0;
    isStop = 0;
    isStatusSilderWork = 0;
    controlPanel.statusSlider.thumb.x = controlPanel.statusSlider.bar.x;
    startVertex = -1;
    endVertex = -1;
    current = 0;
    states.clear();
    trackingTable.clear();
}