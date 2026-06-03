#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a = {rnd.next(0, 1000000)};
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int value = rnd.next(0, 30);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 18);
        a.resize(n);
        int value = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            value += rnd.next(0, 7);
            a[i] = value;
        }
    } else if (mode == 3) {
        n = rnd.next(3, 18);
        a.resize(n);
        int value = rnd.next(0, 80);
        for (int i = 0; i < n; ++i) {
            value = max(0, value - rnd.next(0, 7));
            a[i] = value;
        }
    } else if (mode == 4) {
        n = rnd.next(4, 20);
        a.assign(n, rnd.next(1, 12));
        int dips = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < dips; ++i) {
            a[rnd.next(n)] = rnd.next(0, 2);
        }
    } else if (mode == 5) {
        n = rnd.next(4, 20);
        a.assign(n, rnd.next(0, 5));
        int spikes = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < spikes; ++i) {
            a[rnd.next(n)] = rnd.next(100000, 1000000);
        }
    } else if (mode == 6) {
        n = rnd.next(5, 24);
        a.resize(n);
        int blockValue = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            if (i == 0 || rnd.next(100) < 35) {
                blockValue = rnd.next(0, 50);
            }
            a[i] = blockValue;
        }
    } else {
        n = rnd.next(2, 24);
        a.resize(n);
        int lo = rnd.next(0, 20);
        int hi = rnd.next(lo, lo + rnd.next(0, 80));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
        }
    }

    println(n);
    bool wrap = n > 2 && rnd.next(100) < 30;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            if (wrap && rnd.next(100) < 20) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
        printf("%d", a[i]);
    }
    printf("\n");

    return 0;
}
