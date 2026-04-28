#include <iostream>
 
int main(){
    int a[5] = {0};
    for(auto &x : a){
        std::cin >> x;
    }
    int sum = 0;
    for(auto &x : a){
        sum += (x<40)?40:x;
    }
    std::cout << sum / 5;
     
    return 0;
}