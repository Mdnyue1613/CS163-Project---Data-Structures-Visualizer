#include "../header/HGRAPH.h"
#include "../header/HOBJECT.h"
#include "../header/HGraphVisualize.h"
#include "../header/GUI.h"

void Graph::Initialize()
{
    numVertex = 0;
    numEdge = 0;
    type = 0;
    g.clear();
    g.push_back(vector <Edge>());
    vertex.clear();
    vertex.push_back(Vertex());
    vertex[0].real = 0;
    connections.clear();
    connections.push_back(vector <int> (1, 0));
    vertexRadius = 20;
    fontSize = vertexRadius;
    thick = 3;
    stable = 0;
}

void Graph::DrawGraph()
{
    if (numVertex == 0) return;

    MoveVertex();
    ForceDirectedGraph();

    for (int i = 0; i <= numVertex; i++)
        for (Edge &edge : g[i])
            if (edge.real)
                DrawEdge(vertex[i].position, vertex[edge.to].position, edge.weight, connections[i][edge.to], GUI::BackGroundColor[GUI::ColorMode ^ 1]);
    
    for (int i = 0; i <= numVertex; i++)
        if (vertex[i].real) 
        {
            if (vertex[i].isClick) DrawVertex(i, CORALRED);
            else DrawVertex(i, GUI::BackGroundColor[GUI::ColorMode ^ 1]);
        }
            
}

void Graph::DrawVertex(int ID, Color color)
{ 
    DrawCircleV(vertex[ID].position, vertexRadius, GUI::BackGroundColor[GUI::ColorMode]);
    DrawRing(vertex[ID].position, vertexRadius, vertexRadius + thick, 0, 360, 30, color);

    string text = to_string(ID);
    Vector2 textSize = MeasureTextEx(GUI::font, text.c_str(), fontSize, 0);
    DrawTextEx(GUI::font, text.c_str(), {vertex[ID].position.x - textSize.x/2, vertex[ID].position.y - textSize.y/2}, fontSize, 0, GUI::BackGroundColor[GUI::ColorMode ^ 1]);
}

void Graph::DrawEdge(Vector2 start, Vector2 end, int weight, int connections, Color color)
{
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float angle = atan2f(dy, dx);
    float lenght = Vector2Length(Vector2Subtract(end, start));
    Vector2 perpendicular = {-dy / lenght, dx / lenght};
    float perAngle = atan2f(perpendicular.y, perpendicular.x);
    if (connections > 1)
    {
        float shift = vertexRadius / 3;
        start = Vector2Add(start, Vector2{shift * cos(perAngle), shift * sin(perAngle)});
        end = Vector2Add(end, Vector2{shift * cos(perAngle), shift * sin(perAngle)});
    }

    DrawLineEx(start, end, thick, color);
    if (type == 1)
    {
        float triAltitude = thick * 4;
        Vector2 top = Vector2Subtract(end, Vector2{vertexRadius * cos(angle), vertexRadius * sin(angle)});
        Vector2 point = Vector2Subtract(top, Vector2{triAltitude * cos(angle), triAltitude * sin(angle)});
        Vector2 left = Vector2Add(point, Vector2{triAltitude/2 * cos(perAngle), triAltitude/2 * sin(perAngle)});
        Vector2 right = Vector2Subtract(point, Vector2{triAltitude/2 * cos(perAngle), triAltitude/2 * sin(perAngle)});

        DrawTriangle(left, top, right, color);
    }

    string text = to_string(weight);
    Vector2 textPos = Vector2Scale(Vector2Add(start, end), 0.5f);
    float wFontSize = fontSize * 8/9;
    Vector2 textSize = MeasureTextEx(GUI::font, text.c_str(), wFontSize, 0);
    float diag = sqrt(textSize.y * textSize.y + textSize.x * textSize.x);
    textPos.x += cos(perAngle) * diag;
    textPos.y += sin(perAngle) * diag;
        
    DrawTextEx(GUI::font, text.c_str(), textPos, wFontSize, 0, color);
}

void Graph::ChangeGraphType()
{
    type ^= 1;
    if (type == 0 && numVertex)
    {
        for (int i = 0; i <= numVertex; i++)
        {
            vector <int> isConnect(numVertex + 1, -1);
            vector <Edge> tmp;
            for (int j = 0; j < g[i].size(); j++)
                if (isConnect[g[i][j].to] == -1)
                {
                    tmp.push_back(g[i][j]);
                    isConnect[g[i][j].to] = tmp.size() - 1;
                }
                else
                {
                    tmp[isConnect[g[i][j].to]] = g[i][j];
                }
            g[i] = tmp;
        }
    }
}

