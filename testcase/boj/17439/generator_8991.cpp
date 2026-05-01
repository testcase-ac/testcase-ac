#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, K;
    vector<int> v;

    auto genV = [&](int n, int pattern) {
        v.assign(n, 0);
        if (pattern == 1) {
            // All equal values
            int x = rnd.next(1, 20);
            for (int i = 0; i < n; ++i) v[i] = x;
        } else if (pattern == 2) {
            // Arithmetic progression with small difference
            int start = rnd.next(1, 20);
            int d = rnd.next(1, 5);
            for (int i = 0; i < n; ++i) v[i] = start + i * d;
        } else if (pattern == 3) {
            // Random non-decreasing with small increments
            int cur = rnd.next(1, 20);
            for (int i = 0; i < n; ++i) {
                v[i] = cur;
                cur += rnd.next(0, 5);
                if (cur > 50000) cur = 50000;
            }
        } else if (pattern == 4) {
            // Clusters with occasional big jumps
            int cur = rnd.next(1, 15);
            for (int i = 0; i < n; ++i) {
                v[i] = cur;
                if (i + 1 == n) break;
                int r = rnd.next(0, 2); // 0,1,2
                if (r == 0) {
                    // keep same
                } else if (r == 1) {
                    cur += rnd.next(1, 3);
                } else {
                    cur += rnd.next(10, 50);
                }
                if (cur > 50000) cur = 50000;
            }
        } else if (pattern == 5) {
            // Values near the upper bound
            int cur = 50000 - rnd.next(0, 100);
            for (int i = 0; i < n; ++i) {
                v[i] = cur;
                cur += rnd.next(0, 3);
                if (cur > 50000) cur = 50000;
            }
        }
    };

    int type = rnd.next(1, 8);

    switch (type) {
        case 1: {
            // Minimal N, random K
            N = 1;
            K = rnd.next(1, 5);
            genV(N, rnd.next(1, 5));
            break;
        }
        case 2: {
            // K = 1, must take whole array as one bouquet
            N = rnd.next(2, 15);
            K = 1;
            genV(N, rnd.next(1, 5));
            break;
        }
        case 3: {
            // K >= N, optimal is all singletons
            N = rnd.next(2, 10);
            int maxK = N + 5;
            if (maxK > 20) maxK = 20;
            K = rnd.next(N, maxK);
            genV(N, rnd.next(1, 5));
            break;
        }
        case 4: {
            // General moderate case
            N = rnd.next(5, 20);
            K = rnd.next(2, N - 1);
            genV(N, rnd.next(1, 5));
            break;
        }
        case 5: {
            // General case with many big jumps
            N = rnd.next(5, 20);
            K = rnd.next(1, N);
            genV(N, 4);
            break;
        }
        case 6: {
            // Maximal N for this generator, values near upper bound
            N = 20;
            K = rnd.next(1, 20);
            genV(N, 5);
            break;
        }
        case 7: {
            // Fixed example from statement
            N = 5;
            K = 3;
            v.clear();
            int a[5] = {1, 1, 5, 6, 9};
            v.assign(a, a + 5);
            break;
        }
        case 8: {
            // All equal values, varying N and K
            N = rnd.next(2, 15);
            K = rnd.next(1, N);
            genV(N, 1);
            break;
        }
    }

    println(N, K);
    println(v);

    return 0;
}
