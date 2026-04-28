#include <iostream>
#include <stack>
#include <string>
int main(){
    int n;
    std::cin >> n;
    std::string paren_string;
    char no[] = "NO";
    char yes[] = "YES";
    for(int i = 0; i < n; i++){
        std::cin >> paren_string;
        std::stack<int> paren_stack;
        int size = paren_string.size();
        int error = 0;
        for(auto it = paren_string.begin(); it != paren_string.end(); it++){
            if(*it == '('){
                paren_stack.push(1);
            }
            else{
                if(paren_stack.empty()){
                    error = 1;
                    break;
                }
                else paren_stack.pop();
            }
        }
        if(!paren_stack.empty()) error = 1;
        if(error) std::cout << "NO\n";
        else std::cout << "YES\n";
    }
    
    
}