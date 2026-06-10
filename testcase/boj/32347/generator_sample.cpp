#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(3, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 20);
    } else {
        n = rnd.next(8, 40);
    }

    int k;
    if (mode == 0) {
        k = rnd.next(2, n - 1);
    } else if (mode == 2) {
        k = rnd.next(max(2, n / 3), n - 1);
    } else if (mode == 3) {
        k = rnd.next(2, min(n - 1, 5));
    } else {
        k = rnd.next(2, n - 1);
    }

    vector<int> a(n + 1, 0);
    a[n] = 1;

    if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            a[i] = 1;
        }
    } else if (mode == 2) {
        int start = rnd.next(1, max(1, n / 2));
        for (int i = start; i <= n; ++i) {
            a[i] = rnd.next(0, 3) != 0;
        }
    } else if (mode == 3) {
        int gap = rnd.next(2, min(8, n - 1));
        for (int i = n; i >= 1; i -= gap) {
            a[i] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 9) == 0) {
                a[i] = 1;
            }
        }
    } else if (mode == 4) {
        int parity = rnd.next(0, 1);
        for (int i = 1; i <= n; ++i) {
            a[i] = (i % 2 == parity);
            if (rnd.next(0, 7) == 0) {
                a[i] ^= 1;
            }
        }
    } else {
        for (int i = 1; i < n; ++i) {
            a[i] = rnd.next(0, 4) == 0;
        }
    }
    a[n] = 1;

    println(n, k);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            printf(" ");
        }
        printf("%d", a[i]);
    }
    printf("\n");

    return 0;
}
