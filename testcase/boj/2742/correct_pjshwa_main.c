#include <stdio.h>

int main(void){
    long long int a;
    
    scanf("%lld", &a);
    
    for(long long int i = 0LL; i < a; i++){
        printf("%lld\n", a-i);
    }

    return 0;
}