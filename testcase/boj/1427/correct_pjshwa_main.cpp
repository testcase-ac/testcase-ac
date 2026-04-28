#include <cstdio>
#include <algorithm>

int main(){
    int a[11];
    int digits = 0;
    int o_n;
    scanf("%d", &o_n);
    while(o_n != 0){
        a[digits++] = o_n % 10;
        o_n /= 10;
    }
    std::sort(a, a+digits, [](int x, int y){return x > y;});
    for(int i = 0; i < digits; i++){
        printf("%d", a[i]);
    }
    return 0;
}