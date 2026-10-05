# Graph Algorithms Assignment

## 1. Introduction

For this project, I implemented and tested three graph algorithms in C++:

* Connected Components using DFS
* Cycle Detection using DFS
* Shortest Paths using Dijkstra's algorithm

I used an **undirected graph** for this assignment. The graph is stored using basic C++ data structures such as `vector`, and I did not use a graph library.

I tested the algorithms on several simulated graphs with different structures and sizes. I also tested them on a real-world Pennsylvania road network as part of the optional bonus.

## 2. Files

* `graph_operations.cpp` - contains the main graph algorithms
* `graph_simulator.cpp` - creates the simulated graphs
* `simulated_test.cpp` - runs the simulated experiments
* `run_all_tests.sh` - compiles and runs all simulated tests
* `results.txt` - contains the simulated test results
* `realgraph_make.cpp` - loads and tests the real-world graph
* `run_realgraph_make.sh` - runs the real-world bonus test
* `real_results.txt` - contains the real-world results
* `README.md` - project information and instructions

## 3. Graph Representation

The graph is undirected and uses basic C++ vectors to store the graph.

For the real-world road network, the input file contains both directions of each road. For the main assignment graph, I keep only the edge where `u < v`. This removes the duplicate copy of the same road.

The node IDs in the real dataset are not completely continuous. Because of this, the program reports both the official number of vertices in the dataset and the internal vector size used by the program.

## 4. Algorithms

### Connected Components

`connectedComponents()` uses DFS to visit the graph and find all of its connected components.

### Cycle Detection

`oneCycle()` uses DFS to find a cycle. I used an explicit stack instead of recursive DFS. This helps avoid a recursion stack overflow when running the program on the large real-world graph.

### Shortest Paths

`shortestPaths()` uses Dijkstra's algorithm. Since the simulated graphs and the road network are unweighted, each edge is given a weight of 1.

The function stores the complete shortest path for every reachable vertex.

## 5. Simulated Graphs

I tested four different graph types:

1. **Cycle** - the vertices are connected together to form a cycle.
2. **Complete** - every pair of vertices has an edge.
3. **Empty** - there are vertices but no edges.
4. **Heap** - the vertices are connected in a heap/tree-like structure.

Each graph type was tested with different numbers of vertices.

### Running the simulated tests

First, make the script executable:

```bash
chmod +x run_all_tests.sh
```

Then run:

```bash
./run_all_tests.sh
```

This compiles the C++ files and runs all of the simulated experiments. It also measures the process-level memory and CPU information. The results are saved in `results.txt`.

One experiment can also be run manually:

```bash
g++ -std=c++17 graph_operations.cpp graph_simulator.cpp simulated_test.cpp -o graph_test

./graph_test cycle 1000
```

The first argument can be `cycle`, `complete`, `empty`, or `heap`.

## 6. Real-World Graph Bonus

For the bonus experiment, I used the Pennsylvania road network dataset `roadNet-PA.txt` from the Stanford Network Analysis Project (SNAP).

Dataset page:

