#include <iostream>  // Cho cin, cout
// KHÔNG dùng: using namespace std;

#define M 5  // Số hàng (rows)
#define N 6  // Số cột (columns)

/*
  Giải Thích Bài Toán:
  --------------------
  - Ta có một bảng 5×6, mỗi ô có thể là:
      + 'L' hoặc 'R': cặp ngang (Left-Right).
      + 'T' hoặc 'B': cặp dọc (Top-Bottom).
      + 'X': ô trống hoặc chưa xác định.
  - Mỗi cặp ('L','R') hay ('T','B') sẽ được điền một cặp ('+','-') hoặc ('-','+').
  - Ngoài ra, phải thỏa mãn:
      1) Số dấu '+' trong mỗi cột bằng top[col] (nếu != -1).
      2) Số dấu '-' trong mỗi cột bằng bottom[col] (nếu != -1).
      3) Số '+' trong mỗi hàng bằng left[row], số '-' bằng right[row] (nếu != -1).
      4) Hai ô kề nhau (lên, xuống, trái, phải) không được cùng dấu (nếu không chung 1 cặp).
  - Bài toán: Tìm cách sắp xếp '+' và '-' để thỏa mãn các ràng buộc trên, 
    hoặc báo "không có lời giải" nếu không thể.
*/

/* Mô tả các hàm:
   printBoard(...)        - In bảng kết quả ra màn hình
   countCol(...)        - Đếm số ô mang ký tự ch trong 1 cột
   countRoww(...)       - Đếm số ô mang ký tự ch trong 1 hàng
   isValid(...) - Kiểm tra xem đặt '+' hay '-' tại (row,col) có vi phạm gì không
   checkWin(...)   - Kiểm tra cuối cùng xem bảng có đúng ràng buộc top/left/bottom/right không
   tryMagnet(...) - Hàm đệ quy backtracking để điền dấu +/-
   solveMagnet(...)   - "driver": khởi tạo, gọi tryMagnet, in kết quả
*/

// Hàm in bảng 5×6
void printBoard(char board[M][N])
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Đếm số ký tự `ch` trong cột `col`
int countCol(char board[M][N], char ch, int col)
{
    int count = 0;
    for (int i = 0; i < M; i++)
    {
        if (board[i][col] == ch) {
            count++;
        }
    }
    return count;
}

// Đếm số ký tự `ch` trong hàng `row`
int countRow(char board[M][N], char ch, int row)
{
    int count = 0;
    for (int j = 0; j < N; j++)
    {
        if (board[row][j] == ch) {
            count++;
        }
    }
    return count;
}

// Kiểm tra xem có đặt được ký hiệu `ch` (+ hoặc -) tại (row,col) hay không
bool isValid(char board[M][N], int row, int col, char ch,
                   int top[], int left[], int bottom[], int right[])
{
    // Kiểm tra 4 ô kề: không cho phép ô kề có cùng ký hiệu `ch`
    // (nếu row-1 >= 0, col+1 < N, row+1 < M, col-1 >= 0)
    if ((row - 1 >= 0 && board[row - 1][col] == ch) ||  // ô trên
        (col + 1 < N && board[row][col + 1] == ch)  ||  // ô phải
        (row + 1 < M && board[row + 1][col] == ch)  ||  // ô dưới
        (col - 1 >= 0 && board[row][col - 1] == ch))    // ô trái
    {
        return false;
    }

    // Đếm số ch trong hàng, cột
    int soChHang = countRow(board, ch, row);
    int soChCot  = countCol(board, ch, col);

    // Nếu ch = '+', kiểm tra ràng buộc top[col], left[row]
    if (ch == '+')
    {
        // top[col] là số '+' phải có trong cột col (nếu != -1)
        if (top[col] != -1 && soChCot >= top[col]) {
            return false;
        }
        // left[row] là số '+' phải có trong hàng row (nếu != -1)
        if (left[row] != -1 && soChHang >= left[row]) {
            return false;
        }
    }

    // Nếu ch = '-', kiểm tra bottom[col], right[row]
    if (ch == '-')
    {
        // bottom[col] là số '-' phải có trong cột col (nếu != -1)
        if (bottom[col] != -1 && soChCot >= bottom[col]) {
            return false;
        }
        // right[row] là số '-' phải có trong hàng row (nếu != -1)
        if (right[row] != -1 && soChHang >= right[row]) {
            return false;
        }
    }

    return true;
}

