#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeValues(int n, int mode) {
    vector<int> a(n);

    if (mode == 0) {
        int start = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a[i] = start + i;
        }
    } else if (mode == 1) {
        int start = rnd.next(n, n + 30);
        for (int i = 0; i < n; ++i) {
            a[i] = start - i;
        }
    } else if (mode == 2) {
        int distinct = rnd.next(1, min(n, 6));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, distinct);
        }
    } else if (mode == 3) {
        int start = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            a[i] = start + i;
        }
        int shift = rnd.next(0, n - 1);
        rotate(a.begin(), a.begin() + shift, a.end());
    } else if (mode == 4) {
        int start = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            a[i] = start + i / rnd.next(1, 3);
        }
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            swap(a[rnd.next(n)], a[rnd.next(n)]);
        }
    } else {
        int hi = rnd.any(vector<int>{10, 100, 1000000000});
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, hi);
        }
    }

    if (rnd.next(4) == 0) {
        a[rnd.next(n)] = 1000000000;
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int p = rnd.next(3, 8);
    println(p);

    for (int tc = 0; tc < p; ++tc) {
        int k = rnd.next(0, 1000000000);
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 35);
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = rnd.next(10, 25);
        }

        vector<int> a = makeValues(n, mode);

        println(k, n);
        for (int i = 0; i < n; ++i) {
            if (i % 10) {
                printf(" ");
            }
            printf("%d", a[i]);
            if (i % 10 == 9 || i == n - 1) {
                printf("\n");
            }
        }
    }

    return 0;
}
