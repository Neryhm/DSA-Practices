#include <iostream>
#include <vector>
#include <list>

class Graph {
private:
    int V; // số đỉnh
    std::vector<std::list<int>> adj; // adjacency list
    
public:
    Graph(int vertices) : V(vertices), adj(vertices) {}
    
    // Thêm cạnh từ u đến v (hướng hoặc vô hướng tùy yêu cầu)
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        
        // Nếu là đồ thị vô hướng, thêm:
        // adj[v].push_back(u);
    }
    
    // Xóa cạnh từ u đến v
    void removeEdge(int u, int v) {
        adj[u].remove(v);
        // Nếu vô hướng, cũng xóa adj[v].remove(u);
    }
    
    // Duyệt BFS từ đỉnh start
    void BFS(int start) {
        std::vector<bool> visited(V, false);
        std::list<int> queue;
        
        visited[start] = true;
        queue.push_back(start);
        
        while(!queue.empty()) {
            int u = queue.front();
            queue.pop_front();
            std::cout << u << " ";
            
            for (int neighbor : adj[u]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push_back(neighbor);
                }
            }
        }
        std::cout << std::endl;
    }
    
    // Duyệt DFS (đệ quy)
    void DFSUtil(int u, std::vector<bool>& visited) {
        visited[u] = true;
        std::cout << u << " ";
        
        for (int neighbor : adj[u]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }
    
    void DFS(int start) {
        std::vector<bool> visited(V, false);
        DFSUtil(start, visited);
        std::cout << std::endl;
    }
};
