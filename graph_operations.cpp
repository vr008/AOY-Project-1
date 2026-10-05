#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<int>>;


// -----------------------------
// DFS for connected components
// -----------------------------

void dfs(int u,
         vector<vector<int>>& adj,
         vector<int>& visited,
         vector<int>& component)
{
    visited[u] = 1;
    component.push_back(u);

    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfs(v, adj, visited, component);
        }
    }
}


// -----------------------------
// Connected Components
// -----------------------------

vector<vector<int>> connectedComponents(
    const Graph& graph,
    int V)
{
    // Store adjacency using one large vector of edges.
    // This uses less memory than vector<vector<int>>.
    vector<vector<int>> adj(V);

    for (const auto& edge : graph)
    {
        int u = edge[0];
        int v = edge[1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> visited(V, 0);

    vector<vector<int>> components;

    for (int i = 0; i < V; i++)
    {
        if (visited[i])
            continue;

        vector<int> component;
        stack<int> st;

        st.push(i);
        visited[i] = 1;

        while (!st.empty())
        {
            int node = st.top();
            st.pop();

            component.push_back(node);

            for (int neighbor : adj[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = 1;
                    st.push(neighbor);
                }
            }
        }

        components.push_back(component);
    }

    return components;
}




// vector<vector<int>> connectedComponents(
//     const Graph& graph,
//     int V)
// {
//     vector<vector<int>> adj(V);

//     // Convert edge list to adjacency list
//     for (const auto& edge : graph)
//     {
//         int u = edge[0];
//         int v = edge[1];

//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }

//     vector<int> visited(V, 0);
//     vector<vector<int>> components;

//     for (int i = 0; i < V; i++)
//     {
//         if (!visited[i])
//         {
//             vector<int> component;

//             dfs(i, adj, visited, component);

//             components.push_back(component);
//         }
//     }

//     return components;
// }



// -----------------------------
// DFS for cycle detection
// -----------------------------

vector<int> findCycle(
    int u,
    int parent,
    vector<vector<int>>& adj,
    vector<int>& visited,
    vector<int>& path)
{
    visited[u] = 1;
    path.push_back(u);

    for (int v : adj[u])
    {
        if (!visited[v])
        {
            vector<int> cycle =
                findCycle(v, u, adj, visited, path);

            if (!cycle.empty())
            {
                return cycle;
            }
        }
        else if (v != parent)
        {
            vector<int> cycle;

            cycle.push_back(v);

            for (int i = path.size() - 1; i >= 0; i--)
            {
                cycle.push_back(path[i]);

                if (path[i] == v)
                {
                    break;
                }
            }

            return cycle;
        }
    }

    path.pop_back();

    return {};
}


// -----------------------------
// Find one cycle
// -----------------------------

vector<int> oneCycle(
    int V,
    const Graph& graph)
{
    vector<vector<int>> adj(V);

    for (const auto& edge : graph)
    {
        int u = edge[0];
        int v = edge[1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> visited(V, 0);
    vector<int> path;

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            vector<int> cycle =
                findCycle(i, -1, adj, visited, path);

            if (!cycle.empty())
            {
                return cycle;
            }
        }
    }

    return {};
}


// -----------------------------
// Dijkstra
// -----------------------------

vector<int> dijkstra(
    int V,
    const Graph& graph,
    int source)
{
    vector<vector<pair<int, int>>> adj(V);

    // Build adjacency list
    for (const auto& edge : graph)
    {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    vector<int> distance(V, 1e9);
    vector<int> parent(V, -1);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        int currentDistance = pq.top().first;
        int u = pq.top().second;

        pq.pop();

        if (currentDistance != distance[u])
        {
            continue;
        }

        for (auto edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (distance[u] + weight < distance[v])
            {
                distance[v] =
                    distance[u] + weight;

                parent[v] = u;

                pq.push({distance[v], v});
            }
        }
    }

    return parent;
}


// -----------------------------
// Shortest Paths
// -----------------------------

vector<vector<int>> shortestPaths(
    const Graph& graph,
    int V,
    int source)
{
    vector<int> parent =
        dijkstra(V, graph, source);

    vector<vector<int>> paths(V);

    for (int v = 0; v < V; v++)
    {
        // Skip unreachable vertices
        if (v != source && parent[v] == -1)
        {
            continue;
        }

        int current = v;

        while (current != -1)
        {
            paths[v].push_back(current);

            if (current == source)
            {
                break;
            }

            current = parent[current];
        }
    }

    return paths;
}