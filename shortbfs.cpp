#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    string source, dest;
    int weight;

    Edge(string source, string dest, int weight) : source(source), dest(dest), weight(weight) {}
};

class PQNode
{
public:
    string node;
    int priority;
    int distance;  

    PQNode(string node, int priority, int distance) : node(node), priority(priority), distance(distance) {}

    bool operator<(const PQNode &other) const
    {
        return priority > other.priority;
    }
};

class Graph
{
public:
    unordered_map<string, vector<Edge>> adjList;

    Graph(vector<Edge> const &edges)
    {
        for (auto &edge : edges)
        {
            adjList[edge.source].push_back(edge);
        }
    }
};

unordered_map<string, int> heuristic = {
    {"Arad", 366}, {"Bucharest", 0}, {"Craiova", 160}, {"Dobreta", 242}, {"Eforie", 161}, {"Fagaras", 176}, {"Giurgiu", 77}, {"Hirsova", 151}, {"Iasi", 226}, {"Lugoj", 244}, {"Mehadia", 241}, {"Neamt", 234}, {"Oradea", 380}, {"Pitesti", 100}, {"Rimnicu Vilcea", 193}, {"Sibiu", 253}, {"Timisoara", 329}, {"Urziceni", 80}, {"Vaslui", 199}, {"Zerind", 374}};

void bestFirstSearch(const Graph &graph, string src, string dest)
{
    priority_queue<PQNode> pq;
    unordered_set<string> visited;
    unordered_map<string, string> path;

    pq.push(PQNode(src, 0, 0));

    while (!pq.empty())
    {
        string currentNode = pq.top().node;
        int currentPriority = pq.top().priority;
        int currentDistance = pq.top().distance;
        pq.pop();

        visited.insert(currentNode);

        if (currentNode == dest)
        {
            cout << "Path: ";
            string node = dest;
            vector<string> reversePath;
            while (node != src)
            {
                reversePath.push_back(node);
                node = path[node];
            }
            reversePath.push_back(src);
            for (int i = reversePath.size() - 1; i > 0; --i)
            {
                cout << reversePath[i] << " -> ";
            }
            cout << reversePath[0] << endl;
            cout << "Total Distance: " << currentDistance << " km";
            break;
        }

        for (const Edge &edge : graph.adjList.at(currentNode))
        {
            if (visited.find(edge.dest) == visited.end())
            {
                int priority = edge.weight + heuristic.at(edge.dest);
                int newDistance = currentDistance + edge.weight;
                pq.push(PQNode(edge.dest, priority, newDistance));
                path[edge.dest] = currentNode;
            }
        }
    }
}

int main()
{
    vector<Edge> edges = {
        {"Arad", "Zerind", 75}, {"Arad", "Sibiu", 140}, {"Arad", "Timisoara", 118}, {"Zerind", "Oradea", 71}, {"Oradea", "Sibiu", 151}, {"Timisoara", "Lugoj", 111}, {"Lugoj", "Mehadia", 70}, {"Mehadia", "Dobreta", 75}, {"Dobreta", "Craiova", 120}, {"Craiova", "Rimnicu Vilcea", 146}, {"Craiova", "Pitesti", 138}, {"Rimnicu Vilcea", "Sibiu", 80}, {"Rimnicu Vilcea", "Pitesti", 97}, {"Sibiu", "Fagaras", 99}, {"Fagaras", "Bucharest", 211}, {"Pitesti", "Bucharest", 101}, {"Bucharest", "Giurgiu", 90}, {"Bucharest", "Urziceni", 85}, {"Urziceni", "Vaslui", 142}, {"Vaslui", "Iasi", 92}, {"Iasi", "Neamt", 87}, {"Urziceni", "Hirsova", 98}, {"Hirsova", "Eforie", 86}};

    Graph graph(edges);

    string src = "Arad";
    string dest = "Bucharest";

    bestFirstSearch(graph, src, dest);

    return 0;
}
