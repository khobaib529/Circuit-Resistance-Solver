# Resistance Network Solver
When solving a network of resistors using a programming language, the first step is to select an appropriate data structure to represent the network. This process begins with understanding the network and its resistances. Visualizing the circuit diagram can greatly aid in comprehending the connections between resistors and other elements.

Once the circuit is well-understood, the next consideration is how to effectively model this network in code. Choosing the right data structure is crucial for accurately representing the resistive network. Common approaches include using graphs or matrices, depending on the complexity of the network.

Before diving into the implementation, it’s important to reflect on the data structure that will best suit the representation of the resistor network. This careful planning will facilitate a more efficient and effective solution to calculating the total resistance of the circuit, much like you would do manually using Ohm’s Law.

## Intuition
In this solution, the network of resistors is represented as a directed graph, where each node corresponds to a junction and the edges represent resistors. The direction of the edges indicates the flow of current. The weight of each edge stores the value of the resistor it represents.

To efficiently handle this structure in C++, an array of `multiset` is used to represent the graph. The choice of `multiset` allows for automatic sorting of elements, making computations for parallel connections more efficient by reducing time complexity.

Consider the circuit shown below.

![Circuit Diagram](images/circuit_diagram.svg)

To help clarify the relationships within the network, I have provided a visual representation as a network graph. This graph demonstrates how nodes are interconnected and how these connections relate to each other. The direction of the edges in the graph indicates the flow of electricity. I assume there are V nodes, numbered from 0 to V — 1, with the current flowing from node 0 (high voltage) to node V — 1 (low voltage).

![Network Graph](images/network_graph.png)



To address the problem of solving a network of resistors, an important question arises: which traversal method should be employed? Take a moment to consider this before continuing. If you find a potential solution, try solving it independently. If you’re unable to arrive at a solution on your own, you can scroll down for some guidance.

The intuition behind solving the network is straightforward. Following Ohm’s Law, we can solve it as we would on paper. For resistors connected in series, the total resistance R’ is the sum of the individual resistances:

**1 / R' = 1 / R1 + 1/ R2 + ... + 1 / Rn.**

For resistors connected in parallel, the total resistance R’ is given by:
So, **R' = 1 / (1 / R1 + 1 / R2 + ... + 1 / Rn)**

Here’s a step-by-step illustration of how to solve it manually.


![Step 1](images/illustration1.png)


**Step-1:** Between nodes 4 and 6, there are series connections. We simply add the resistances between 4 and 5, and 5 and 6, resulting in a total resistance of 20 ohms (10 + 10).

<br/><br/>

![Step 2](images/illustration2.png)

**Step-2:** In the previous step, we identified a parallel connection between nodes 4 and 6. In this step, we calculate the total resistance between nodes 4 and 6 using the parallel connection formula.
<br/><br/>

![Step 3](images/illustration3.png)



**Step-3:** In this step, we apply the same process as in the first step, but now for nodes 4, 6, and 7.
<br/><br/>

![Step 4](images/illustration4.png)



**Step-4**: In this step, we use the same approach as in the second step, but now for nodes 4 and 7.
<br/><br/>

![Step 5](images/illustration5.png)


**Step-5:** Between nodes 3, 4 and 7, there are series connections. In this step, we perform a series addition for nodes 3, 4, and 7.
<br/><br/>


![Step 6](images/illustration6.png)


**Step-6:** Similar to step 2, we perform a parallel addition between nodes 3 and 7.
<br/><br/>


![Step 7](images/illustration7.png)


**Step-7:** Similar to step 1, we have a series connection between nodes 3, 7, and 8. We simply calculate the total resistance by adding them together.
<br/><br/>


![Step 8](images/illustration8.png)


**Step-8:** Similar to step 2, we have a parallel connection between nodes 3 and 8. We calculate the total resistance using the parallel connection formula.
<br/><br/>

![Step 9](images/illustration11.png)


**Step-9:** Similar to step 1, we have a series connection between nodes 0, 1, 2, 3 and 8. We calculate the total resistance by summing them up.
<br/><br/>

Yes, in this step, the current flows directly from the low voltage to the high voltage. The resistance between junctions 0 and 8 is 20 ohm, as we consistently apply Ohm’s law throughout the process.

In the previous steps, we demonstrated how to logically solve the resistance of a network using pen and paper. This logical approach can be implemented in any programming language to create an algorithm for solving network resistances.

If you understand how to solve it, try implementing it yourself in any programming language you’re familiar with.

In my approach, I use Depth First Search (DFS) on the graph and perform two main actions based on specific conditions:

**1. Node Simplification:** During DFS traversal, I check if each adjacent node of the current node has an in-degree and out-degree of 1. When this condition is met, indicating a series connection, I simplify the graph by removing the adjacent node and directly connecting the current node to the node that the adjacent node was originally connected to.

*Why do this?* The logic is straightforward: When a node has both an in-degree and out-degree of 1, it effectively acts as a connector between two other nodes. In such cases, we can combine the resistances of the adjacent node’s neighboring nodes and remove the adjacent node from the graph. This is similar to how we simplify circuits on paper. If you’re still unsure, try working through more examples to understand this better.

**2. Handling Non-Simplifiable Nodes:** If the adjacent node does not have an in-degree and out-degree of 1, the next step is to call DFS recursively for that adjacent node. This ensures that we explore all possible simplifications in the graph.

*When to Calculate Total Resistance:* You might wonder whether we should calculate the total resistance of parallel connections after completing all operations on a node or before returning from a DFS call. It’s generally best to calculate the total resistance of parallel connections after processing all operations for a node, before moving on to the next DFS call. This ensures that all possible simplifications have been made before computing the resistance.

## Algorithm Explanation:

I’ve implemented this algorithm in C++, but it can be adapted to any programming language.

### Main Components:

1. **needs_resistance_adjustment**: This function checks if a node in the network needs resistance adjustment, which happens if it has only one incoming and outgoing connection.

2. **adjust_parallel_connections**: This function adjusts parallel connections in the network. It iterates over each node and its adjacent nodes to identify parallel connections. If parallel connections are found, it adjusts them by calculating the equivalent resistance.

3. **dfs**: This function performs a Depth-First Search (DFS) traversal of the network. It recursively traverses each node and its adjacent nodes to perform resistance adjustments using the above functions.

4. **calculate_indegree**: This function calculates the indegree of each node in the network, which represents the number of incoming connections to each node.

5. **calculate_total_resistence**: This function calculates the total resistance of the network by repeatedly calling the DFS function until the last node is reached.

### Steps:

1. Initialize a multiset of pairs to represent the adjacency list of the network.

2. Populate the adjacency list with node-resistance pairs according to the network connections.

3. Calculate the indegree of each node in the network.

4. Repeat DFS traversal until the last node is reached, adjusting resistances as needed.

5. Return the total resistance of the network.

## Usage

1. Compile the C++ program.
2. Run the executable.
3. The program will output the total resistance of the network.
4. You can check the program for different types of circuit.

If you find any issues with this program you can give a pull request.