void Graph::MoveVertex()
{
    Vector2 mouse = GetMousePosition();
    Vector2 displacement = {0, 0};

    int u = -1;
    for (int i = 0; i <= numVertex; i++)
        if (vertex[i].isClick == 1)
        {
            u = i;
            break;
        }
    
    if (u != -1)
    {
        stable = 0;
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            displacement = Vector2Subtract(mouse, vertex[u].lastMousePos);
            if (Vector2Length(displacement) > 0) 
                vertex[u].lastMousePos = mouse;
        }
        else vertex[u].isClick = 0;

        if (Vector2Length(displacement) > 0)
            vertex[u].position = Vector2Add(vertex[u].position, Vector2Multiply(displacement, {1.25f, 1.25f}));
        
        vertex[u].position.x = max(vertex[u].position.x, workspace.x +vertexRadius*2);
        vertex[u].position.x = min(vertex[u].position.x, workspace.x + workspace.width - vertexRadius*2);
        vertex[u].position.y = max(vertex[u].position.y, workspace.y +vertexRadius*2);
        vertex[u].position.y = min(vertex[u].position.y, workspace.y + workspace.height - vertexRadius*2);
    }
    else
    {
        for (int i = 0; i <= numVertex; i++)
            if (vertex[i].real)
            {
                if (CheckCollisionPointCircle(mouse, vertex[i].position, vertexRadius) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    vertex[i].isClick = 1;
                    vertex[i].lastMousePos = mouse;
                }
            }
    }
}

void Graph::ForceDirectedGraph()
{
    float adjustmentFactor = 2;
    float k = sqrt((workspace.height * workspace.width) / (float)realNumVertex) / adjustmentFactor;
    int maxIterations = 200;
    float maxForce = sqrt(workspace.width * workspace.height) / 10; 
    float dt = maxForce / (maxIterations + 1);
    float threshold = 10.0f;
    float damping = 0.0015f;

    for (int i = 1; i <= maxIterations && stable == 0; i++)
    {
        ApplyRepulsion(k);
        ApplyAttraction(k);
        ApplyGravitation(k * adjustmentFactor);
        if (IsStable(threshold))
        {
            stable = 1;
            for (int i = 0; i <= numVertex; i++)
                if (vertex[i].real)
                    vertex[i].force = {0, 0};
            break;
        }
        UpdatePosition(maxForce, damping);
        maxForce -= dt;
    }

    if (stable)
    {
        Zoom();
        UpdatePosition(maxForce, damping*50);
    }
}

void Graph::ApplyRepulsion(float k)
{
    for (int i = 0; i <= numVertex; i++)
        for (int j = i+1; j <= numVertex; j++)
            if (vertex[i].real && vertex[j].real)
            {
                Vector2 diff = Vector2Subtract(vertex[j].position, vertex[i].position);
                float distance = Vector2Length(diff);
                if (distance == 0) continue;
                float force = k * k / distance;
                float angle = atan2f(diff.y, diff.x);
                Vector2 repel = Vector2{force * cos(angle), force * sin(angle)};

                vertex[i].force = Vector2Subtract(vertex[i].force, repel);
                vertex[j].force = Vector2Add(vertex[j].force, repel);
            }
}

void Graph::ApplyAttraction(float k)
{
    bool isConnected[numVertex + 1][numVertex + 1];
    for (int i = 0; i <= numVertex; i++)
        for (int j = 0; j <= numVertex; j++)
            isConnected[i][j] = 0;
    
    for (int i = 0; i <= numVertex; i++)
        for (Edge &edge : g[i])
            if (!isConnected[i][edge.to])
            {
                isConnected[i][edge.to] = isConnected[edge.to][i] = 1;

                Vector2 diff = Vector2Subtract(vertex[edge.to].position, vertex[i].position);
                float distance = Vector2Length(diff);
                if (distance == 0) continue;
                float force = distance * distance / k;
                float angle = atan2f(diff.y, diff.x);
                Vector2 attract = Vector2{force * cos(angle), force * sin(angle)};

                vertex[i].force = Vector2Add(vertex[i].force, attract);
                vertex[edge.to].force = Vector2Subtract(vertex[edge.to].force, attract);
            }    
}

