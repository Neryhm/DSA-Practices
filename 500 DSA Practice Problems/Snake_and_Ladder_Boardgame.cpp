#include <iostream>
#include <queue>           // dùng trong BFS
#include <unordered_map>
#include <vector>
#include <algorithm>       // hàm std::reverse

// Ta xem bàn cờ gồm 100 ô 10x10
#define N 100

/*
  BÀI TOÁN "SNAKE AND LADDER"
  ---------------------------
  - Bàn cờ có 100 ô, đánh số 1..100
  - Có một số "cặp" (start -> end) thể hiện Thang hoặc Rắn:
       + Thang: start < end => đi từ start sẽ nhảy lên end.
       + Rắn  : start > end => đi từ start sẽ tụt xuống end.
  - Mỗi lượt, ta gieo xúc xắc (1..6) và di chuyển từ vị trí hiện tại. Nếu rơi 
    vào ô có rắn/thang, ta lập tức chuyển sang ô đích do rắn/thang quy định.
  - Mục tiêu: Tìm cách đến ô 100 với số lượt gieo xúc xắc ít nhất.
  
  Ý TƯỞNG (BFS)
  ------------------------------------------------------
  - Xem mỗi ô là một đỉnh (vertex) của đồ thị.
  - Từ mỗi ô i, ta có thể gieo xúc xắc 6 giá trị (1..6), tạo ra 6 cạnh (edge) 
    đi đến ô i+j (nếu i+j <= 100). Sau đó, nếu ô (i+j) là đầu của Rắn/Thang, 
    ta nhảy sang đuôi/đầu thang tương ứng.
  - Ta xây dựng danh sách kề (adjList).
  - Chạy BFS từ ô 1 đến ô 100:
    + Khi duyệt ô con, lưu lại “cha” (parent) và “diceUsed” (giá trị xúc xắc) đã 
      giúp đi từ cha đến con.
    + Khi đến được ô 100, ta dừng BFS, dùng mảng parent[] và diceUsed[] để dựng 
      lại đường đi kèm từng giá trị xúc xắc.
  - Kết quả: Số lượt gieo chính là chiều dài đường đi. Danh sách xúc xắc gieo 
    chính là diceUsed[] trên đường.
*/

/*
  Cấu trúc lưu một cạnh của đồ thị, gồm:
    - src (đỉnh nguồn)
    - dest (đỉnh đích)
    - dice (giá trị xúc xắc đã gieo để đi từ src đến dest)
*/
struct Edge {
    int src;
    int dest;
    int dice;
};

/*
  Lớp Graph:
  - adjList[u] là danh sách các (đỉnh kề, giá trị xúc xắc) mà từ u có thể đi tới.
*/
class Graph {
public:
    // Mỗi ô có một vector chứa các cặp (đỉnh đích, dice)
    std::vector<std::pair<int,int>> adjList[N + 1];

    // Hàm dựng nhận vào danh sách các cạnh (Edge)
    Graph(const std::vector<Edge> &edges) {
        // Duyệt tất cả các cạnh để lập danh sách kề
        for (auto &edge : edges) {
            // Thêm (đỉnh đích, xúc xắc) vào adjList của src
            adjList[edge.src].push_back({edge.dest, edge.dice});
        }
    }
};

/*
  Hàm BFS:
  - Thực hiện BFS từ ô 1 đến ô 100.
  - Trả về vector<int> gồm các giá trị xúc xắc đã gieo để đi từ 1 đến 100 
    (theo thứ tự).
  - Nếu không đến được 100, vector trả về rỗng.
*/
std::vector<int> BFS(const Graph &g, int start, int target) {
    // Hàng đợi lưu các ô
    std::queue<int> q;
    q.push(start);

    // Mảng đánh dấu ô đã thăm
    std::vector<bool> visited(N + 1, false);
    visited[start] = true;

    // Mảng parent[u] để lưu "ô cha" của u
    std::vector<int> parent(N + 1, -1);
    // Mảng diceUsed[u] để lưu giá trị xúc xắc khi đi từ parent[u] đến u
    std::vector<int> diceUsed(N + 1, -1);

    // BFS
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Nếu đã đến ô 100, ta có thể dừng BFS và truy hồi đường đi
        if (current == target) {
            // truy hồi đường đi: ta lần ngược từ 100 về 1 qua parent[],
            // đồng thời lưu diceUsed[] tương ứng
            std::vector<int> pathDice;
            int node = target;

            // Lùi về cho đến khi gặp start (hoặc -1)
            while (node != -1 && node != start) {
                pathDice.push_back(diceUsed[node]);
                node = parent[node];
            }

            // Đảo ngược lại vì ta vừa thu thập từ đích về nguồn
            std::reverse(pathDice.begin(), pathDice.end());

            return pathDice;
        }

        // Nếu chưa đến target, ta xét các cạnh kề
        for (auto &nbr : g.adjList[current]) {
            int nextCell = nbr.first;
            int dice = nbr.second;

            if (!visited[nextCell]) {
                visited[nextCell] = true;
                parent[nextCell] = current;
                diceUsed[nextCell] = dice;
                q.push(nextCell);
            }
        }
    }

    // Nếu BFS xong mà không tìm thấy đường đến target, trả về mảng rỗng
    return {};
}

