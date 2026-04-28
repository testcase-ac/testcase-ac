#include <cstdio>

int main(){
    int n, c, a = 1, b = 2;
    scanf("%d", &n);
    int i = n - 2;
    while(i > 0){
        c = (a+b)%15746;
        a = b;
        b = c;
        i--;
    }
    printf("%d", (n==2)?2:(n==1)?1:c);
}