# Circuit Resistance Solver

This project implements a graph-based algorithm in C++ for calculating the total resistance of a circuit represented as a directed graph. The algorithm's approach is discussed in detail in this [Medium article](https://medium.com/@khobaib529/solving-electrical-circuits-a-graph-based-algorithm-for-resistance-calculations-921575c59946)

## Build and Run

To build and run the Circuit Resistance Solver, follow these steps:

```bash
# Clone the repository
git clone https://github.com/khobaib529/Circuit-Resistance-Solver.git

# Navigate to the project directory
cd Circuit-Resistance-Solver

# Compile the code
g++ -o main src/main.cpp -std=c++11

# Run the executable
./main
```

## Circuit Class

The `Circuit` class represents an electrical circuit with nodes and resistances. It provides functionality to connect nodes, perform depth-first search (DFS), and calculate the total resistance of the circuit by handling series and parallel connections.

### Functions

- **Circuit(int V)**
  - **Description**: Constructor that initializes a circuit with `V` vertices.
  - **Parameters**:
    - `V` - The number of nodes in the circuit.

- **void connect(int u, int v, double resistance)**
  - **Description**: Connects two nodes (`u` and `v`) with a given resistance.
  - **Parameters**:
    - `u` - The source node.
    - `v` - The target node.
    - `resistance` - The resistance value between the nodes.

- **double calculate_total_resistence()**
  - **Description**: Calculates the total resistance of the circuit using depth-first search and adjustments for series and parallel connections.
  - **Returns**: The total resistance of the circuit.
  - **Throws**: `std::runtime_error` if the total resistance cannot be calculated.

### Private Methods

- **void dfs(int node)**
  - **Description**: Depth-first search function to traverse the circuit and adjust resistances for series and parallel connections.

- **void adjust_parallel_connections(int node)**
  - **Description**: Adjusts the parallel connections at a given node by recalculating resistances for parallel branches.

- **bool is_series_connection(int node)**
  - **Description**: Checks if a node has a series connection by examining its degree.
