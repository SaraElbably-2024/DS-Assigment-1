#include <iostream>
#include <vector>  

using namespace std;

class RotatedArraySearcher {
private:
    int totalComparisons;

public:
    RotatedArraySearcher() : totalComparisons(0) {}

    int search(const vector<int>& nums, int target) {
        totalComparisons = 0;
        int low = 0, high = (int)nums.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            totalComparisons++;
            if (nums[mid] == target) return mid;

            totalComparisons += 2; 
            if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
                low++;
                high--;
                continue;
            }

            totalComparisons++;
            if (nums[low] <= nums[mid]) {
                totalComparisons += 2;
                if (nums[low] <= target && target < nums[mid]) high = mid - 1;
                else low = mid + 1;
            } else {
                totalComparisons += 2;
                if (nums[mid] < target && target <= nums[high]) low = mid + 1;
                else high = mid - 1;
            }
        }
        return -1;
    }

    int getComparisonsCount() const {
        return totalComparisons;
    }
};

int main() {
    int n, target;
    cout << "Enter size: ";
    if (!(cin >> n)) return 0;

    vector<int> nums(n); // بديل آمن لـ int arr[n]
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Enter target: ";
    cin >> target;

    RotatedArraySearcher searcher;
    int index = searcher.search(nums, target);

    if (index != -1) cout << "Index: " << index << endl;
    else cout << "Not found" << endl;

    cout << "Comparisons: " << searcher.getComparisonsCount() << endl;

    return 0;
}