// Kiểm tra cuối cùng: các cột/hàng đã khớp số lượng +, - với top[], bottom[], left[], right[] chưa
bool checkWin(char board[M][N], int top[], int left[], int bottom[], int right[])
{
    // Kiểm tra top[]: số '+' trong mỗi cột
    for (int j = 0; j < N; j++)
    {
        if (top[j] != -1)
        {
            if (countCol(board, '+', j) != top[j]) {
                return false;
            }
        }
    }

    // Kiểm tra left[]: số '+' trong mỗi hàng
    for (int i = 0; i < M; i++)
    {
        if (left[i] != -1)
        {
            if (countRow
    (board, '+', i) != left[i]) {
                return false;
            }
        }
    }

    // Kiểm tra bottom[]: số '-' trong mỗi cột
    for (int j = 0; j < N; j++)
    {
        if (bottom[j] != -1)
        {
            if (countCol(board, '-', j) != bottom[j]) {
                return false;
            }
        }
    }

    // Kiểm tra right[]: số '-' trong mỗi hàng
    for (int i = 0; i < M; i++)
    {
        if (right[i] != -1)
        {
            if (countRow
    (board, '-', i) != right[i]) {
                return false;
            }
        }
    }

    return true;
}

// Hàm đệ quy backtracking đặt cặp +/-
bool tryMagnet(char board[M][N], int row, int col,
                   int top[], int left[], int bottom[], int right[],
                   char rules[M][N])
{
    // Nếu ta đã xét xong đến ô cuối cùng (hàng M-1, cột N-1)
    if (row == M - 1 && col == N)
    {
        // Kiểm tra cấu hình cuối
        if (checkWin(board, top, left, bottom, right)) {
            return true;
        }
        return false;
    }

    // Nếu col >= N, chuyển sang hàng mới
    if (col == N)
    {
        return tryMagnet(board, row + 1, 0, top, left, bottom, right, rules);
    }

    // Nếu ô này là 'R' hoặc 'B', ta không cần đặt (đã xử lý trước), move tiếp
    if (rules[row][col] == 'R' || rules[row][col] == 'B')
    {
        if (tryMagnet(board, row, col + 1, top, left, bottom, right, rules)) {
            return true;
        }
    }

    // Nếu ô này là 'L' và ô kế bên là 'R', tức slot ngang
    if (rules[row][col] == 'L' && (col + 1 < N) && rules[row][col + 1] == 'R')
    {
        // Thử đặt (+, -)
        if (isValid(board, row, col, '+', top, left, bottom, right) &&
            isValid(board, row, col + 1, '-', top, left, bottom, right))
        {
            board[row][col] = '+';
            board[row][col + 1] = '-';

            if (tryMagnet(board, row, col + 2, top, left, bottom, right, rules)) {
                return true;
            }

            // backtrack
            board[row][col] = 'X';
            board[row][col + 1] = 'X';
        }

        // Thử đặt (-, +)
        if (isValid(board, row, col, '-', top, left, bottom, right) &&
            isValid(board, row, col + 1, '+', top, left, bottom, right))
        {
            board[row][col] = '-';
            board[row][col + 1] = '+';

            if (tryMagnet(board, row, col + 2, top, left, bottom, right, rules)) {
                return true;
            }

            // backtrack
            board[row][col] = 'X';
            board[row][col + 1] = 'X';
        }
    }

    // Nếu ô này là 'T' và ô kế dưới là 'B', tức slot dọc
    if (rules[row][col] == 'T' && (row + 1 < M) && rules[row + 1][col] == 'B')
    {
        // Thử đặt (+, -)
        if (isValid(board, row, col, '+', top, left, bottom, right) &&
            isValid(board, row + 1, col, '-', top, left, bottom, right))
        {
            board[row][col] = '+';
            board[row + 1][col] = '-';

            // Sau khi đặt xong, sang ô kế tiếp
            if (tryMagnet(board, row, col + 1, top, left, bottom, right, rules)) {
                return true;
            }

            // backtrack
            board[row][col] = 'X';
            board[row + 1][col] = 'X';
        }

        // Thử đặt (-, +)
        if (isValid(board, row, col, '-', top, left, bottom, right) &&
            isValid(board, row + 1, col, '+', top, left, bottom, right))
        {
            board[row][col] = '-';
            board[row + 1][col] = '+';

            if (tryMagnet(board, row, col + 1, top, left, bottom, right, rules)) {
                return true;
            }

            // backtrack
            board[row][col] = 'X';
            board[row + 1][col] = 'X';
        }
    }

    // Thử bỏ qua ô này (đặt 'X') và chuyển sang ô kế
    if (tryMagnet(board, row, col + 1, top, left, bottom, right, rules)) {
        return true;
    }

    return false; // Không cách nào hợp lệ
}

