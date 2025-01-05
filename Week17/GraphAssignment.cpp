#include<iostream>

enum Node {
    A = 0,
    B,
    C,
    D,
    E,
    G,
    H
};

static const char* nodeNames[7] = { "A", "B", "C", "D", "E", "G", "H" };

struct Graph {
    // Adjacency matrix: matrix[i][j] is true if there's an edge from i to j
    bool matrix[7][7];

    // Constructor initializes the matrix with false (no edges)
    Graph() {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                matrix[i][j] = false;
            }
        }
    }

    // Add a directed edge from 'from' to 'to'
    void addEdge(Node from, Node to) {
        matrix[from][to] = true;
    }

    // Check if there's a directed edge from 'from' to 'to'
    bool isEdge(Node from, Node to) const {
        return matrix[from][to];
    }

    // Print the adjacency matrix
    void print() const {
        std::cout << "Adjacency Matrix:\n";
        std::cout << "    A B C D E G H\n";
        for (int i = 0; i < 7; i++) {
            std::cout << nodeNames[i] << " : ";
            for (int j = 0; j < 7; j++) {
                std::cout << (matrix[i][j] ? 1 : 0) << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void bfs(Node start) const {
        bool visited[7];
        for (int i = 0; i < 7; i++) {
            visited[i] = false;
        }

        // Simple array-based queue
        Node queue[7];
        int front = 0, rear = 0;

        // Mark the start node as visited and enqueue it
        visited[start] = true;
        queue[rear++] = start;

        std::cout << "BFS order starting from node " << nodeNames[start] << ": ";

        // Standard BFS loop
        while (front < rear) {
            // Dequeue
            Node current = queue[front++];
            std::cout << nodeNames[current] << " ";

            // Visit all adjacent nodes
            for (int j = 0; j < 7; j++) {
                if (matrix[current][j] && !visited[j]) {
                    visited[j] = true;
                    queue[rear++] = static_cast<Node>(j);
                }
            }
        }
        std::cout << std::endl;
    }

    // DFS traversal from a given start node (recursive)
    void dfs(Node start) const {
        bool visited[7];
        for (int i = 0; i < 7; i++) {
            visited[i] = false;
        }
        std::cout << "DFS order starting from node " << nodeNames[start] << ": ";
        dfsUtil(start, visited);
        std::cout << std::endl;
    }

private:
    // Recursive helper for DFS
    void dfsUtil(Node current, bool visited[]) const {
        visited[current] = true;
        std::cout << nodeNames[current] << " ";

        // Visit all unvisited adjacent nodes
        for (int j = 0; j < 7; j++) {
            if (matrix[current][j] && !visited[j]) {
                dfsUtil(static_cast<Node>(j), visited);
            }
        }
    }
};

int main() {
    Graph g;
    
    // Example of adding a few directed edges
    g.addEdge(A, B);
    g.addEdge(A, D);
    g.addEdge(A, E);
    g.addEdge(A, H);
    g.addEdge(B, C);
    g.addEdge(B, D);
    g.addEdge(B, G);
    g.addEdge(C, B);
    g.addEdge(C, D);
    g.addEdge(C, H);
    g.addEdge(D, A);
    g.addEdge(D, C);
    g.addEdge(D, G);
    g.addEdge(D, H);
    g.addEdge(E, B);
    g.addEdge(E, D);
    g.addEdge(E, G);
    g.addEdge(G, A);
    g.addEdge(G, B);
    g.addEdge(G, E);
    g.addEdge(G, H);
    
    // Print out the adjacency matrix
    g.print();
    
    // Check if certain edges exist
    std::cout << "\nEdge from A to B? " << (g.isEdge(A, B) ? "Yes" : "No") << "\n";
    std::cout << "Edge from B to A? " << (g.isEdge(B, A) ? "Yes" : "No") << "\n";

    // BFS and DFS
    g.bfs(A);
    g.dfs(A);

    return 0;   
}