[SNAP RoadNet-PA dataset page](https://snap.stanford.edu/data/roadNet-PA.html?utm_source=chatgpt.com)

The dataset represents a real road network from Pennsylvania. The official dataset contains 1,088,092 vertices and 1,541,898 undirected edges.

### Running the bonus experiment

Place `roadNet-PA.txt` in the same folder as the C++ files.

Then run:

```bash
chmod +x run_realgraph_make.sh

./run_realgraph_make.sh
```

The script compiles `realgraph_make.cpp` with `graph_operations.cpp`, runs the real-world experiment, and records the CPU and peak memory information.

The results are saved in:

```text
real_results.txt
```

It can also be run manually:

```bash
g++ -std=c++17 realgraph_make.cpp graph_operations.cpp -o realgraph_make

./realgraph_make
```

## 7. Adjacency Criteria Bonus

I also tested three different ways of building the adjacency information.

### Criterion 1 - Undirected adjacency

For the main assignment graph, I keep only `u < v`. This removes the duplicate direction from the road dataset.

This criterion was tested with `connectedComponents()` and was also used for the main cycle and shortest-path tests.

### Criterion 2 - Original input adjacency

For this version, I kept every `(u,v)` pair exactly as it appears in the input file.

This criterion was tested with `oneCycle()`.

### Criterion 3 - Reverse adjacency

For this version, each input pair is reversed from `(u,v)` to `(v,u)`.

This criterion was tested with `shortestPaths()`.

The RoadNet-PA file contains 3,083,796 input edge pairs, while the undirected representation contains 1,541,898 physical edges.

## 8. Final Simulated Results

The final simulated run contained 12 experiments.

| Graph    | Vertices |   Edges | CC (µs) | Cycle (µs) | Shortest Paths (µs) | Peak Memory (KB) |
| -------- | -------: | ------: | ------: | ---------: | ------------------: | ---------------: |
| Cycle    |    1,000 |   1,000 |     403 |        473 |               5,635 |            5,248 |
| Cycle    |    5,000 |   5,000 |   1,791 |      1,960 |              87,096 |           38,272 |
| Cycle    |   10,000 |  10,000 |   4,440 |      5,348 |             340,363 |          128,220 |
| Complete |      100 |   4,950 |     412 |        299 |                 867 |            4,224 |
| Complete |      500 | 124,750 |   8,488 |      4,931 |              18,630 |           12,360 |
| Complete |    1,000 | 499,500 |  32,796 |     20,322 |              62,321 |           38,856 |
| Empty    |    1,000 |       0 |     829 |         98 |                  49 |            3,968 |
| Empty    |    5,000 |       0 |   4,106 |        468 |                 216 |            4,352 |
| Empty    |   10,000 |       0 |   8,873 |      1,062 |                 466 |            4,412 |
| Heap     |    1,000 |     999 |     467 |        409 |               1,798 |            3,840 |
| Heap     |    5,000 |   4,999 |   2,216 |      1,834 |               8,062 |            4,480 |
| Heap     |   10,000 |   9,999 |   4,582 |      4,693 |              19,340 |            5,428 |

From the tests, I noticed that the complete graphs used more memory as the number of edges increased. The cycle graph also showed a large increase in shortest-path time as the number of vertices increased. The empty graph used very little memory because it did not have any edges.

## 9. Final Real-World Results

The final RoadNet-PA run completed successfully.

* Official dataset vertices: **1,088,092**
* Internal vertex array size: **1,090,920**
* Undirected edges: **1,541,898**
* Connected components: **3,034**
* Connected components time: **556,915 microseconds**
* Cycle found: **Yes**
* Cycle size: **4 vertices**
* Cycle detection time: **484,412 microseconds**
* Source: **0**
* Reachable vertices: **1,087,562**
* Total path vertices stored: **311,821,786**
* Shortest paths time: **7,240,154 microseconds**

### Adjacency criteria results

* Criterion 1: `connectedComponents()` - **556,915 microseconds**
* Criterion 2: `oneCycle()` - cycle of 4 vertices, **730,824 microseconds**
* Criterion 3: `shortestPaths()` - 1,087,562 reachable vertices, **7,578,200 microseconds**

Process-level measurements for the complete bonus run:

* Peak memory: **3,959,552 KB**
* User CPU time: **18.26 seconds**
* System CPU time: **1.83 seconds**
* Total elapsed time: **20.10 seconds**

## 10. Observations

The simulated tests showed that the graph structure and the number of edges affected both runtime and memory.

The complete graphs became expensive quickly because the number of edges grows very fast. The empty graphs were much cheaper because there were no edges to process. The cycle and heap graphs had fewer edges, so their memory usage was much lower than the complete graphs.

The real-world graph was much larger than the simulated graphs, so it needed much more memory. The shortest-path function used a large amount of memory because it stores the full path for every reachable vertex. Even with the large graph, the real-world experiment completed successfully.

For the large graph, I used an explicit DFS stack for cycle detection instead of recursive DFS. This was important because recursion can run out of stack space when working with a graph containing more than one million vertices.

## 11. Submission

The recommended submission folder contains:

```text
graph_operations.cpp
graph_simulator.cpp
simulated_test.cpp
run_all_tests.sh
results.txt
realgraph_make.cpp
run_realgraph_make.sh
real_results.txt
README.md
```

The `roadNet-PA.txt` dataset should only be included if the submission system allows the dataset file. Otherwise, the dataset name and source are included in this README.

The ZIP file should follow the required naming format:

```text
Lastname Firstname assignment1.zip
```

## 12. Quick Run Summary

For the normal assignment tests:

```bash
chmod +x run_all_tests.sh

./run_all_tests.sh
```

For the real-world bonus:

```bash
chmod +x run_realgraph_make.sh

./run_realgraph_make.sh
```

Both scripts compile the required C++ programs and save the results in their corresponding result files.
