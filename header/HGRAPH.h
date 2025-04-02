#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

struct Vertex
{
    bool real;
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

struct Graph
{
    bool type;
    int numVertex;
    int numEdge;
    vector <vector<Edge>> g;
    vector <Vertex> vertex;
    int realNumVertex;
    float vertexRadius;
    float fontSize;
    float thick;
    bool stable;
    Rectangle workspace;
    void Initialize();
    void DrawGraph();
    void DrawVertex(int ID);
    void DrawEdge(Vector2 start, Vector2 end, int weight, int connections);
    void ChangeGraphType();
    void ForceDirectedGraph();
    void ApplyRepulsion(float k);
    void ApplyAttraction(float k);
    void ApplyGravitation(float k);
    bool Zoom();
    bool IsStable(float threshold);
    void UpdatePosition(float t, float damping);
    void RandomData();
    void LoadFromFile(const char* filePath);
    // void LoadFromInputBox(vector <string> &userInput);
};