#include <stdio.h>

int main(void){
    long long int n;
    
    scanf("%lld", &n);

    int seconds = 0;
    long long int deduction = 1LL;

    while(n > 0){
    	n -= deduction;
    	deduction++;
    	seconds++;
    	if(n - deduction < 0) deduction = 1LL;
    }

    printf("%d", seconds);
}