void Graph::ApplyGravitation(float k)
{
    Vector2 center = Vector2{workspace.x + workspace.width/2, workspace.y + workspace.height/2};
    for (int i = 0; i <= numVertex; i++)
        if (vertex[i].real)
        {
            Vector2 diff = Vector2Subtract(vertex[i].position, center);
            float distance = Vector2Length(diff);
            if (distance == 0) continue;
            float force = distance * distance / k;
            float angle = atan2f(diff.y, diff.x);
            Vector2 attract = Vector2{force * cos(angle), force * sin(angle)};

            vertex[i].force = Vector2Subtract(vertex[i].force, attract);
        }
}

void Graph::Zoom()
{
    Vector2 center = Vector2{workspace.x + workspace.width/2, workspace.y + workspace.height/2};
    float minDistX = center.x - workspace.x;
    float minDistY = center.y - workspace.y;

    for (int i = 0; i <= numVertex; i++)
        if (vertex[i].real)
        {
            minDistX = min(minDistX, min(vertex[i].position.x - workspace.x, workspace.x + workspace.width - vertex[i].position.x));
            minDistY = min(minDistY, min(vertex[i].position.y - workspace.y, workspace.y + workspace.height - vertex[i].position.y));
        }
    
    float zoom;
    if (minDistX <= minDistY)
        zoom = (workspace.width/2 - vertexRadius*2) / (workspace.width/2 - minDistX);
    else
        zoom = (workspace.height/2 - vertexRadius*2) / (workspace.height/2 - minDistY);
    
    for (int i = 0; i <= numVertex; i++)
        if (vertex[i].real)
        {
            float angle = atan2f(vertex[i].position.y - center.y, vertex[i].position.x - center.x);
            float lenght = Vector2Length(Vector2Subtract(vertex[i].position, center));
            lenght = abs(lenght * zoom - lenght);
            if (zoom > 1)
                vertex[i].force = Vector2Add(vertex[i].force, {cos(angle) * lenght, sin(angle) * lenght});
            else 
                vertex[i].force = Vector2Subtract(vertex[i].force, {cos(angle) * lenght, sin(angle) * lenght});
        }
}

bool Graph::IsStable(float threshold)
{
    float maxForce = 0;
    for (int i = 0; i <= numVertex; i++)
        if (vertex[i].real)
            maxForce = max(maxForce, Vector2Length(vertex[i].force));

    return maxForce < threshold;
}

void Graph::UpdatePosition(float maxForce, float damping)
{
    for (int i = 0; i <= numVertex; i++)
        if (vertex[i].real && Vector2Length(vertex[i].force) > 0)
        {
            if (Vector2Length(vertex[i].force) > maxForce)
            {
                float angle = atan2f(vertex[i].force.y, vertex[i].force.x);
                vertex[i].force = Vector2{maxForce * cos(angle), maxForce * sin(angle)};
            }
            float force = Vector2Length(vertex[i].force);
            float angle = atan2f(vertex[i].force.y, vertex[i].force.x);
            vertex[i].force = Vector2{damping * force * cos(angle), damping * force * sin(angle)};

            if (vertex[i].isClick == 0)
            {
                vertex[i].position = Vector2Add(vertex[i].position, vertex[i].force);
            }
            vertex[i].force = {0, 0};
        }
}

void Graph::SetInitialPosition()
{
    float angleStep = 2 * PI / realNumVertex;
    Vector2 center = Vector2{(workspace.x + GetScreenWidth())/2, (workspace.y + GetScreenHeight())/2};
    float INITIAL_RADIUS = workspace.height / 500;
    int count = 0;
    
    for (int i = 0; i <= numVertex; i++) 
        if (vertex[i].real)
        {
            count++;
            vertex[i].position.x = center.x + INITIAL_RADIUS * cos(count * angleStep);
            vertex[i].position.y = center.y + INITIAL_RADIUS * sin(count * angleStep);
        }
}

