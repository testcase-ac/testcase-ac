#include <stdio.h>

int main() {
    int s=0, t, c=4;
    while(c--) {
        scanf("%d", &t);
        s += t;
    }
    printf("%d\n%d", s/60, s%60);
}
