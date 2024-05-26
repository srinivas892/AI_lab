#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

map<string, map<string, int>> graph = {
    {"Arad", {{"Zerind", 75}, {"Sibiu", 140}, {"Timisoara", 118}}},
    {"Zerind", {{"Arad", 75}, {"Oradea", 71}}},
    {"Oradea", {{"Zerind", 71}, {"Sibiu", 151}}},
    {"Sibiu", {{"Arad", 140}, {"Oradea", 151}, {"Fagaras", 99}, {"Rimnicu Vilcea", 80}}},
    {"Timisoara", {{"Arad", 118}, {"Lugoj", 111}}},
    {"Lugoj", {{"Timisoara", 111}, {"Mehadia", 70}}},
    {"Mehadia", {{"Lugoj", 70}, {"Drobeta", 75}}},
    {"Drobeta", {{"Mehadia", 75}, {"Craiova", 120}}},
    {"Craiova", {{"Drobeta", 120}, {"Rimnicu Vilcea", 146}, {"Pitesti", 138}}},
    {"Rimnicu Vilcea", {{"Sibiu", 80}, {"Craiova", 146}, {"Pitesti", 97}}},
    {"Fagaras", {{"Sibiu", 99}, {"Bucharest", 211}}},
    {"Pitesti", {{"Rimnicu Vilcea", 97}, {"Craiova", 138}, {"Bucharest", 101}}},
    {"Bucharest", {{"Fagaras", 211}, {"Pitesti", 101}, {"Giurgiu", 90}, {"Urziceni", 85}}},
    {"Giurgiu", {{"Bucharest", 90}}},
    {"Urziceni", {{"Bucharest", 85}, {"Vaslui", 142}, {"Hirsova", 98}}},
    {"Vaslui", {{"Urziceni", 142}, {"Iasi", 92}}},
    {"Iasi", {{"Vaslui", 92}, {"Neamt", 87}}},
    {"Neamt", {{"Iasi", 87}}},
    {"Hirsova", {{"Urziceni", 98}, {"Eforie", 86}}},
    {"Eforie", {{"Hirsova", 86}}}};

map<string, int> heuristic = {
    {"Arad", 366}, {"Zerind", 374}, {"Oradea", 380}, {"Sibiu", 253}, {"Timisoara", 329}, {"Lugoj", 244}, {"Mehadia", 241}, {"Drobeta", 242}, {"Craiova", 160}, {"Rimnicu Vilcea", 193}, {"Fagaras", 178}, {"Pitesti", 98}, {"Bucharest", 0}, {"Giurgiu", 77}, {"Urziceni", 80}, {"Vaslui", 199}, {"Iasi", 226}, {"Neamt", 234}, {"Hirsova", 151}, {"Eforie", 161}};

struct Node
{
    string city;
    int g; // Cost from start to current node
    int h; // Heuristic (estimated cost from current node to goal)
    Node *parent;

    Node(string c, int cost, int est, Node *p) : city(c), g(cost), h(est), parent(p) {}

    int f() const { return g + h; }
};

struct CompareNode
{
    bool operator()(const Node *a, const Node *b) const
    {
        return a->f() > b->f();
    }
};

// A* algorithm implementation
pair<vector<string>, int> aStar(string start, string goal)
{
    map<string, bool> visited;
    priority_queue<Node *, vector<Node *>, CompareNode> openSet;
    openSet.push(new Node(start, 0, heuristic[start], nullptr));

    while (!openSet.empty())
    {
        Node *current = openSet.top();
        openSet.pop();

        if (current->city == goal)
        {
            vector<string> path;
            int totalDistance = current->g; 
            while (current != nullptr)
            {
                path.push_back(current->city);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return make_pair(path, totalDistance);
        }

        visited[current->city] = true;

        for (auto neighbor : graph[current->city])
        {
            if (!visited[neighbor.first])
            {
                int g = current->g + neighbor.second;
                int h = heuristic[neighbor.first];
                openSet.push(new Node(neighbor.first, g, h, current));
            }
        }
    }

    return make_pair(vector<string>{}, 0);
}

int main()
{
    string start = "Arad";
    string goal = "Bucharest";

    auto result = aStar(start, goal);
    vector<string> path = result.first;
    int totalDistance = result.second;

    cout << "Path: ";
    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i];
        if (i != path.size() - 1)
        {
            cout << "->";
        }
    }
    cout << endl;
    cout << "Total distance: " << totalDistance << endl;
    return 0;
}
