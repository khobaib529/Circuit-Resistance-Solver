/*
 * circuit.h
 *
 * This header file defines the Circuit class, which represents an electrical circuit
 * with nodes and resistances. It provides functionality to connect nodes and calculate
 * the total resistance of the circuit using depth-first search and resistance adjustments
 * for series and parallel connections.
 *
 */

#ifndef CIRCUIT_H_
#define CIRCUIT_H_

#include <set>
#include <stdexcept>
#include <vector>

class Circuit {
 private:
  // Check if a node has a series connection
  bool is_series_connection(int node) {
    return adj_ls[node].size() == 1 && indegree[node] == 1;
  }

  // Adjust parallel connections for a given node
  void adjust_parallel_connections(int node) {
    std::multiset<std::pair<int, double>>::iterator it = adj_ls[node].begin();

    // Iterate through the connections
    while (it != adj_ls[node].end()) {
      std::multiset<std::pair<int, double>>::iterator start = it;
      std::multiset<std::pair<int, double>>::iterator end =
          ++std::multiset<std::pair<int, double>>::iterator(it);

      double reciprocal_sum = 0;  // Sum of reciprocals of resistances
      bool flag = false;          // Flag to indicate if adjustments were made

      // Loop through parallel connections
      while (end != adj_ls[node].end() && it->first == end->first) {
        reciprocal_sum += (1.0 / end->second);  // Calculate reciprocal
        end = adj_ls[node].erase(end);          // Remove the edge
        --indegree[it->first];                  // Decrement indegree
        --edge_cnt;                             // Decrement edge count
        flag = true;                            // Set flag
      }

      // If adjustments were made, update the resistance
      if (flag == true) {
        reciprocal_sum += (1.0 / start->second);
        adj_ls[node].erase(start);
        adj_ls[node].insert(std::make_pair(start->first, 1.0 / reciprocal_sum));
      }

      it = end;  // Move to the next connection
    }
  }

  // Depth-first search to adjust resistances
  void dfs(int node) {
    int prev_edge_cnt = edge_cnt;  // Store the previous edge count
    for (const std::pair<int, double>& it : adj_ls[node]) {
      int adj_node = it.first;        // Get adjacent node
      double resistance = it.second;  // Get resistance

      // Checking for resistance adjustment in series connection
      if (is_series_connection(adj_node)) {
        double new_resistence = resistance + adj_ls[adj_node].begin()->second;
        int node_to_connect = adj_ls[adj_node].begin()->first;

        // Clear the connections of the adjacent node
        adj_ls[adj_node].clear();
        --indegree[adj_node];
        --edge_cnt;

        // Update the current node's connection
        adj_ls[node].erase(std::make_pair(adj_node, resistance));
        adj_ls[node].insert(std::make_pair(node_to_connect, new_resistence));
      } else {
        dfs(adj_node);  // Continue DFS if not a series connection
      }
    }
    adjust_parallel_connections(node);  // Adjust parallel connections

    // If edge count was reduced, continue DFS
    if (edge_cnt < prev_edge_cnt) {
      dfs(node);
    }
  }

 public:
  // Constructor to initialize the circuit with V vertices
  Circuit(int V) : adj_ls(V), V(V), indegree(V, 0), edge_cnt(0) {}

  // Connect two nodes with a given resistance
  void connect(int u, int v, double resistance) {
    ++indegree[v];                      // Increment indegree of the target node
    ++edge_cnt;                         // Increment edge count
    adj_ls[u].insert({v, resistance});  // Add the connection
  }

  // Calculate the total resistance of the circuit
  double calculate_total_resistence() {
    dfs(0);  // Start DFS from node 0
    // Ensure there is only one edge left in the circuit
    if (edge_cnt != 1) {
      throw std::runtime_error(
          "Unable to calculate the total resistance of the circuit.");
    }
    return adj_ls[0].begin()->second;  // Return the total resistance
  }

 private:
  int V;  // Number of vertices
  std::vector<std::multiset<std::pair<int, double>>> adj_ls;  // Adjacency list
  int edge_cnt;                                               // Count of edges
  std::vector<int> indegree;  // Indegree of each node
};

#endif  // CIRCUIT_H_
