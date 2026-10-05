#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<int>>;


// Functions from graph_operations.cpp

vector<vector<int>> connectedComponents(
    const Graph& graph,
    int V
);

vector<int> oneCycle(
    int V,
    const Graph& graph
);

vector<vector<int>> shortestPaths(
    const Graph& graph,
    int V,
    int source
);


// Functions from graph_simulator.cpp

Graph makeCycle(int n);
Graph makeComplete(int n);
Graph makeEmpty(int n);
Graph makeHeap(int n);


// --------------------------------------------------
// Test one graph
// --------------------------------------------------

void testGraph(
    string name,
    Graph graph,
    int n)
{
    cout << "\n==============================" << endl;
    cout << name << endl;
    cout << "Vertices: " << n << endl;
    cout << "Edges: " << graph.size() << endl;
    cout << "==============================" << endl;


    // Connected Components

    auto start =
        chrono::high_resolution_clock::now();

    vector<vector<int>> components =
        connectedComponents(graph, n);

    auto end =
        chrono::high_resolution_clock::now();

    long long ccTime =
        chrono::duration_cast<
            chrono::microseconds
        >(end - start).count();


    // Cycle Detection

    start =
        chrono::high_resolution_clock::now();

    vector<int> cycle =
        oneCycle(n, graph);

    end =
        chrono::high_resolution_clock::now();

    long long cycleTime =
        chrono::duration_cast<
            chrono::microseconds
        >(end - start).count();


    // Shortest Paths

    start =
        chrono::high_resolution_clock::now();

    vector<vector<int>> paths =
        shortestPaths(graph, n, 0);

    end =
        chrono::high_resolution_clock::now();

    long long shortestTime =
        chrono::duration_cast<
            chrono::microseconds
        >(end - start).count();


    // Print results

    cout << "Number of components: "
         << components.size() << endl;

    cout << "Connected components time: "
         << ccTime
         << " microseconds" << endl;

    cout << "Cycle detection time: "
         << cycleTime
         << " microseconds" << endl;

    cout << "Shortest paths time: "
         << shortestTime
         << " microseconds" << endl;


    // Small graph: print cycle

    if (n <= 10)
    {
        if (cycle.empty())
        {
            cout << "Cycle: none" << endl;
        }
        else
        {
            cout << "Cycle: ";

            for (int vertex : cycle)
                cout << vertex << " ";

            cout << endl;
        }
    }


    // Small graph: print paths

    if (n <= 10)
    {
        cout << "Paths from source 0:" << endl;

        for (int i = 0; i < n; i++)
        {
            if (paths[i].empty())
                continue;

            cout << i << ": ";

            for (int vertex : paths[i])
                cout << vertex << " ";

            cout << endl;
        }
    }


    // Save CPU results

    ofstream results(
        "results.txt",
        ios::app
    );

    results << "\n--------------------------------" << endl;
    results << name << endl;
    results << "Vertices: " << n << endl;
    results << "Edges: " << graph.size() << endl;

    results << "Number of components: "
            << components.size() << endl;

    results << "Connected components time: "
            << ccTime
            << " microseconds" << endl;

    results << "Cycle detection time: "
            << cycleTime
            << " microseconds" << endl;

    results << "Shortest paths time: "
            << shortestTime
            << " microseconds" << endl;

    results.close();
}


// --------------------------------------------------
// Main
// --------------------------------------------------

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage: ./graph_test <graph_type> <number_of_vertices>"
             << endl;

        cout << endl;

        cout << "Graph types:" << endl;
        cout << "  cycle" << endl;
        cout << "  complete" << endl;
        cout << "  empty" << endl;
        cout << "  heap" << endl;

        return 1;
    }


    string type = argv[1];

    int n;

    try
    {
        n = stoi(argv[2]);
    }
    catch (...)
    {
        cout << "Invalid number of vertices." << endl;
        return 1;
    }


    if (n <= 0)
    {
        cout << "Number of vertices must be greater than 0."
             << endl;

        return 1;
    }


    // Run ONLY the requested experiment

    if (type == "cycle")
    {
        testGraph(
            "Cycle " + to_string(n),
            makeCycle(n),
            n
        );
    }
    else if (type == "complete")
    {
        testGraph(
            "Complete " + to_string(n),
            makeComplete(n),
            n
        );
    }
    else if (type == "empty")
    {
        testGraph(
            "Empty " + to_string(n),
            makeEmpty(n),
            n
        );
    }
    else if (type == "heap")
    {
        testGraph(
            "Heap " + to_string(n),
            makeHeap(n),
            n
        );
    }
    else
    {
        cout << "Unknown graph type." << endl;
        return 1;
    }


    return 0;
}