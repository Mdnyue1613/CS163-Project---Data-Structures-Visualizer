#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include "HOBJECT.h"

using namespace std;

struct Vertex
{
    bool real;
    bool isClick;
    Vector2 lastMousePos;
    Vector2 position;
    Vector2 force;
    Vertex()
    {
        real = 0;
        position = force = {0, 0};
    };
    Vertex(bool Real, Vector2 Position, Vector2 Force)
    {
        real = Real;
        position = Position;
        force = Force;
        isClick = 0;
    };
};

struct Edge
{
    bool real;
    int to;
    int weight;
    Edge(){};
    Edge(bool Real, int To, int Weight)
    {
        real = Real;
        to = To;
        weight = Weight;
    };
};

typedef pair <int, int> ii;
typedef pair <pair <int, int>, int> ii_i;

struct Graph
{
    bool type;
    int numVertex;
    int numEdge;
    vector <vector<Edge>> g;
    vector <Vertex> vertex;
    vector <vector<int>> connections;
    int realNumVertex;
    float vertexRadius;
    float fontSize;
    float thick;
    bool stable;
    Rectangle workspace;
    void Initialize();
    void DrawGraph();
    void DrawVertex(int ID, Color color);
    void DrawEdge(Vector2 start, Vector2 end, int weight, int connections, Color color);
    void ChangeGraphType();

    void MoveVertex();
    void ForceDirectedGraph();
    void ApplyRepulsion(float k);
    void ApplyAttraction(float k);
    void ApplyGravitation(float k);
    void Zoom();
    bool IsStable(float threshold);
    void UpdatePosition(float t, float damping);
    void SetInitialPosition();

    void RandomData();
    void LoadFromFile(const char* filePath);
    void LoadFromKeyBoard(vector <string> &userInput);
    void LoadNewGraph(vector <string> &userInput);
    void LoadAdjacencyList(vector <string> &userInput);
    void LoadAdjacencyMatrix(vector <string> &userInput);
    void LoadEdgeList(vector <ii_i> &edges);
    void Add(vector <string> &userInput);
    void AddVertex(int u);
    void AddEdge(int u, int v, int w);
    void Delete(vector <string> &userInput);
    void DeleteVertex(int u);
    void DeleteEdge(int u, int v, int w);
    void SynchronizeData(InputBox &box);  

    Edge FindEdge(int u, int v);
};

long long Rand(long long l, long long r);
bool GetNumFromStr(string &s, int &pos, int &num);
string NumToStr(int num);
int FindEdgeID(vector <Edge> &g, int v, bool real);