#include <stdio.h>

int main(void){
    long long int a, b;
    scanf("%lld %lld", &a, &b);
    printf("%lld\n%lld\n%lld\n%lld\n%lld", a+b, a-b, a*b, a/b, a%b);

    return 0;

}