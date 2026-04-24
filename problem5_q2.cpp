//Time: O(n)
//Space: O(n)
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> nextBigNum(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;

    for (int i = 0; i < 2 * n; i++) {
        int num = nums[i % n];

        while (!st.empty() && nums[st.top()] < num) {
            result[st.top()] = num;
            st.pop();
        }

        if (i < n) {
            st.push(i);
        }
    }

    return result;
}

int main() {
    vector<int> nums1 = {1,2,1};
    vector<int> res1 = nextBigNum(nums1);

    for (int x : res1) cout << x << " ";
    cout << endl;  

    vector<int> nums2 = {1,2,3,4,3};
    vector<int> res2 = nextBigNum(nums2);

    for (int x : res2) 
    cout << x << " ";
    
}