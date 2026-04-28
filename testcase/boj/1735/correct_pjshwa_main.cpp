#include <cstdio>

int main(){
    int a[2], b[2];
    scanf("%d%d%d%d", &a[0], &a[1], &b[0], &b[1]);
    int c = a[1];
    a[0] *= b[1];
    a[1] *= b[1];
    b[0] *= c;
    b[1] *= c;
    int d = a[0] + b[0];
    c = a[1];
    int temp;
    while(d != c){
        d>c?d-=c:c-=d;
    }
    printf("%d %d", (a[0] + b[0]) / c, a[1] / c);
}