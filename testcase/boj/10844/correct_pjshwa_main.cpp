#include <cstdio>
 
 
int main(){
     
    int n;
    scanf("%d", &n);
     
    long long int digits[10] = {0}, add[10] = {0};
 
    for(int i = 1; i < 10; i++){
        digits[i] = 1;
    }
 
    for(int i = 2; i <= n; i++){
        add[1] = (digits[0] % 1000000000LL);
        add[8] = (digits[9] % 1000000000LL);
        for(int j = 1; j < 9; j++){
            add[j-1] += (digits[j] % 1000000000LL);
            add[j+1] += (digits[j] % 1000000000LL);
        }
        for(int j = 0; j < 10; j++){
            digits[j] = add[j] % 1000000000LL;
            add[j] = 0;
        }
    }
    long long int sum = 0;
    for(int j = 0; j < 10; j++){
        digits[j] %= 1000000000LL;
        sum += digits[j];
    }
    printf("%lld", sum % 1000000000LL);
}