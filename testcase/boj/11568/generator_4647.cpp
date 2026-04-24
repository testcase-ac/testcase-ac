#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size
    int N = rnd.next(1, 10);
    // Choose a pattern
    int mode = rnd.next(0, 4);
    vector<int> a(N);

    switch (mode) {
        // 0: random distinct values
        case 0: {
            int range = rnd.next(N, max(N, 20));
            vector<int> pool(range);
            for (int i = 0; i < range; i++) pool[i] = i + 1;
            shuffle(pool.begin(), pool.end());
            for (int i = 0; i < N; i++) a[i] = pool[i];
            break;
        }
        // 1: strictly increasing
        case 1: {
            int cur = rnd.next(1, 10);
            for (int i = 0; i < N; i++) {
                a[i] = cur;
                cur += rnd.next(1, 5);
            }
            break;
        }
        // 2: strictly decreasing
        case 2: {
            int cur = rnd.next(N * 2, N * 5 + 10);
            for (int i = 0; i < N; i++) {
                a[i] = cur;
                cur -= rnd.next(1, 5);
                if (cur < 1) cur = 1;
            }
            break;
        }
        // 3: many duplicates (small value range)
        case 3: {
            int r = rnd.next(1, min(N, 5));
            for (int i = 0; i < N; i++) {
                a[i] = rnd.next(1, r);
            }
            break;
        }
        // 4: bitonic (first increasing then decreasing)
        case 4: {
            if (N < 3) {
                for (int i = 0; i < N; i++) a[i] = rnd.next(1, 100);
            } else {
                int p = rnd.next(1, N - 2);
                int peak = rnd.next(p + 1, p + 30);
                // increasing part
                for (int i = 0; i <= p; i++) {
                    a[i] = peak - (p - i);
                }
                // decreasing part
                for (int i = p + 1; i < N; i++) {
                    a[i] = peak - (i - p);
                    if (a[i] < 1) a[i] = 1;
                }
            }
            break;
        }
    }

    // Output
    println(N);
    println(a);

    return 0;
}
