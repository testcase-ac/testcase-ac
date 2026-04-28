#include <cstdio>

int main(){
    long long int n;
    scanf("%lld", &n);
    printf("%lld", ((3*n*n+5*n+2)/2)%45678);
}
