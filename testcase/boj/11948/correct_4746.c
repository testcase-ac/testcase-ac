#include <stdio.h>
int main() {
    int t, s=0, m1=100, m2=100;
    for(int i=0; i<4; i++) scanf("%d", &t), m1=m1<t?m1:t, s += t;
    for(int i=0; i<2; i++) scanf("%d", &t), m2=m2<t?m2:t, s += t;
    printf("%d", s-m1-m2);
}
