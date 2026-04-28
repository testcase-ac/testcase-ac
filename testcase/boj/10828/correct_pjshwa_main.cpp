#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main(){
    int n;
    cin >> n;

    stack<int> int_stack;

    string order;
    int parameter;
    for(int i = 0; i < n; i++){
        cin >> order;
        if(order == "push"){
            cin >> parameter;
            int_stack.push(parameter);
        }
        else if(order == "pop"){
            if(int_stack.empty()) cout << -1 << '\n';
            else{
                cout << int_stack.top() << '\n';
                int_stack.pop();
            }
        }
        else if(order == "size"){
            cout << int_stack.size() << '\n';
        }
        else if(order == "empty"){
            cout << (int_stack.empty()?1:0) << '\n';
        }
        else if(order == "top"){
            if(int_stack.empty()) cout << -1 << '\n';
            else{
                cout << int_stack.top() << '\n';
            }
        }
    }
}