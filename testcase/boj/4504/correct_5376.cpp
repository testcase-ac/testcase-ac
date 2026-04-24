#include <stdio.h>

int main() {
    int n,i;
    scanf("%d%d", &n,&i);
    while(i != 0) {
        printf("%d is %sa multiple of %d.\n", i, (i%n?"NOT ":""), n);
        scanf("%d", &i);
    }
}
