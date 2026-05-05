#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;
//--------------------- Time Complexity : O(n) always
int* nextGreater(int arr[], int n){
    int* res = new int[n]; //Result Array
    fill_n(res, n, -1); // Default Value is -1 for resulrt array
    stack<int> s; //create a stack

    for(int i = 2*n-1; i>=0; i--){ //start from the last to reduce time complexity
        int num = arr[i%n]; // to make the circular array
        while(!s.empty() && s.top() <= num){ // if the top less that or equal num , remove it 
            s.pop();
        }
        if(i<n && !s.empty()){ // 0, 1, 2
            res[i] = s.top(); // push the bigger number in the array
        }

        s.push(num); 
    }
    return res;
}
