//for 2 questions
//Time: O(n)
//Space: O(n)

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

//  ----------- Question 1 --------------
class ExpressionEvaluator {
public:
    int calculate(const string& s) {
        stack<int> st;
        int result = 0, number = 0, sign = 1;

        for (char c : s) {
            if (isdigit(c)) {
                number = number * 10 + (c - '0');
            }
            else if (c == '+') {
                result += sign * number;
                number = 0;
                sign = 1;
            }
            else if (c == '-') {
                result += sign * number;
                number = 0;
                sign = -1;
            }
            else if (c == '(') {
                st.push(result);
                st.push(sign);
                result = 0;
                sign = 1;
            }
            else if (c == ')') {
                result += sign * number;
                number = 0;

                result *= st.top(); st.pop();
                result += st.top(); st.pop();
            }
        }

        result += sign * number;
        return result;
    }
};

// ------------- Question 2 -------------
class nextGreaterNum {
public:
    vector<int> solve(const vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);
        stack<int> st;

        for (int i = 0; i < 2 * n; i++) {
            int current = nums[i % n];

            while (!st.empty() && nums[st.top()] < current) {
                result[st.top()] = current;
                st.pop();
            }

            if (i < n) {
                st.push(i);
            }
        }

        return result;
    }
};

 
int main() {
    ExpressionEvaluator evaluator;

    cout << "Q1 test:" << endl;
    cout<< evaluator.calculate("1 + 1") << endl;

    cout << evaluator.calculate("2-1 + 2") << endl;

    cout << evaluator.calculate("(1+(4+5+2)-3)+(6+8)") << endl;


    nextGreaterNum nge;

    cout << " Q2 test:" << endl;

    vector<int> nums1 = {1, 2, 1};

    vector<int> res1 = nge.solve(nums1);

     
    for (int x : res1) cout << x << " ";
    cout << endl;

    vector<int> nums2 = {1, 2, 3, 4, 3};

    vector<int> res2 = nge.solve(nums2);

  
    for (int x : res2) cout << x << " ";
    cout << endl;

    return 0;
}