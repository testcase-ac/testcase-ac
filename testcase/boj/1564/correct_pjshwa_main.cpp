#include <stdio.h>
#define ll long long int

int main() {
    int n;
    ll result = 1;
    scanf("%d", &n);

    for(ll i=n; i>0; i--) {
        result *= i;

        while(result%10==0) result /= 10;
        result %= 1000000000000LL;
    }
    result %= 100000;

    printf("%05lld", result);
    return 0;
}
