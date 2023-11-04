/*
PID : 13

Topic : Design and Analysis of Algorithms

Problem Statement : Implement merge sort and multithreaded merge sort. Compare time required by both the algorithms. Also analyze the performance of each algorithm for the best case and the worst case

*/

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

// Function to merge two subarrays of arr[]
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

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

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to perform merge sort on the array
void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// Thread function for merge sort
void mergeSortThread(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    if (r - l < 5) {
        mergeSort(arr, l, r);
        return;
    }

    int m = l + (r - l) / 2;
    thread t1(mergeSortThread, ref(arr), l, m);
    thread t2(mergeSortThread, ref(arr), m + 1, r);

    t1.join();
    t2.join();

    merge(arr, l, m, r);
}

// Function to print the array
void printArray(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    auto start = chrono::steady_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end = chrono::steady_clock::now();
    cout<<endl;
    cout << "Sorted array using simple merge sort: ";
    printArray(arr);
    cout << "Time taken by simple merge sort: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    start = chrono::steady_clock::now();
    mergeSortThread(arr, 0, n - 1);
    end = chrono::steady_clock::now();
    cout<<endl;
    cout << "Sorted array using multithreaded merge sort: ";
    printArray(arr);
    cout << "Time taken by multithreaded merge sort: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    return 0;
}


/*
The time complexity of the multithreaded merge sort is the same as that of the regular merge sort for both the best and worst cases. 

The best-case time complexity occurs when the input array is already sorted, while the worst-case time complexity occurs when the input array is in reverse order.



- Best Case Time Complexity: O(n log n)
- Worst Case Time Complexity: O(n log n)

Here, 'n' represents the number of elements in the input array. 
*/