#include <iostream>
#include <vector>
using namespace std;
int comparisons=0;
int swaps =0;
//====================================================
//Bubble Sort
//left half array
//ascending order
//====================================================
void BubbleSort(vector<int>& arr,int start,int end) {
    for (int i = start; i <= end; i++) {
        for (int j = start+1; j <= end-(i-start); j++) {
            comparisons++;
            if(arr[j]<arr[j-1]){
                swap(arr[j],arr[j-1]);
                swaps++;
            }
        }
    }
}
//======================================================
//SelectionSort
//right half array
//descending order
//======================================================
void selectionSort(vector<int>& arr,int start,int end) {
    for (int i = start; i <= end; i++) {
        int max =i;
        for ( int j = i+1; j <= end; j++) {
            comparisons++;
            if(arr[j]>arr[max]) {
                max = j;
            }
        }
        if(max != i) {
            swap(arr[i],arr[max]);
            swaps++;
        }
    }
}
//============================================================
//  Build Bitonic Array
//  Left  half (0..mid)       → ascending  via Bubble Sort
//  Right half (mid+1 .. n-1) → descending via Selection Sort
// ============================================================
void BuildBitonicArray(vector<int>& arr) {
    comparisons=0;
    swaps=0;
    int mid = arr.size()/2;
    BubbleSort(arr,0,mid-1);
    selectionSort(arr,mid,arr.size()-1);
}
//=========================================================
//Linear Search
//=========================================================
void LinearSearch(vector<int>& arr, int target) {
    bool found = false;
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == target) {
            cout << "Result         : FOUND at index " << i << "\n";
            found = true;
        }
    }
    if (!found)
        cout << "Result         : NOT FOUND\n";
}
//===========================================================
//print array
//===========================================================
void printArray(vector<int>& arr) {
    cout<<"[ ";
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout<<"]"<<endl;
}
//==========================================================
//run test cases
//=========================================================
void runTest(int testNum,vector<int>arr,int target,string description) {
    cout << "Test " << testNum << ": " << description << "\n";
    cout << "_______________________________________________________\n";

    cout << "Original array : ";
    printArray(arr);
    cout << "\n";

    BuildBitonicArray(arr);
    cout << "Bitonic  array : ";
    printArray(arr);
    cout << "\n";
    int mid = arr.size() / 2;
    cout << "Bitonic  point : index " << mid
        << "  (value = " << arr[mid] << ")\n";
    cout << "Comparisons    : " << comparisons << "\n";
    cout << "Swaps          : " << swaps       << "\n";

    cout << "Searching for  : " << target << "\n";
    LinearSearch(arr, target);

    cout << "_______________________________________________________\n";

}



int main() {
    cout << "_______________________________________________________\n";
    // Test 1 – target IS the bitonic point (highest value)
    runTest(1,
        {6, 1, 9, 3, 12, 4, 8},
        12,
        "Target at the Bitonic Point");

    // Test 2 – target in the LEFT (ascending) half
    runTest(2,
        {6, 1, 9, 3, 12, 4, 8},
        6,
        "Target in the LEFT half (ascending portion)");

    // Test 3 – target in the RIGHT (descending) half
    runTest(3,
        {6, 1, 9, 3, 12, 4, 8},
        4,
        "Target in the RIGHT half (descending portion)");

    // Test 4 – target NOT present
    runTest(4,
        {6, 1, 9, 3, 12, 4, 8},
        99,
        "Target NOT present in the array");

    // Test 5 – array with DUPLICATE elements
    runTest(5,
        {5, 3, 8, 3, 10, 5, 7, 2},
        3,
        "Array with DUPLICATE elements");

    return 0;

}