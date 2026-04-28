#include <cstdio>
int main(void){
    int n;
    scanf("%d", &n);
     
    auto a = 1, b = 3;
    auto c = b;
 
    while(n > 2){
        c = (2 * a + b) % 10007;
        a = b;
        b = c;
        n--;
    }

    printf("%d", (n==1)?a:b);
     
    return 0;
}