#include <iostream>
#include <list>
using namespace std;

int josephus(int N, int M) {
    list<int> people;
    for (int i = 1; i <= N; i++) {
        people.push_back(i);
    }

    auto it = people.begin();
    while (people.size() > 1) {
        if (M == 0) {
            it = people.erase(it);
            if (it == people.end()) {
                it = people.begin();
            }
        } else {
            for (int i = 0; i < M; i++) {
                ++it;
                if (it == people.end()) {
                    it = people.begin();
                }
            }
            it = people.erase(it);
            if (it == people.end()) {
                it = people.begin();
            }
        }
    }

    return *people.begin();
}

int main() {
    int N, M;
    cout << "Enter the number of people (N): ";
    cin >> N;
    cout << "Enter the step count (M): ";
    cin >> M;

    int winner = josephus(N, M);
    cout << "The winner is: " << winner << endl;

    return 0;
}

/*
Time complexity: O(N*M) vì mỗi lần loại bỏ 1 người thì phải di chuyển qua M người
Space complexity: O(N) vì sử dụng linked list N phần tử
Khi N > 100,000 và M = 1, mỗi lần loại bỏ 1 người chỉ di chuyển đến người tiếp theo. Do đó, độ phức tạp thời gian trở thành O(N^2)
Thời gian chạy khi đó sẽ là O(100000^2) = 100,000,000 lần di chuyển
*/ 