//Time: O(n)
//Space: O(n)
#include <iostream>
#include <stack>
using namespace std;

int calculate(string s) {
    stack<int> st;
    int result = 0, number = 0, sign = 1;

    for (int i = 0; i < s.size(); i++) {
        char c = s[i];

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

int main() {
    cout << calculate("1 + 1") << endl;              
    cout << calculate("2-1 + 2") << endl;            
    cout << calculate("(1+(4+5+2)-3)+(6+8)") << endl;
}