#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<int>>;

// Functions from graph_operations.cpp
vector<vector<int>> connectedComponents(const Graph&, int);
vector<int> oneCycle(int, const Graph&);
vector<vector<int>> shortestPaths(const Graph&, int, int);


// ------------------------------------------------------------
// Adjacency criteria used for the real-world graph:
//
// Criterion 1 - Undirected adjacency:
// Keep only u < v. The roadNet-PA file contains both
// directions of each road, so this removes the duplicate.
//
// Criterion 2 - Original input adjacency:
// Keep every (u,v) pair exactly as it appears in the file.
//
// Criterion 3 - Reverse adjacency:
// Reverse every input pair from (u,v) to (v,u).
//
// The assignment graph is UNDIRECTED, so Criterion 1 is used
// for the main results. Criteria 2 and 3 are also actually
// tested below to satisfy the adjacency-criteria bonus.
// ------------------------------------------------------------


Graph loadRoadNetwork(const string& filename,
                      int& V,
                      int& officialNodes,
                      Graph& originalGraph,
                      Graph& reverseGraph)
{
    ifstream file(filename);

    if (!file)
    {
        cerr << "ERROR: Could not open " << filename << endl;
        exit(1);
    }

    Graph graph;

    string line;

    V = 0;
    officialNodes = 0;

    while (getline(file, line))
    {
        // Read official number of vertices from header
        if (line.rfind("# Nodes:", 0) == 0)
        {
            string temp1, temp2;
            stringstream ss(line);

            ss >> temp1 >> temp2 >> officialNodes;
            continue;
        }

        // Ignore comments and empty lines
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);

        int u, v;

        if (!(ss >> u >> v))
            continue;

        // Make sure V is large enough for the largest node ID
        V = max(V, max(u, v) + 1);

        // Criterion 1:
        // Keep one copy of each undirected edge.
        if (u < v)
        {
            graph.push_back({u, v, 1});
        }

        // Criterion 2:
        // Keep the input pair exactly as it appears.
        originalGraph.push_back({u, v, 1});

        // Criterion 3:
        // Reverse the input pair.
        reverseGraph.push_back({v, u, 1});
    }

    file.close();

    return graph;
}


void runConnectedComponents(const Graph& graph, int V)
{
    cout << "\n===== Criterion 1: Undirected adjacency =====\n";
    cout << "Testing connectedComponents()\n";

    auto start = chrono::high_resolution_clock::now();

    vector<vector<int>> components =
        connectedComponents(graph, V);

    auto end = chrono::high_resolution_clock::now();

    long long time =
        chrono::duration_cast<chrono::microseconds>
        (end - start).count();

    cout << "Number of components: "
         << components.size() << endl;

    cout << "Time: "
         << time << " microseconds" << endl;

    components.clear();
    components.shrink_to_fit();
}


void runCycle(const Graph& graph, int V)
{
    cout << "\n===== Criterion 2: Original input adjacency =====\n";
    cout << "Testing oneCycle()\n";

    auto start = chrono::high_resolution_clock::now();

    vector<int> cycle = oneCycle(V, graph);

    auto end = chrono::high_resolution_clock::now();

    long long time =
        chrono::duration_cast<chrono::microseconds>
        (end - start).count();

    if (cycle.empty())
        cout << "No cycle found." << endl;
    else
        cout << "Cycle found. Cycle vertices: "
             << cycle.size() << endl;

    cout << "Time: "
         << time << " microseconds" << endl;

    cycle.clear();
    cycle.shrink_to_fit();
}


void runShortestPaths(const Graph& graph, int V)
{
    cout << "\n===== Criterion 3: Reverse adjacency =====\n";
    cout << "Testing shortestPaths()\n";

    auto start = chrono::high_resolution_clock::now();

    vector<vector<int>> paths =
        shortestPaths(graph, V, 0);

    auto end = chrono::high_resolution_clock::now();

    long long time =
        chrono::duration_cast<chrono::microseconds>
        (end - start).count();

    long long reachable = 0;
    long long totalPathVertices = 0;

    for (const auto& path : paths)
    {
        if (!path.empty())
        {
            reachable++;
            totalPathVertices += path.size();
        }
    }

    cout << "Reachable vertices: "
         << reachable << endl;

    cout << "Total path vertices stored: "
         << totalPathVertices << endl;

    cout << "Time: "
         << time << " microseconds" << endl;

    paths.clear();
    paths.shrink_to_fit();
}


