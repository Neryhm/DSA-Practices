#include <iostream>
#include <vector>
#include <algorithm>

/*
  BÀI TOÁN "POTS OF GOLD GAME"

  Mô tả bài toán:
  ---------------
  - Ta có một dãy n hũ vàng được xếp thành hàng.
  - Mỗi lượt, người chơi được phép chọn một trong hai hũ ở đầu hoặc cuối hàng.
  - Hai người chơi luân phiên nhau, người chơi đầu tiên (Player 1) là người 
    chủ động, nhưng cả hai đều chơi tối ưu.
  - Mục tiêu: Tìm số vàng tối đa mà Player 1 có thể thu được.

  Ý tưởng thuật toán (Bottom-up Dynamic Programming):
  ---------------------------------------------------
  - Định nghĩa dp[i][j] là giá trị tối đa mà người chơi (đang được đi) có thể 
    thu được khi chỉ còn các hũ từ vị trí i đến j.
  - Sau khi người chơi lấy xong, đối thủ sẽ chơi tối ưu, dẫn đến việc 
    người chơi hiện tại chỉ còn lại giá trị nhỏ hơn (do đối thủ cũng cố gắng lấy 
    nhiều nhất).
  - Công thức quy hoạch động thường gặp:
      dp[i][j] = max(
          value[i] + min(dp[i+2][j], dp[i+1][j-1]),
          value[j] + min(dp[i+1][j-1], dp[i][j-2])
      )
    - Lý do có min(...) là vì đối thủ sẽ lấy đi nước tốt hơn cho họ (và gây "bất lợi" nhất cho ta).
  - Cách tính:
      + dp[i][i] = value[i] (nếu chỉ còn 1 hũ thì chắc chắn lấy).
      + Điền dần dp cho các đoạn (subarray) có độ dài từ 2 đến n.
  - Kết quả cuối cùng: dp[0][n-1], là giá trị tối đa Player 1 có thể lấy với toàn dãy.
*/

static int getOptimalPick(int i, int j,
                          const std::vector<long long> &value,
                          const std::vector<std::vector<long long>> &dp) {
    /*
      Hàm phụ trợ: Cho biết người chơi "đang đến lượt" (tương ứng dp[i][j]) 
      sẽ chọn hũ nào (i hay j) trên đoạn [i..j], dựa vào công thức so sánh:
          left_pick  = value[i] + phần còn lại sau đối thủ (min(...))
          right_pick = value[j] + phần còn lại sau đối thủ (min(...))
      Trả về chỉ số hũ được chọn (i hoặc j).
    */

    // Nếu chỉ còn 1 hũ thì chắc chắn chọn hũ đó
    if (i == j) {
        return i;
    }

    // Tính "lợi ích" nếu chọn hũ i
    long long leftPick = value[i];
    // Sau khi ta chọn i, đối thủ sẽ đứng trước bài toán dp[i+1][j].
    // Đối thủ chọn i+1 hoặc j, khiến ta nhận được min(...) trong lượt kế.
    long long leftAfterOpp = 0;
    if (i + 2 <= j) {
        leftAfterOpp = dp[i+2][j];
    }
    if (i + 1 <= j - 1) {
        leftAfterOpp = std::min(leftAfterOpp, dp[i+1][j-1]);
    }
    leftPick += leftAfterOpp;

    // Tính "lợi ích" nếu chọn hũ j
    long long rightPick = value[j];
    long long rightAfterOpp = 0;
    if (i <= j - 2) {
        rightAfterOpp = dp[i][j-2];
    }
    if (i + 1 <= j - 1) {
        rightAfterOpp = std::min(rightAfterOpp, dp[i+1][j-1]);
    }
    rightPick += rightAfterOpp;

    // So sánh để xem chọn i hay j tốt hơn
    if (leftPick >= rightPick) {
        return i;  // Chọn hũ i
    } else {
        return j;  // Chọn hũ j
    }
}

