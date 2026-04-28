#include <iostream>
using namespace std;
    
int main(){
    int n;
    cin >> n;
    char stars[2*n] = {0};
        
    for(int i = 0; i < 2*n - 1; i++){
        stars[i] = 42;
    }
    for(int i = 0; i < n; i++){
        cout << stars << '\n';
        stars[2*n - 2 - i] = 0;
        stars[i] = 32;
    }

    return 0;
}