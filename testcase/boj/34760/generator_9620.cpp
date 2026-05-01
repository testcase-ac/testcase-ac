#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> a(15);
    int type = rnd.next(0, 7);

    switch (type) {
        case 0: {
            // Sample 1 from statement
            long long tmp[15] = {4, 5, 1, 2, 2, 4, 2, 3, 1, 5, 3, 2, 2, 4, 1};
            for (int i = 0; i < 15; ++i) a[i] = tmp[i];
            break;
        }
        case 1: {
            // Sample 2 from statement
            long long tmp[15] = {3, 2, 1, 4, 4, 4, 2, 3, 1, 3, 2, 2, 4, 1, 5};
            for (int i = 0; i < 15; ++i) a[i] = tmp[i];
            break;
        }
        case 2: {
            // All equal
            long long K = rnd.next(1, 20);
            for (int i = 0; i < 15; ++i) a[i] = K;
            break;
        }
        case 3: {
            // Strictly increasing, last is unique maximum
            long long cur = rnd.next(1, 10);
            for (int i = 0; i < 15; ++i) {
                a[i] = cur;
                if (i != 14) cur += rnd.next(1, 5);
            }
            break;
        }
        case 4: {
            // Random, last not strictly greater than prefix maximum (A15 <= preMax)
            long long preMax = 0;
            for (int i = 0; i < 14; ++i) {
                a[i] = rnd.next(1, 50);
                if (a[i] > preMax) preMax = a[i];
            }
            if (preMax == 0) preMax = 1;
            a[14] = rnd.next(1, (int)preMax); // ensures A15 <= preMax
            break;
        }
        case 5: {
            // Random, last is unique global maximum (A15 > preMax)
            long long preMax = 0;
            for (int i = 0; i < 14; ++i) {
                a[i] = rnd.next(1, 50);
                if (a[i] > preMax) preMax = a[i];
            }
            long long add = rnd.next(1, 10);
            a[14] = preMax + add; // <= 60, well within bounds
            break;
        }
        case 6: {
            // Max value appears multiple times, including last (A15 == preMax, not strictly >)
            long long M = rnd.next(5, 60);
            for (int i = 0; i < 14; ++i) {
                a[i] = rnd.next(1, (int)M);
            }
            int pos = rnd.next(0, 13);
            a[pos] = M; // ensure prefix max is M
            a[14] = M;
            break;
        }
        case 7: {
            // General random, mixed small/large ranges
            bool smallRange = (rnd.next(0, 9) < 7); // 70% small, 30% large
            long long lo = 1;
            long long hi = smallRange ? 50 : 1000000000LL;
            for (int i = 0; i < 15; ++i) {
                a[i] = rnd.next((int)lo, (int)hi);
            }
            break;
        }
    }

    println(a);
    return 0;
}
