#include <stdio.h>

int main() {
    for (int t = 0; t < 3; t++) {
        int n;
        scanf("%d", &n);
        __int128 sum = 0;
        for (int i = 0; i < n; i++) {
            long long num;
            scanf("%lld", &num);
            sum += num;
        }
        if (sum == 0)
            printf("0\n");
        else if (sum > 0)
            printf("+\n");
        else
            printf("-\n");
    }
}