/*
  Hàm findMinimumMoves:
  - Dựng danh sách tất cả các cạnh (src -> dest) có tính đến Rắn/Thang.
  - Từ mỗi ô i, với 6 giá trị xúc xắc (1..6), nếu i+j <= 100:
       + Tính ô đích, có thể bị điều chỉnh nếu rơi vào Rắn/Thang.
  - Dùng đồ thị này để BFS, tìm đường đi từ 0 đến 100.
  - Kết quả trả về là dãy xúc xắc gieo (theo thứ tự).
*/
std::vector<int> findMinimumMoves(
    const std::unordered_map<int, int> &ladder,
    const std::unordered_map<int, int> &snake)
{
    // Tạo vector lưu các cạnh
    std::vector<Edge> edges;
    edges.reserve(N * 6); // ước lượng trước

    // Với mỗi ô i trong [1..99]
    for (int i = 0; i < N; i++)
    {
        // Gieo xúc xắc j từ 1..6
        for (int j = 1; j <= 6 && i + j <= N; j++)
        {
            int src = i;
            
            // Tính ô đích tạm thời (i + j)
            int tmp = i + j;

            // Kiểm tra xem ô đó có rơi vào đầu Rắn/Thang không
            // Nếu có, điều chỉnh tmp thành end của Rắn/Thang
            auto itLadder = ladder.find(tmp);
            if (itLadder != ladder.end()) {
                tmp = itLadder->second;
            }
            auto itSnake = snake.find(tmp);
            if (itSnake != snake.end()) {
                tmp = itSnake->second;
            }

            int dest = tmp;

            // Tạo một cạnh (src -> dest, dice=j)
            Edge e = { src, dest, j };
            edges.push_back(e);
        }
    }

    // Xây dựng đồ thị
    Graph g(edges);

    // Gọi BFS để tìm đường từ 0 đến 100
    return BFS(g, 0, 100);
}

int main()
{
    // Tạo bảng băm cho ladder, snake (Rắn và Thang)
    std::unordered_map<int, int> ladder;
    std::unordered_map<int, int> snake;

    // Nhập số lượng thang
    std::cout << "Nhập số lượng thang (ladder): ";
    int L;
    std::cin >> L;
    // Nhập từng cặp start -> end cho thang
    // start < end
    for(int i = 0; i < L; i++) {
        int start, end;
        std::cout << "Nhập cặp thang thứ " << i + 1 << " (start end): ";
        std::cin >> start >> end;
        ladder[start] = end;
    }

    // Nhập số lượng rắn
    std::cout << "Nhập số lượng rắn (snake): ";
    int S;
    std::cin >> S;
    // Nhập từng cặp start -> end cho rắn
    // start > end
    for(int i = 0; i < S; i++) {
        int start, end;
        std::cout << "Nhập cặp rắn thứ " << i + 1 << " (start end): ";
        std::cin >> start >> end;
        snake[start] = end;
    }

    // Tìm dãy xúc xắc dùng để đi từ 0 đến 100
    std::vector<int> result = findMinimumMoves(ladder, snake);

    // Nếu không có đường đi (result rỗng), in thông báo
    if (result.empty()) {
        std::cout << "Không thể đến đích!\n";
    } else {
        // In số lượt gieo:
        std::cout << "Số lượt gieo min: " << result.size() << "\n";
        // In các giá trị xúc xắc
        std::cout << "Các xúc xắc có thể gieo để được min (theo thứ tự): ";
        for (auto dice : result) {
            std::cout << dice << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
