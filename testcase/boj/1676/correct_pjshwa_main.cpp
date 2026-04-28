#include <cstdio>

int main(){
    int n;
    scanf("%d", &n);
    
    int zeros = 0;
    for(int i = 5; i <= n; i+=5){
        int temp = i;
        while(temp % 5 == 0){
            zeros++;
            temp /=5;
        }
    }
    printf("%d", zeros);
}
