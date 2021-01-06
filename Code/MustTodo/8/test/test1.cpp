#include <bits/stdc++.h>
using namespace std;
const int counts = 10;
int arr[10] = {2, 5, 3, 9, 1, 43, 55, 12, 15, 9999};
// int arr[5] = {4, 9, 8, 5, 6};

void BubbleSort() {
    for (int i = 0; i < counts - 1; i++) {
        for (int j = 0; j < counts - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

/**
 * @description: —°‘Ò≈≈–Ú
 */
void Selection() {
    for (int i = 0; i < counts; i++) {
        int k = i;
        for (int j = k + 1; j < counts; j++) {
            if (arr[j] < arr[k]) {
                k = j;
            }
        }
        if (k != i) {
            int tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp;
        }
    }
}

int partition(int low, int high) {
    int tmp = arr[low];
    while (low < high) {
        while (low < high && tmp <= arr[high]) {
            high--;
        }
        arr[low] = arr[high];
        while (low < high && tmp >= arr[low]) {
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = tmp;
    return low;
}

void QuickSort(int low, int high) {
    if (low < high) {
        int pivot = partition(low, high);
        QuickSort(low, pivot - 1);
        QuickSort(pivot + 1, high);
    }
}
void QuickSort() { QuickSort(0, 9); }

void HeapSort(int i, int length) {
    int tmp = arr[i];
    for (int k = 2 * i + 1; k < length; k = 2 * k + 1) {
        if (k + 1 < length && arr[k] < arr[k + 1]) {
            ++k;
        }
        if (tmp < arr[k]) {
            arr[i] = arr[k];
            i = k;
        } else {
            break;
        }
    }
    arr[i] = tmp;
}

void HeapSort() {
    int tmp = 0;
    for (int i = counts / 2 - 1; i >= 0; --i) {
        HeapSort(i, counts);
    }
    for (int j = counts - 1; j > 0; j--) {
        tmp = arr[j];
        arr[j] = arr[0];
        arr[0] = tmp;
        HeapSort(0, j);
    }
}

void print() {
    for (int i = 0; i < counts; i++) {
        cout << arr[i] << " ";
    }
}

void traverse() {
    for (int k = 0; k < 5; k++) {
        int tmp = arr[k];
        arr[k] = arr[9 - k];
        arr[9 - k] = tmp;
    }
}

/**
 * @description: ?????????
 */
void merge(int left, int mid, int right, int tmp[]) {
    int i = left;
    int j = mid + 1;
    int t = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            tmp[t++] = arr[i++];
        } else {
            tmp[t++] = arr[j++];
        }
    }
    while (i <= mid) {
        tmp[t++] = arr[i++];
    }
    while (j <= right) {
        tmp[t++] = arr[j++];
    }
    t = 0;
    int tmpLeft = left;
    while (tmpLeft <= right) {
        arr[tmpLeft++] = tmp[t++];
    }
}

void mergeSort(int left, int right, int tmp[]) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(left, mid, tmp);
        mergeSort(mid + 1, right, tmp);
        merge(left, mid, right, tmp);
    }
}

void mergeSort() {
    int *tmp = new int[counts]();
    mergeSort(0, counts - 1, tmp);
}

/**
 * @description: ????
 */
void Insert(int num, int length) {
    int i = 0;
    for (i = length - 1; i >= 0; i--) {
        if (num < arr[i]) {
            arr[i + 1] = arr[i];
        } else {
            break;
        }
    }
    arr[i + 1] = num;
}

void InsertSort() {
    int length = 1;
    for (int i = 1; i < counts; i++) {
        Insert(arr[i], length);
        length++;
    }
}

/**
 * @description: ????
 */
void shellSortingSwap(int array[], int length) {
    for (int gap = length / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < length; ++i) {
            for (int j = i - gap; j >= 0; j -= gap) {
                if (array[j] > array[j + gap]) {
                    int tmp = array[j];
                    array[j] = array[j + gap];
                    array[j + gap] = tmp;
                }
            }
        }
    }
}

void radixSort() {
    int max = arr[0];
    for (int i = 1; i < counts; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    int maxLength = 0;
    while (max) {
        max /= 10;
        maxLength++;
    }
    //????????????
    int **bucket;
    bucket = new int *[10];
    for (int i = 0; i < 10; i++) {
        bucket[i] = new int[counts]();
    }
    int *bucketElementCounts = new int[10]();

    for (int k = 0, n = 1; k < maxLength; k++, n *= 10) {
        for (int i = 0; i < counts; i++) {
            int digitOfElement = arr[i] / n % 10;
            bucket[digitOfElement][bucketElementCounts[digitOfElement]++] =
                arr[i];
        }
        int index = 0;
        for (int i = 0; i < counts; i++) {
            if (bucketElementCounts[i] > 0) {
                for (int j = 0; j < bucketElementCounts[i]; j++) {
                    arr[index++] = bucket[i][j];
                }
            }
            bucketElementCounts[i] = 0;
        }
    }
}

int main() {
    // shellSortingSwap(arr, counts);
    radixSort();
    print();

    return 0;
}