// Hàm chính “driver”: khởi tạo board, gọi đệ quy, in kết quả
void solveMagnet(int top[], int left[], int bottom[], int right[], char rules[M][N])
{
    // Tạo bảng lưu kết quả, ban đầu toàn 'X'
    char board[M][N];
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            board[i][j] = 'X';
        }
    }

    // Bắt đầu đệ quy từ ô (0,0)
    bool ok = tryMagnet(board, 0, 0, top, left, bottom, right, rules);

    if (!ok)
    {
        std::cout << "Khong co loi giai" << std::endl;
    }
    else
    {
        printBoard(board);
    }
}

int main()
{
    // Trong ví dụ này, ta cố định M=5, N=6.
    // Người dùng sẽ nhập 4 mảng top, bottom (kích thước 6), left, right (kích thước 5)
    // và sau đó nhập rules[M][N].

    int top[N], bottom[N], left[M], right[M];
    char rules[M][N];

    // Nhập top[]
    std::cout << "Nhap 6 gia tri top[] (so '+' moi cot, -1 neu khong gioi han):\n";
    for (int i = 0; i < N; i++) {
        std::cin >> top[i];
    }

    // Nhập bottom[]
    std::cout << "Nhap 6 gia tri bottom[] (so '-' moi cot, -1 neu khong gioi han):\n";
    for (int i = 0; i < N; i++) {
        std::cin >> bottom[i];
    }

    // Nhập left[]
    std::cout << "Nhap 5 gia tri left[] (so '+' moi hang, -1 neu khong gioi han):\n";
    for (int i = 0; i < M; i++) {
        std::cin >> left[i];
    }

    // Nhập right[]
    std::cout << "Nhap 5 gia tri right[] (so '-' moi hang, -1 neu khong gioi han):\n";
    for (int i = 0; i < M; i++) {
        std::cin >> right[i];
    }

    // Nhập ma trận rules 5×6
    // Mỗi ô là 1 ký tự trong {'L','R','T','B','X'} (tuỳ puzzle)
    std::cout << "Nhap ma tran rules (5 hang, moi hang 6 ky tu):\n";
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cin >> rules[i][j];
        }
    }

    // Gọi hàm giải
    solveMagnet(top, left, bottom, right, rules);
    /*
    Input mẫu:
    1 -1 -1 2 1 -1
    2 -1 -1 2 -1 3
    2 3 -1 -1 -1
    -1 -1 -1 1 -1

    L R L R T T
    L R L R B B
    T T T T L R
    B B B B T T
    L R L R B B
    */

    return 0;
}
