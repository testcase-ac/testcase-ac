#include <cstdio>
int power_10(int base, int x){
    for(int i = 0; i < x; i++){
        base *= 10;
    }
    return base;
}

int rev(int x){
    int temp = x;
    int a[5];
    int digits = 0;
    while(temp != 0){
        a[digits] = temp % 10;
        temp /= 10;
        digits++;
    }
    temp = 0;
    for(int i = 0; i < digits; i++){
        temp += power_10(a[i], digits-i-1);
    }
    return temp;    
}

int main(){
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d", rev(rev(x)+rev(y)));
}