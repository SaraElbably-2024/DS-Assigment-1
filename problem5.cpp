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

 
 
int main() {
    ExpressionEvaluator evaluator;

    cout << "Q1 test:" << endl;
    cout<< evaluator.calculate("1 + 1") << endl;

    cout << evaluator.calculate("2-1 + 2") << endl;

    cout << evaluator.calculate("(1+(4+5+2)-3)+(6+8)") << endl;


     

    return 0;
}