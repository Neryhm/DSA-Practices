#include <iostream>
#include <vector>
#include <unordered_map>

/*
  BÀI TOÁN "TWO SUM"
  -----------------
  - Cho một mảng số nguyên (nums) và một số nguyên target.
  - Yêu cầu: tìm hai chỉ số (i, j) sao cho nums[i] + nums[j] = target.
  - Có thể có nhiều cặp thỏa mãn, ta chỉ cần trả về một cặp (i, j) bất kỳ.

  Giải thích:
  -----------------------
  - Ta có thể duyệt tất cả cặp (i, j) để kiểm tra, nhưng cách đó có độ phức tạp O(n^2).
  - Giải pháp tối ưu hơn (O(n)):
    + Dùng một cấu trúc dữ liệu dạng bảng băm (hash map) để lưu trữ và tra cứu nhanh.
    + Với mỗi phần tử nums[i], ta kiểm tra xem (target - nums[i]) đã xuất hiện trước đó chưa.
      - Nếu đã xuất hiện và được lưu trong bảng băm với chỉ số k, ta có cặp (k, i) thỏa mãn.
      - Nếu chưa, lưu nums[i] cùng chỉ số i vào bảng băm và tiếp tục.
  - Thuật toán này đảm bảo ta chỉ duyệt mảng đúng một lần (tính thời gian trung bình),
    nên độ phức tạp trung bình là O(n).

  Chi tiết:
  --------------------
  - Tạo một bảng băm lưu cặp (giá trị phần tử -> chỉ số).
  - Lần lượt duyệt i từ 0 đến n-1:
      + Tính key = target - nums[i].
      + Kiểm tra trong bảng băm có chứa key hay không.
      + Nếu có, trả về cặp (chỉ số key, i).
      + Nếu không, thêm (nums[i], i) vào bảng băm.
  - Nếu không tìm thấy cặp nào, ta có thể trả về một mảng trống hoặc tùy định nghĩa.
*/

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    // Bảng băm (Hash map): key = giá trị phần tử, value = chỉ số phần tử
    std::unordered_map<int, int> hashTable;

    // Duyệt các phần tử trong mảng
    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
        // key là giá trị còn thiếu để đạt được target
        int key = target - nums[i];

        // Kiểm tra xem key đã có trong bảng băm chưa
        if (hashTable.find(key) != hashTable.end()) {
            // Nếu có, ta lấy được cặp chỉ số
            return {hashTable[key], i};
        }

        // Nếu chưa, đưa nums[i] và chỉ số i vào bảng băm
        hashTable[nums[i]] = i;
    }

    // Nếu không tìm được cặp thỏa mãn
    return {};
}

int main() {
    // Nhập kích cỡ mảng
    std::cout << "Nhập số lượng ptử: ";
    int n;
    std::cin >> n;

    // Nhập các phần tử của mảng
    std::vector<int> nums(n);
    std::cout << "Nhập các ptử: ";
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }

    // Nhập giá trị target
    std::cout << "Nhập target: ";
    int target;
    std::cin >> target;

    // Gọi hàm twoSum
    std::vector<int> result = twoSum(nums, target);

    // Xuất kết quả
    if (result.size() == 2) {
        std::cout << "Chỉ số cần tìm: (" << result[0] << ", " << result[1] << ")\n";
        std::cout << "Vì nums[" << result[0] << "] + nums[" << result[1] 
                  << "] = " << nums[result[0]] + nums[result[1]] << " = " << target << "\n";
    } else {
        std::cout << "Không có cặp nào có tổng bằng " << target << "\n";
    }

    return 0;
}
