#include <iostream>
#include <string>
int main(){
    int n;
    std::cin >> n;
    std::string paren_string;
    for(int i = 0; i < n; i++){
        std::cin >> paren_string;
        int points = 0;
        int streak = 1;
        for(auto it = paren_string.begin(); it != paren_string.end(); it++){
            if(*it == 'O'){
                points += (streak++);
            }
            else{
                streak = 1;
            }
        }
        std::cout << points <<'\n';

    }
     
     
}