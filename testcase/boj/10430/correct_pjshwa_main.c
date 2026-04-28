#include <stdio.h>

int main(void){
    long long int a,b,c;

    scanf("%lld %lld %lld", &a, &b, &c);

    printf("%lld\n", (a+b)%c);
    printf("%lld\n", (a%c + b%c)%c);
    printf("%lld\n", (a*b)%c);
    printf("%lld", (a%c * b%c)%c);
}