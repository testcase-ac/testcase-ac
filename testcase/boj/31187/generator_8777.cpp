#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T;
    int dice = rnd.next(0, 9);
    if (dice < 3) T = 1;
    else if (dice < 7) T = rnd.next(2, 4);
    else T = rnd.next(5, 7);

    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int scenario = rnd.next(0, 8);
        int n;
        vector<long long> a;

        switch (scenario) {
            case 0: { // n = 1, edge values
                n = 1;
                a.resize(n);
                int kind = rnd.next(0, 5);
                if (kind == 0) a[0] = 0;
                else if (kind == 1) a[0] = 1;
                else if (kind == 2) a[0] = -1;
                else if (kind == 3) a[0] = 1000000000LL;
                else if (kind == 4) a[0] = -1000000000LL;
                else a[0] = rnd.next(-10, 10);
                break;
            }
            case 1: { // very small random
                n = rnd.next(2, 6);
                a.resize(n);
                for (int i = 0; i < n; ++i)
                    a[i] = rnd.next(-10, 10);
                break;
            }
            case 2: { // small-medium with both signs if possible
                n = rnd.next(3, 10);
                a.resize(n);
                bool hasPos = false, hasNeg = false;
                for (int i = 0; i < n; ++i) {
                    a[i] = rnd.next(-20, 20);
                    if (a[i] > 0) hasPos = true;
                    if (a[i] < 0) hasNeg = true;
                }
                if (!hasPos) a[rnd.next(0, n - 1)] = rnd.next(1, 20);
                if (!hasNeg) a[rnd.next(0, n - 1)] = -rnd.next(1, 20);
                break;
            }
            case 3: { // alternating signs
                n = rnd.next(2, 12);
                a.resize(n);
                bool startPos = rnd.next(0, 1);
                for (int i = 0; i < n; ++i) {
                    long long val = rnd.next(1, 20);
                    bool pos = ((i % 2) == 0) ? startPos : !startPos;
                    if (!pos) val = -val;
                    if (rnd.next(0, 6) == 0) val = 0; // occasional zero
                    a[i] = val;
                }
                break;
            }
            case 4: { // all positive, possibly with huge values
                n = rnd.next(2, 15);
                a.resize(n);
                int bigPosIdx = rnd.next(0, n - 1);
                for (int i = 0; i < n; ++i) {
                    if (i == bigPosIdx && rnd.next(0, 3) == 0)
                        a[i] = rnd.next(100000000, 1000000000);
                    else
                        a[i] = rnd.next(1, 50);
                }
                break;
            }
            case 5: { // all negative, possibly with huge values
                n = rnd.next(2, 15);
                a.resize(n);
                int bigNegIdx = rnd.next(0, n - 1);
                for (int i = 0; i < n; ++i) {
                    if (i == bigNegIdx && rnd.next(0, 3) == 0)
                        a[i] = -rnd.next(100000000, 1000000000);
                    else
                        a[i] = -rnd.next(1, 50);
                }
                break;
            }
            case 6: { // many zeros, small mix
                n = rnd.next(2, 15);
                a.assign(n, 0);
                int nonZeroCnt = rnd.next(1, max(1, n / 2));
                for (int i = 0; i < nonZeroCnt; ++i) {
                    int idx = rnd.next(0, n - 1);
                    long long v = rnd.next(-5, 5);
                    if (v == 0) v = (rnd.next(0, 1) ? 1 : -1);
                    a[idx] = v;
                }
                break;
            }
            case 7: { // larger n, mixed, moderate magnitudes
                n = rnd.next(16, 30);
                a.resize(n);
                for (int i = 0; i < n; ++i) {
                    if (rnd.next(0, 9) == 0)
                        a[i] = rnd.next(-1000000000, 1000000000);
                    else
                        a[i] = rnd.next(-100, 100);
                }
                break;
            }
            case 8: { // even n, all same sign except one
                vector<int> evens = {2, 4, 6, 8, 10, 12, 14};
                n = evens[rnd.next(0, (int)evens.size() - 1)];
                a.resize(n);
                bool majorityPos = rnd.next(0, 1);
                int special = rnd.next(0, n - 1);
                for (int i = 0; i < n; ++i) {
                    if (i == special) continue;
                    long long v = rnd.next(1, 20);
                    a[i] = majorityPos ? v : -v;
                }
                long long spv;
                if (majorityPos)
                    spv = - (long long)rnd.next(1, 20);
                else
                    spv = (long long)rnd.next(1, 20);
                if (rnd.next(0, 4) == 0) {
                    long long mag = rnd.next(100000000, 1000000000);
                    spv = (spv > 0 ? mag : -mag);
                }
                a[special] = spv;
                break;
            }
        }

        println(n);
        println(a);
    }

    return 0;
}