int main()
{
    cout << "Loading roadNet-PA.txt..." << endl;

    int V = 0;
    int officialNodes = 0;

    Graph originalGraph;
    Graph reverseGraph;

    Graph graph =
        loadRoadNetwork(
            "roadNet-PA.txt",
            V,
            officialNodes,
            originalGraph,
            reverseGraph
        );

    cout << "Graph loaded." << endl;

    cout << "Official dataset vertices: "
         << officialNodes << endl;

    cout << "Internal vertex array size: "
         << V << endl;

    cout << "Criterion 1 edges: "
         << graph.size() << endl;

    cout << "Criterion 2 edges: "
         << originalGraph.size() << endl;

    cout << "Criterion 3 edges: "
         << reverseGraph.size() << endl;


    // --------------------------------------------------------
    // Main assignment results
    //
    // All three required functions use Criterion 1 because
    // the selected graph type is UNDIRECTED.
    // --------------------------------------------------------

    cout << "\n========================================" << endl;
    cout << "MAIN ASSIGNMENT RESULTS" << endl;
    cout << "Using Criterion 1: UNDIRECTED" << endl;
    cout << "========================================" << endl;

    runConnectedComponents(graph, V);

    cout << "\nRunning cycle detection..." << endl;

    auto start = chrono::high_resolution_clock::now();

    vector<int> cycle = oneCycle(V, graph);

    auto end = chrono::high_resolution_clock::now();

    long long cycleTime =
        chrono::duration_cast<chrono::microseconds>
        (end - start).count();

    if (cycle.empty())
        cout << "No cycle found." << endl;
    else
        cout << "Cycle found. Cycle vertices: "
             << cycle.size() << endl;

    cout << "Cycle detection time: "
         << cycleTime << " microseconds" << endl;

    cycle.clear();
    cycle.shrink_to_fit();


    cout << "\nRunning shortest paths from source 0..." << endl;

    start = chrono::high_resolution_clock::now();

    vector<vector<int>> paths =
        shortestPaths(graph, V, 0);

    end = chrono::high_resolution_clock::now();

    long long shortestTime =
        chrono::duration_cast<chrono::microseconds>
        (end - start).count();

    long long reachable = 0;
    long long totalPathVertices = 0;

    for (const auto& path : paths)
    {
        if (!path.empty())
        {
            reachable++;
            totalPathVertices += path.size();
        }
    }

    cout << "Reachable vertices: "
         << reachable << endl;

    cout << "Total path vertices stored: "
         << totalPathVertices << endl;

    cout << "Shortest paths time: "
         << shortestTime << " microseconds" << endl;


    // --------------------------------------------------------
    // Bonus adjacency-criteria tests
    // --------------------------------------------------------

    cout << "\n========================================" << endl;
    cout << "BONUS ADJACENCY CRITERIA TESTS" << endl;
    cout << "========================================" << endl;

    // Criterion 1 was already tested above with connectedComponents().
    // Criterion 2 is tested with oneCycle().
    // Criterion 3 is tested with shortestPaths().

    runCycle(originalGraph, V);

    runShortestPaths(reverseGraph, V);


    // --------------------------------------------------------
    // Save main assignment results
    // --------------------------------------------------------

    ofstream output("real_results.txt");

    output << "REAL-LIFE GRAPH BONUS RESULTS\n";
    output << "==============================\n\n";

    output << "Dataset: roadNet-PA.txt\n";
    output << "Graph: Pennsylvania road network\n\n";

    output << "Official dataset vertices: "
           << officialNodes << "\n";

    output << "Internal vertex array size: "
           << V << "\n";

    output << "Undirected edges: "
           << graph.size() << "\n\n";

    output << "Main assignment graph:\n";
    output << "Adjacency criterion: Criterion 1 - UNDIRECTED\n\n";

    output << "Connected components:\n";
    output << "Time was measured during the run above.\n\n";

    output << "Cycle detection:\n";
    output << "Time: "
           << cycleTime << " microseconds\n\n";

    output << "Shortest paths:\n";
    output << "Source: 0\n";
    output << "Reachable vertices: "
           << reachable << "\n";

    output << "Total path vertices stored: "
           << totalPathVertices << "\n";

    output << "Time: "
           << shortestTime << " microseconds\n\n";

    output << "Adjacency criteria tested:\n";
    output << "Criterion 1 - Undirected adjacency: connectedComponents()\n";
    output << "Criterion 2 - Original input adjacency: oneCycle()\n";
    output << "Criterion 3 - Reverse adjacency: shortestPaths()\n";

    output.close();

    cout << "\nResults saved to real_results.txt" << endl;

    return 0;
}