void printGameMoves(const std::vector<long long> &value,
                    const std::vector<std::vector<long long>> &dp) {
    /*
      Hàm này mô phỏng toàn bộ quá trình game:
      - i, j ban đầu = 0, n-1
      - Player 1 và Player 2 lần lượt chọn, đều "tham khảo" hàm getOptimalPick 
        để biết nên chọn i hay j.
      - Sau mỗi lượt chọn, in ra người chơi, vị trí chọn, giá trị hũ vàng và 
        danh sách hũ còn lại.
      - Kết thúc khi i > j (hết hũ).
    */

    int i = 0;
    int j = static_cast<int>(value.size()) - 1;
    bool isPlayerOne = true;
    int turn = 1;

    while (i <= j) {
        // Xác định người chơi chọn hũ i hay hũ j
        int chosenIndex = getOptimalPick(i, j, value, dp);

        // In ra thông báo
        std::cout << "Luot " << turn 
                  << ": Player " << (isPlayerOne ? 1 : 2)
                  << " chon hu " << chosenIndex 
                  << " (gia tri = " << value[chosenIndex] << ")\n";
        
        // Cập nhật lại i hoặc j
        if (chosenIndex == i) {
            i++;
        } else {
            j--;
        }
        turn++;
        // Đổi lượt
        isPlayerOne = !isPlayerOne;

        // In ra hũ còn lại
        if (i <= j) {
            std::cout << "Cac hu con lai: ";
            for (int k = i; k <= j; k++) {
                std::cout << value[k] << (k < j ? " " : "");
            }
        } else {
            std::cout << "Khong con hu nao!";
        }
        std::cout << "\n\n";
    }
}

int main() {
    // Nhập số lượng hũ vàng
    std::cout << "Nhập số lượng hũ vàng (n): ";
    int n;
    std::cin >> n;
    
    // Nhập giá trị từng hũ
    std::vector<long long> value(n);
    std::cout << "Nhập giá trị các Pot: ";
    for (int i = 0; i < n; i++) {
        std::cin >> value[i];
    }

    // Tạo mảng dp, dp[i][j] lưu số vàng tối đa mà "người chơi tới lượt"
    // có thể lấy được trên đoạn [i..j].
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(n, 0));

    // Bước 1: Khởi tạo cho những đoạn dài 1 (chỉ một hũ)
    for (int i = 0; i < n; i++) {
        dp[i][i] = value[i];
    }

    // Bước 2: Xét độ dài đoạn từ 2 đến n
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            
            // Tính dp[i][j]
            // Lấy hũ i:
            long long pick_i = value[i];
            // Sau khi ta lấy i, đối thủ sẽ đối mặt đoạn [i+1..j]
            // nhưng đối thủ cũng tối ưu, nên ta chỉ được cộng thêm min(...) sau khi đối thủ lấy 1 hũ.
            long long afterOpponentPick_i = 0;
            if (i + 2 <= j) {
                afterOpponentPick_i = dp[i+2][j];
            }
            if (i + 1 <= j - 1) {
                afterOpponentPick_i = std::min(afterOpponentPick_i, dp[i+1][j-1]);
            }
            pick_i += afterOpponentPick_i;

            // Lấy hũ j:
            long long pick_j = value[j];
            long long afterOpponentPick_j = 0;
            if (i <= j - 2) {
                afterOpponentPick_j = dp[i][j-2];
            }
            if (i + 1 <= j - 1) {
                afterOpponentPick_j = std::min(afterOpponentPick_j, dp[i+1][j-1]);
            }
            pick_j += afterOpponentPick_j;

            dp[i][j] = std::max(pick_i, pick_j);
        }
    }

    // In kết quả tối đa cho Player 1
    std::cout << "\nSố vàng tối đa Player 1 có thể lấy: " << dp[0][n-1] << "\n\n";

    // In ra quá trình chọn của hai người chơi
    std::cout << "======== Turn Order ========\n\n";
    printGameMoves(value, dp);

    return 0;
}
