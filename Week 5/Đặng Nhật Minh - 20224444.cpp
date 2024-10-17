/*Bài 1:  Nhập vào n đối tượng có màu đỏ (red), trắng (white) và xanh (blue), sắp xếp theo trật tự như sau: các đối tượng cùng mầu nằm kế tiếp nhau và theo thứ tự đỏ, trắng, xanh.
Input {xanh, đỏ, xanh, đỏ, đỏ, trắng, đỏ, xanh, trắng}
Output {đỏ, đỏ, đỏ, đỏ, trắng, trắng, xanh, xanh, xanh}
Gợi ý:
Có thể mã hóa các mầu bằng các số nguyên 0, 1, 2 để biểu diễn lần lượt mầu đỏ, trắng và xanh tương ứng.
Chú ý: Không sử dụng các thư viện hàm sắp xếp có sẵn để giải quyết bài toán trên khi cài đặt chương trình
Bài 2: Thiết kế giải thuật và cài đặt để tạo ra một mảng số nửa nguyên tố nhỏ hơn một số N cho trước và thực hiện hai yêu cầu sau
- Tìm ra tất cả các cặp số nửa nguyên tố có tổng cũng là một số nửa nguyên tố nhỏ hơn N
- Kiểm tra xem một số nửa nguyên tố M có tồn tại trong dãy số Blum được tạo ra hay không.
Đặng Nhật Minh - 20224444*/

#include <iostream>
#include <vector>

class Bai1{
    private:
    std::vector<std::string> colors = {"do", "xanh", "do", "do", "trang", "xanh", "xanh", "trang", "do"};
    public:
    Bai1(){ std::cout<< "Bai 1:" << std::endl; }
    void sortColors(){
        for(int i = 0; i < colors.size(); ++i){
            for(int j = i + 1; j < colors.size(); ++j){
                if(colors[i] > colors[j]){
                    std::string temp = colors[i];
                    colors[i] = colors[j];
                    colors[j] = temp;
                }
            }
        }
    }
    void printColors(){
        for(int i = 0; i < colors.size(); ++i){
            std::cout << colors[i] << " ";
        }
        std::cout << std::endl;
    }
};

class Bai2{
    //Semiprime number
    private:
        std::vector<int> Semiprime;
        int n;
    public:
        Bai2(){
            std::cout << "Bai 2:" << std::endl;
            std::cout << "Nhap N: ";
            std::cin >> n;
            for(int i = 2; i < n; ++i){
                if(isSemiprime(i)){
                    Semiprime.push_back(i);
                }
            }
            printSemiprime();
        }

        bool isSemiprime(int n){
            int count = 0;
            for(int i = 2; i <= n; ++i){
                if(n % i == 0){
                    ++count;
                    if(count > 2){
                        return false;
                    }
                    n /= i;
                    --i;
                }
            }
            if(count == 2){
                return true;
            }
            return false;
        }

        void printSemiprime(){
            std::cout << "List cac so nua nguyen to nho hon " << n << ": ";
            for(int i = 0; i < Semiprime.size(); ++i){
                std::cout << Semiprime[i] << " ";
            }
            std::cout << std::endl;
        }

        void findSemiprimePair(){
            int count = 0;
            for(int i = 0; i < Semiprime.size() - 1; ++i){
                for(int j = i + 1; j < Semiprime.size(); ++j){
                    if(isSemiprime(Semiprime[i] + Semiprime[j])&& Semiprime[i] + Semiprime[j] < n){
                        ++count;
                        std::cout << "Pair " << count << ": (" << Semiprime[i] << ", " << Semiprime[j] << ')' << std::endl;
                    }
                }
            }
            if(count == 0) std::cout << "Khong co cap nao thoa man" << std::endl;
            else std::cout << "Co tat ca " << count << " cap so nua nguyen to ma tong cua no bang mot so nua nguyen to khac trong mang" << std::endl;
            
            std::cout << std::endl;
        }
};

int main(){
    //O(n^2)
    Bai1 b1;
    b1.sortColors();
    b1.printColors();
    Bai2 b2;
    b2.findSemiprimePair();
}