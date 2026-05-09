#include<iostream>
#include<vector>
using namespace std;

class RotatedArraySearch {
private:
    vector<int> arr;
    int comparisons;

public:
    RotatedArraySearch() : comparisons(0) {}
    void inputArray() {
        int n;
        cout << "Enter the array size: ";
        cin >> n;
        arr.resize(n);
        cout << "Enter array elements: ";
        for (int i = 0; i < n; i++)
            cin >> arr[i];
    }
    int search(int target) {
        comparisons = 0;
        int low = 0, high = arr.size() - 1;

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
            } else {
                comparisons++;
                if (arr[mid] < target && target <= arr[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return -1;
    }
    void displayResult(int target) {
        int result = search(target);
        cout << "Index: " << result << endl;
        cout << "Comparisons: " << comparisons << endl;
    }

    // Getter for comparisons
    int getComparisons() {
        return comparisons;
    }
};

int main() {
    RotatedArraySearch searcher;
    searcher.inputArray();
    int target;
    cout << "Enter target value: ";
    cin >> target;

    searcher.displayResult(target);

    return 0;
}


//Best Case:O(1)
//Worst Case:O(n)


// [5, 6, 7, 1, 2, 3, 4],  target = 7   → index 2  (الـ peak نفسه)
//  [5, 6, 7, 1, 2, 3, 4],  target = 5   → index 0  (أول عنصر)
//  [5, 6, 7, 1, 2, 3, 4],  target = 4   → index 6  (آخر عنصر)
//  [5, 6, 7, 1, 2, 3, 4],  target = 9   → -1        (مش موجود)

//  [1],                     target = 1   → index 0  (عنصر واحد، موجود)
//  [1],                     target = 5   → -1        (عنصر واحد، مش موجود)
//  [2, 1],                  target = 1   → index 1  (array صغيرة متدورة)
//  [1, 2, 3, 4, 5],        target = 3   → index 2  (مش متدورة خالص)
