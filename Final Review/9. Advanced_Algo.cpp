#include <iostream>
using namespace std;\

// Floyd - Warshall
static const int INF = 99999; // Giá trị đại diện cho vô cực

void floydWarshall(int dist[][4], int V) {
    // dist[i][j] là ma trận khoảng cách ban đầu
    // Sao chép ma trận nếu cần (ở đây mình dùng trực tiếp dist)
    
    // Thuật toán Floyd-Warshall
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

// MST (Minimum Spanning Tree) - Kruskal
// --------------------------------------
// Khai báo hằng số (giới hạn tối đa)
// --------------------------------------
const int MAX_V = 100;    // Số đỉnh tối đa
const int MAX_E = 100;    // Số cạnh tối đa

// --------------------------------------
// Cấu trúc lưu cạnh (Edge)
// --------------------------------------
struct Edge {
    int src;       // đỉnh đầu
    int dest;      // đỉnh cuối
    int weight;    // trọng số
};

// --------------------------------------
// Selection Sort để sắp xếp các cạnh 
// theo trọng số tăng dần
// --------------------------------------
void sortEdges(Edge edges[], int E) {
    for (int i = 0; i < E - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < E; j++) {
            if (edges[j].weight < edges[minIndex].weight) {
                minIndex = j;
            }
        }
        // Hoán đổi
        if (minIndex != i) {
            Edge temp = edges[i];
            edges[i] = edges[minIndex];
            edges[minIndex] = temp;
        }
    }
}

// --------------------------------------
// Disjoint Set (Union-Find)
// --------------------------------------
int parent[MAX_V];
int rankSet[MAX_V];  // "rank" để tối ưu

// Tìm gốc (tập) của phần tử u (tìm đại diện)
int findSet(int u) {
    if (parent[u] != u) {
        parent[u] = findSet(parent[u]); // Path compression
    }
    return parent[u];
}

// Hợp nhất 2 tập (union by rank)
void unionSet(int x, int y) {
    int rx = findSet(x);
    int ry = findSet(y);
    if (rx != ry) {
        if (rankSet[rx] < rankSet[ry]) {
            parent[rx] = ry;
        } else if (rankSet[rx] > rankSet[ry]) {
            parent[ry] = rx;
        } else {
            parent[ry] = rx;
            rankSet[rx]++;
        }
    }
}

// --------------------------------------
// Thuật toán Kruskal
// - edges[]: mảng chứa các cạnh
// - E: số cạnh
// - V: số đỉnh
// --------------------------------------
void kruskalMST(Edge edges[], int E, int V) {
    // B1. Khởi tạo Disjoint Set cho các đỉnh [0..V-1]
    for (int i = 0; i < V; i++) {
        parent[i] = i;    // cha của i là chính i
        rankSet[i] = 0;   // rank ban đầu = 0
    }

    // B2. Sắp xếp các cạnh theo trọng số tăng dần
    sortEdges(edges, E);

    // Kết quả MST sẽ có tối đa (V - 1) cạnh
    cout << "MST edges (Kruskal):\n";

    // B3. Duyệt lần lượt các cạnh đã sắp xếp
    int mstCount = 0; // đếm số cạnh đã đưa vào MST
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        // Kiểm tra xem u, v có cùng tập không
        if (findSet(u) != findSet(v)) {
            // Không tạo chu trình => thêm vào MST
            cout << u << " -- " << v 
                 << "  ==  " << edges[i].weight << "\n";
            unionSet(u, v);
            mstCount++;
            if (mstCount == V - 1) {
                break; // MST đủ rồi
            }
        }
    }
}