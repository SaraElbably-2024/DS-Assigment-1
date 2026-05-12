#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BitonicSearcher {
private:
    int comparisons;
    int swaps;

    // ====================================================
    // Bubble Sort (Private: because it's a helper for building the array)
    // ====================================================
    void bubbleSort(vector<int>& arr, int start, int end) {
        for (int i = start; i <= end; i++) {
            for (int j = start + 1; j <= end - (i - start); j++) {
                comparisons++;
                if (arr[j] < arr[j - 1]) {
                    swap(arr[j], arr[j - 1]);
                    swaps++;
                }
            }
        }
    }

    // ======================================================
    // Selection Sort (Private)
    // ======================================================
    void selectionSort(vector<int>& arr, int start, int end) {
        for (int i = start; i <= end; i++) {
            int max = i;
            for (int j = i + 1; j <= end; j++) {
                comparisons++;
                if (arr[j] > arr[max]) {
                    max = j;
                }
            }
            if (max != i) {
                swap(arr[i], arr[max]);
                swaps++;
            }
        }
    }

public:
    // Constructor
    BitonicSearcher() : comparisons(0), swaps(0) {}

    // ============================================================
    // Build Bitonic Array
    // ============================================================
    void buildBitonicArray(vector<int>& arr) {
        comparisons = 0; // Reset counters for every new build
        swaps = 0;
        
        int n = (int)arr.size();
        if (n == 0) return;

        int mid = n / 2;
        // النصف الأول (تصاعدي)
        bubbleSort(arr, 0, mid - 1);
        // النصف الثاني (تنازلي)
        selectionSort(arr, mid, n - 1);
    }

    // =========================================================
    // Linear Search
    // =========================================================
    void linearSearch(const vector<int>& arr, int target) {
        bool found = false;
        for (int i = 0; i < (int)arr.size(); i++) {
            if (arr[i] == target) {
                cout << "Result         : FOUND at index " << i << "\n";
                found = true;
                // لم نضع break هنا للتعامل مع العناصر المكررة كما في متطلبات السؤال
            }
        }
        if (!found)
            cout << "Result         : NOT FOUND\n";
    }

    // Getters for metrics
    int getComparisons() const { return comparisons; }
    int getSwaps() const { return swaps; }

    // Helper to print array
    void printArray(const vector<int>& arr) {
        cout << "[ ";
        for (int val : arr)
            cout << val << " ";
        cout << "]" << endl;
    }
};

// ===========================================================
// Test Runner Class (To keep Main clean)
// ===========================================================
class TestManager {
public:
    static void runTest(int testNum, vector<int> arr, int target, string description) {
        BitonicSearcher engine;

        cout << "Test " << testNum << ": " << description << "\n";
        cout << "_______________________________________________________\n";

        cout << "Original array : ";
        engine.printArray(arr);

        engine.buildBitonicArray(arr);

        cout << "Bitonic  array : ";
        engine.printArray(arr);

        int mid = arr.size() / 2;
        cout << "Bitonic  point : index " << mid << " (value = " << (arr.empty() ? 0 : arr[mid]) << ")\n";
        cout << "Comparisons    : " << engine.getComparisons() << "\n";
        cout << "Swaps          : " << engine.getSwaps() << "\n";

        cout << "Searching for  : " << target << "\n";
        engine.linearSearch(arr, target);

        cout << "_______________________________________________________\n\n";
    }
};

int main() {
    
    TestManager::runTest(1, {6, 1, 9, 3, 12, 4, 8}, 12, "Target at the Bitonic Point");
    TestManager::runTest(2, {6, 1, 9, 3, 12, 4, 8}, 6, "Target in the LEFT half (ascending portion)");
    TestManager::runTest(3, {6, 1, 9, 3, 12, 4, 8}, 4, "Target in the RIGHT half (descending portion)");
    TestManager::runTest(4, {6, 1, 9, 3, 12, 4, 8}, 99, "Target NOT present in the array");
    TestManager::runTest(5, {5, 3, 8, 3, 10, 5, 7, 2}, 3, "Array with DUPLICATE elements");

    return 0;
}