void Graph::RandomData()
{
    stable = 0;
    numVertex = Rand(3, 10);
    realNumVertex = numVertex;

    vertex.clear();
    vertex.resize(numVertex + 1);

    for (int i = 1; i <= numVertex; i++)
        vertex[i].real = 1;

    float edgeProb;
    if (numVertex <= 5) edgeProb = 0.7f;
    else if (numVertex <= 8) edgeProb = 0.4f;
    else edgeProb = 0.2f;

    numEdge = 0;
    g.clear();
    g.resize(numVertex + 1);
    for (int i = 1; i <= numVertex; i++)
        for (int j = 1; j <= numVertex; j++)
            if (i != j)
            {
                if (type == 0 && j < i) continue;
                if ((Rand(1, 100)) < edgeProb * 100)
                {
                    numEdge++;
                    int weight = Rand(1, 20);
                    g[i].push_back(Edge(1, j, weight));
                    g[j].push_back(Edge(0, i, weight));
                }
            }
    
    connections.clear();
    connections.resize(numVertex + 1, vector <int>(numVertex + 1, 0));
    for (int i = 0; i <= numVertex; i++)
        for (Edge &edge : g[i])
            if (edge.real)
            {
                connections[i][edge.to]++;
                connections[edge.to][i]++;
            }
    
    SetInitialPosition();
}

void Graph::LoadFromFile(const char* filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        GraphGUI::Notify((const char*)"Cannot open file!!!");
        return;
    }

    vector <string> userInput;
    while (!file.eof())
    {
        string tmp;
        getline(file, tmp);
        userInput.push_back(tmp);
    }

    LoadNewGraph(userInput);
    if (numVertex)
        SetInitialPosition();
    
    file.close();
}

void Graph::LoadFromKeyBoard(vector <string> &userInput)
{
    LoadNewGraph(userInput);
    if (numVertex)
        SetInitialPosition();
}

void Graph::LoadNewGraph(vector <string> &userInput)
{
    bool success = 1;
    int cursor = 0;
    int n, m;

    success = GetNumFromStr(userInput[0], cursor, n);
    if (!success)
    {
        GraphGUI::Notify((const char*)"Please check the format and the data of input!!!");
        return;
    }

    success = GetNumFromStr(userInput[0], cursor, m);
    if (!success)
        LoadAdjacencyMatrix(userInput);
    else 
        LoadAdjacencyList(userInput);
}

void Graph::LoadAdjacencyList(vector <string> &userInput)
{
    bool success = 1;
    int cursor = 0;

    stable = 0;
    g.clear();
    vertex.clear();
    connections.clear();

    GetNumFromStr(userInput[0], cursor, numVertex);
    GetNumFromStr(userInput[0], cursor, numEdge);
    g.resize(numVertex + 1);
    vertex.resize(numVertex + 1);
    connections.resize(numVertex + 1, vector <int>(numVertex + 1, 0));
    realNumVertex = numVertex;

    for (int i = 1; i <= numVertex; i++)
        vertex[i].real = 1;

    if (userInput.size() < numEdge + 1)
    {
        GraphGUI::Notify((const char*)"Please check the format and the data of input!!!");
        g.clear();
        vertex.clear();
        connections.clear();
        numVertex = realNumVertex = numEdge = 0;
        return;
    }

    vector <ii_i> edges;
    for (int i = 1; i <= numEdge; i++)
    {
        cursor = 0;
        int u, v, w;
        success = GetNumFromStr(userInput[i], cursor, u);
        success = GetNumFromStr(userInput[i], cursor, v);
        success = GetNumFromStr(userInput[i], cursor, w);
        if (!success || u > numVertex || v > numVertex)
        {
            GraphGUI::Notify((const char*)"Please check the format and the data of input!!!");
            g.clear();
            vertex.clear();
            connections.clear();
            numVertex = realNumVertex = numEdge = 0;
            return;
        }
        if (type == 0 && u > v) swap(u, v);
        edges.push_back(ii_i(ii(u, v), w));
    }
    sort(edges.begin(), edges.end());

    LoadEdgeList(edges);
}

