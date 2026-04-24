#include<iostream>
using namespace std;
int rotatedBinarySearch(int arr[], int n, int target, int &comparisons) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        comparisons++;
        if (arr[mid] == target)
            return mid;

        comparisons += 2;
        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low++;
            high--;
            continue;
        }

        comparisons++;
        if (arr[low] <= arr[mid]) {
            comparisons++;
            if (arr[low] <= target && target < arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        else {
            comparisons++; 
            if (arr[mid] < target && target <= arr[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }

    return -1;
}

int main() {
    int n;
    cout << "inter the array size" << endl;
    cin>>n;
    int arr[n] ;
    cout << "enter array elements" << endl;
    for(int i=0;i<n;i++) {
        cin>>arr[i];
    }
    int target ;
    cout<<"enter target value"<<endl;
    cin>>target;
    int comparisons = 0;
    int result = rotatedBinarySearch(arr, n, target, comparisons);
    cout << "Index: " << result << endl;
    cout << "Comparisons: " << comparisons << endl;

    return 0;
}