#include <cstdio>

int main() {
    for (;;) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        int a, b;
        scanf("%d%d", &a, &b);
        int slw = 0;
        int fst = 0;
        int lim = 1;
        int dist = 0;
        for (;;) {
            fst = 1LL * fst * fst % n * a % n + b;
            fst %= n;
            ++dist;
            if (slw == fst) break;
            if (dist == lim) {
                lim *= 2;
                dist = 0;
                slw = fst;
            }
        }
        int ans = n - dist;
        printf("%d\n", ans);
    }

    return 0;
}