void Graph::LoadAdjacencyMatrix(vector <string> &userInput)
{
    bool success = 1;
    int cursor = 0;

    stable = 0;
    g.clear();
    vertex.clear();
    connections.clear();

    GetNumFromStr(userInput[0], cursor, numVertex);
    g.resize(numVertex + 1);
    vertex.resize(numVertex + 1);
    connections.resize(numVertex + 1, vector <int>(numVertex + 1, 0));
    realNumVertex = numVertex;

    for (int i = 1; i <= numVertex; i++)
        vertex[i].real = 1;
    
    if (userInput.size() < numVertex + 1)
    {
        GraphGUI::Notify((const char*)"Please check the format and the data of input!!!");
        g.clear();
        vertex.clear();
        connections.clear();
        numVertex = realNumVertex = numEdge = 0;
        return;
    }

    vector <ii_i> edges;
    for (int i = 1; i <= numVertex; i++)
    {
        cursor = 0;
        int j = 0;
        int w = 0;
        while (j < numVertex)
        {
            j++;

            success = GetNumFromStr(userInput[i], cursor, w);
            if (!success)
            {
                GraphGUI::Notify((const char*)"Please check the format and the data of input!!!");
                g.clear();
                vertex.clear();
                connections.clear();
                numVertex = realNumVertex = numEdge = 0;
                return;
            }
            if (w != 0) 
            {
                numEdge++;
                if (type == 0 && i > j)
                    edges.push_back(ii_i(ii(j, i), w));
                else 
                edges.push_back(ii_i(ii(i, j), w));
            }
        }
    }
    sort(edges.begin(), edges.end());

    LoadEdgeList(edges);
}

void Graph::LoadEdgeList(vector <ii_i> &edges)
{
    int duplicate = 0;
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first.first;
        int v = edges[i].first.second;
        int w = edges[i].second;
        if (i > 0 && edges[i].first == edges[i-1].first)
        {
            g[u].back().weight = w;
            g[v].back().weight = w;
            duplicate++;
        }
        else 
        {
            g[u].push_back(Edge(1, v, w));
            g[v].push_back(Edge(0, u, w));
            vertex[u].force = vertex[v].force = {0, 0};
            if (u == 0 && !vertex[u].real) 
            {
                vertex[u].real = 1;
                realNumVertex++;
            }
            if (v == 0 && !vertex[v].real)
            {
                vertex[v].real = 1;
                realNumVertex++;
            }
        }
    }
    numEdge -= duplicate;

    for (int i = 0; i <= numVertex; i++)
        for (Edge &edge : g[i])
            if (edge.real)
            {
                connections[i][edge.to]++;
                connections[edge.to][i]++;
            }
    
    for (int i = 0; i <= numVertex; i++)
        vertex[i].isClick = 0;
}

void Graph::Add(vector <string> &userInput) 
{
    bool success1, success2, success3;
    int cursor;

    for (int i = 0; i < userInput.size(); i++)
    {
        cursor = 0;
        int u, v, w;
        success1 = GetNumFromStr(userInput[i], cursor, u);
        success2 = GetNumFromStr(userInput[i], cursor, v);
        success3 = GetNumFromStr(userInput[i], cursor, w);

        if (success1 && !success2) 
        {
            AddVertex(u);
            stable = 0;
        }
        else if (success1 && success2 && success3)
        {
            AddEdge(u, v, w);
            stable = 0;
        }
        else if (success1 && success2 && !success3)
        {
            GraphGUI::Notify((const char*)"Please check the format and the data of input!!!");
            return;
        }
    }
}

void Graph::AddVertex(int u)
{
    for (int i = numVertex + 1; i <= u; i++)
    {
        g.push_back(vector <Edge>());
        vertex.push_back(Vertex());
        connections.push_back(vector <int> (max(numVertex, u) + 1, 0));
    }

    numVertex = max(numVertex, u);
    for (int i = 0; i <= numVertex; i++)
    {
        int tmp = numVertex + 1 - connections[i].size();
        for (int j = 1; j <= tmp; j++)
            connections[i].push_back(0);
    }

    if (!vertex[u].real)
    {
        realNumVertex++;
        vertex[u].real = 1;
        vertex[u].position.x = GetScreenWidth() + vertexRadius + Rand(0, 100);
        vertex[u].position.y = GetScreenHeight() + vertexRadius + Rand(0, 100);
        vertex[u].isClick = 0;
    }
}

void Graph::AddEdge(int u, int v, int w)
{
    AddVertex(u);
    AddVertex(v);

    int pos = FindEdgeID(g[u], v, 1);
    if (pos == -1)
    {
        if (type == 1)
        {
            g[u].push_back(Edge(1, v, w));
            g[v].push_back(Edge(0, u, w));
            connections[u][v]++;
            connections[v][u]++;
            numEdge++;
        }
        else
        {
            pos = FindEdgeID(g[u], v, 0);
            if (pos == -1)
            {
                g[u].push_back(Edge(1, v, w));
                g[v].push_back(Edge(0, u, w));
                connections[u][v]++;
                connections[v][u]++;
                numEdge++;
            }
            else
            {
                g[u][pos].real = 1;
                g[u][pos].weight = w;
                pos = FindEdgeID(g[v], u, 1);
                g[v][pos].real = 0;
                g[v][pos].weight = w;
            }
        }
    }
    else
    {
        g[u][pos].weight = w;
        pos = FindEdgeID(g[v], u, 0);
        g[v][pos].weight = w;
    }
}

