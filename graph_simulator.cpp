#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<int>>;


// -----------------------------
// Add an edge
// Format: {u, v, 1}
// -----------------------------

void addEdge(Graph& graph, int u, int v)
{
    graph.push_back({u, v, 1});
}


// -----------------------------
// Cycle Graph
// -----------------------------

Graph makeCycle(int n)
{
    Graph graph;

    if (n < 3)
    {
        return graph;
    }

    for (int i = 0; i < n; i++)
    {
        int next = (i + 1) % n;

        addEdge(graph, i, next);
    }

    return graph;
}


// -----------------------------
// Complete Graph
// -----------------------------

Graph makeComplete(int n)
{
    Graph graph;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            addEdge(graph, i, j);
        }
    }

    return graph;
}


// -----------------------------
// Empty Graph
// -----------------------------

Graph makeEmpty(int n)
{
    Graph graph;

    // There are n vertices,
    // but there are no edges.
    return graph;
}


// -----------------------------
// Heap Graph
// -----------------------------

Graph makeHeap(int n)
{
    Graph graph;

    for (int i = 1; i < n; i++)
    {
        int parent = (i - 1) / 2;

        addEdge(graph, i, parent);
    }

    return graph;
}