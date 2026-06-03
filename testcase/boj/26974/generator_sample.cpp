#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000LL;

    int mode = rnd.next(6);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 5) {
        n = rnd.next(12, 28);
    } else {
        n = rnd.next(2, 14);
    }

    vector<long long> a(n, 0);

    if (mode == 0) {
        long long value = rnd.next(0LL, LIM);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        long long cur = rnd.next(0LL, 1000LL);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0LL, 20LL);
            a[i] = cur;
        }
    } else if (mode == 2) {
        long long cur = rnd.next(0LL, LIM);
        a[0] = cur;
        for (int i = 1; i < n; ++i) {
            long long step = rnd.next(0LL, 1000000LL);
            if (rnd.next(2) == 0) {
                cur = max(0LL, cur - step);
            } else {
                cur = min(LIM, cur + step);
            }
            a[i] = cur;
        }
    } else if (mode == 3) {
        long long low = rnd.next(0LL, 1000LL);
        long long high = rnd.next(LIM - 1000LL, LIM);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a[i] = low + rnd.next(0LL, 5LL);
            } else {
                a[i] = high - rnd.next(0LL, 5LL);
            }
        }
    } else if (mode == 4) {
        long long cur = rnd.next(0LL, 100000LL);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(100) < 45) {
                cur = min(LIM, cur + rnd.next(0LL, 50LL));
            }
            a[i] = cur;
        }
        shuffle(a.begin(), a.end());
    } else {
        long long floor = rnd.next(0LL, 100LL);
        long long ceiling = rnd.next(LIM - 100LL, LIM);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(100);
            if (pick < 25) {
                a[i] = floor;
            } else if (pick < 50) {
                a[i] = ceiling;
            } else {
                a[i] = rnd.next(0LL, 1000000LL);
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        long long mn = a[i];
        long long mx = a[i];
        for (int j = i; j < n; ++j) {
            mn = min(mn, a[j]);
            mx = max(mx, a[j]);
            if (j > i) {
                printf(" ");
            }
            printf("%lld", mx - mn);
        }
        printf("\n");
    }

    return 0;
}