void Graph::Delete(vector <string> &userInput)
{
    bool success1, success2, success3;
    int cursor;

    for (int i = 0; i < userInput.size(); i++)
    {
        cursor = 0;
        int u, v, w;
        success1 = GetNumFromStr(userInput[i], cursor, u);
        success2 = GetNumFromStr(userInput[i], cursor, v);
        success3 = GetNumFromStr(userInput[i], cursor, w);

        if (success1 && !success2) 
        {
            DeleteVertex(u);
            stable = 0;
        }
        else if (success1 && success2 && success3)
        {
            DeleteEdge(u, v, w);
            stable = 0;
        }
        else if (success1 && success2 && !success3)
        {
            GraphGUI::Notify((const char*)"Please check the format and the data of input!!!");
            return;
        }
    }
}

void Graph::DeleteVertex(int u)
{
    if (u > numVertex) return;

    for (int i = 0; i <= numVertex; i++)
    {
        int count = 0;
        for (int j = 0; j < g[i].size(); j++)
        if (g[i][j].to != u)
        {
            g[i][j - count] = g[i][j];
        }
        else count++;
        
        while (count)
        {
            g[i].pop_back();
            count--;
        }
    }
    numEdge -= g[u].size();
    
    if (u == numVertex)
    {
        numVertex--;
        realNumVertex--;
        g.pop_back();
        vertex.pop_back();
        connections.pop_back();
    }
    else
    {
        realNumVertex--;
        g[u].clear();
        vertex[u] = Vertex();
        for (int i = 0; i <= numVertex; i++)
            connections[u][i] = connections[i][u] = 0;
    }
}

void Graph::DeleteEdge(int u, int v, int w)
{
    if (u > numVertex || v > numVertex) return;

    int count = 0;
    for (int i = 0; i < g[u].size(); i++)
        if (g[u][i].to != v || g[u][i].weight != w)
        {
            g[u][i - count] = g[u][i];
        }
        else count++;
    
    while (count)
    {
        g[u].pop_back();
        count--;
        numEdge--;
    }
    
    count = 0;
    for (int i = 0; i < g[v].size(); i++)
        if (g[v][i].to != u || g[v][i].weight != w)
        {
            g[v][i - count] = g[v][i];
        }
        else count++;
    
    while (count)
    {
        g[v].pop_back();
        count--;
        connections[u][v]--;
        connections[v][u]--;
    }
}

void Graph::SynchronizeData(InputBox &box)
{
    box.userInput.clear();
    box.userInput.push_back(NumToStr(numVertex) + ' ' + NumToStr(numEdge));

    for (int i = 0; i <= numVertex; i++)
        for (Edge &e : g[i])
            if (e.real)
                box.userInput.push_back(NumToStr(i) + ' ' + NumToStr(e.to) + ' ' + NumToStr(e.weight));
    
    box.firstLine = 0;
    box.firstChar = 0;
    box.cursorPos = {0, 0};
}

Edge Graph::FindEdge(int u, int v)
{
    for (Edge &edge : g[u])
        if (edge.to == v)
            return edge;
    
    return Edge();
}

long long Rand(long long l, long long r)
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<long long>(l,r)(rng);
}

bool GetNumFromStr(string &s, int &pos, int &num)
{
    num = -1;

    while (pos < s.size() && !isdigit(s[pos]))
        pos++;
    
    while (pos < s.size() && isdigit(s[pos]))
    {
        if (num == -1) num = 0;
        num = num * 10 + s[pos] - '0';
        pos++;
    }

    if (num != -1) return 1;
    else
    {
        num = 0;
        return 0;
    }
}

string NumToStr(int num)
{
    string s = "";
    while (num)
    {
        s += char(num % 10 + '0');
        num /= 10;
    }
    if (s.empty()) s.push_back('0');
    
    int lenght = s.size();
    for (int i = 0; i < lenght / 2; i++)
        swap(s[i], s[lenght-i-1]);
    
    return s;
}

int FindEdgeID(vector <Edge> &g, int v, bool real)
{
    for (int i = 0; i < g.size(); i++)
        if (g[i].to == v && g[i].real == real)
            return i;

    return -1;
}
