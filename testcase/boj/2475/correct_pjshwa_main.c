#include <stdio.h>

int main(void){
    int a[5];
    int temp = 0;
    for(int i = 0; i < 5; i++){
        scanf("%d", &a[i]);
        temp += (a[i]*a[i]);
    }
    
    printf("%d", temp % 10);
    
    return 0;
}