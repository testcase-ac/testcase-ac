#include <cstdio>

int main(){
    int n;
    scanf("%d", &n);

    int i = 0;
    int squares[317] = {0};
    while(i*i + 2*i + 1 <= n){
        squares[i] = i*i + 2*i + 1;
        i++;
        
    }
    int numbers = 0;
    i--;
    while(i >= 0){
        while(squares[i] <= n){
            n -= squares[i];
            numbers++;
        }
        i--;
    }
    printf("%d", numbers);
}