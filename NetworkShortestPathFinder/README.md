# Network Packet Routing System

This project is an implementation of a **Network Packet Routing System** using **C language**.  
It demonstrates the application of **Dijkstra’s Algorithm** and **Breadth First Search (BFS)** for computing the **shortest path** between two routers in a network graph.

The project reads router data from an input file (`routers.txt`), constructs the graph using an **Adjacency Matrix**, and allows the user to compute the shortest path between a source and destination router. The results (path and cost/latency) are calculated using both algorithms and stored in an output file.

---

## Features
- Reads graph data (routers and latencies) from a file.
- Represents the graph using an **Adjacency Matrix**.
- Implements:
  - **Dijkstra’s Algorithm** (using a **Min Heap** for efficiency).
  - **Breadth First Search (BFS)** (using a **Queue**).
- Allows the user to:
  1. Load routers from file and construct the graph.
  2. Enter a source router.
  3. Enter a destination router.
  4. Compute and display the **shortest path** and **total latency** using both algorithms.
  5. Save the results to a file (`shortest_distance.txt`).

---

## File Format
The input file `routers.txt` must contain edges in the format:  

```
From-To-Latency
```

Example (`routers.txt`):
```
A-B-10
A-C-15
B-D-12
B-E-15
B-F-30
C-E-10
D-E-2
D-F-1
E-F-5
```

---

## Example Run

**Input:**  
Source = `A`  
Destination = `F`  

**Output:**  
```
Shortest path from A to F is:

Dijkstra: A -> B -> D -> F with a total cost of 23.
BFS: A -> B -> F with a total cost of 40.
```

The program also writes this information into `shortest_distance.txt`.

---

## Data Structures Used
- **Adjacency Matrix** → for graph representation.  
- **Queue** → for BFS implementation.  
- **Min Heap** → for efficient Dijkstra’s Algorithm implementation.  

---

## Compilation & Execution
### Compile:
```bash
gcc -o routing routing.c
```

### Run:
```bash
./routing
```

---

## Menu Options
1. **Load routers**: Loads the file and constructs the graph.  
2. **Enter source**: Specify the starting router.  
3. **Enter destination**: Specify the target router and compute the shortest paths.  
4. **Exit**: Saves the result into `shortest_distance.txt` and exits.  

---

## Output File
The file `shortest_distance.txt` contains the computed paths and costs from both algorithms.  

Example:
```
Shortest path from A to F is:
Dijkstra: A -> B -> D -> F with a total cost of 23.
BFS: A -> B -> F with a total cost of 40.
```

---