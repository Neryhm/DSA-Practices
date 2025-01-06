#include <iostream>
using namespace std;

// Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Hoán đổi arr[i] và arr[minIndex]
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // Dịch chuyển các phần tử lớn hơn key sang phải
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        // Đặt key vào vị trí thích hợp
        arr[j + 1] = key;
    }
}

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Hoán đổi
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Quick Sort
// Hàm partition
int partitionFunc(int arr[], int low, int high) {
    int pivot = arr[high]; // Chọn pivot là phần tử cuối
    int i = low - 1;       // i là ranh giới của phần nhỏ hơn pivot
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            // Hoán đổi arr[i] và arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Đưa pivot (arr[high]) vào vị trí thích hợp
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

// Hàm sắp xếp
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionFunc(arr, low, high);
        // Đệ quy tiếp cho 2 phần
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
// Hàm merge: trộn hai mảng con arr[l..m], arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    // Tạo mảng tạm
    int *L = new int[n1];
    int *R = new int[n2];
    
    // Copy dữ liệu
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    // Trộn lại
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Copy các phần còn lại
    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
    delete[] L;
    delete[] R;
}

// Hàm sắp xếp
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2; // Tìm điểm giữa
        // Đệ quy sắp xếp 2 nửa
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        // Trộn kết quả 2 nửa
        merge(arr, l, m, r);
    }
}

// Heap Sort
// Đảm bảo tính chất max-heap tại node `i` trong vùng [0..n-1]
void heapify(int arr[], int n, int i) {
    int largest = i;       // node gốc
    int left = 2 * i + 1;  // con trái
    int right = 2 * i + 2; // con phải
    
    // Nếu con trái lớn hơn gốc
    if (left < n && arr[left] > arr[largest])
        largest = left;
    // Nếu con phải lớn hơn node lớn nhất hiện tại
    if (right < n && arr[right] > arr[largest])
        largest = right;
    // Nếu largest không phải i, hoán đổi và đệ quy
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        
        heapify(arr, n, largest);
    }
}

// Hàm sắp xếp
void heapSort(int arr[], int n) {
    // Bước 1: Xây dựng max-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // Bước 2: Hoán đổi từng phần tử cuối, rồi heapify lại
    for (int i = n - 1; i >= 0; i--) {
        // Di chuyển root (phần tử lớn nhất) về cuối
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        // Gọi heapify lên đỉnh (chú ý giới hạn i, nghĩa là “cắt bớt” heap)
        heapify(arr, i, 0);
    }
}

// Binary Search
int binarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid = (left + right) / 2;
        
        if (arr[mid] == x) {
            return mid; // Tìm thấy
        } else if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Không tìm thấy
}


