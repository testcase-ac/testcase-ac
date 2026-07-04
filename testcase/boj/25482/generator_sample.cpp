#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<long long> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.any(vector<long long>{-1000000000LL, -1LL, 0LL, 1LL, 1000000000LL}));
    } else {
        n = rnd.next(2, mode == 5 ? 30 : 12);
        a.resize(n);

        if (mode == 1) {
            long long lo = rnd.next(-10, 0);
            long long hi = rnd.next(0, 10);
            for (int i = 0; i < n; ++i) {
                a[i] = rnd.next(lo, hi);
            }
        } else if (mode == 2) {
            for (int i = 0; i < n; ++i) {
                long long x = rnd.next(1, 1000);
                a[i] = (i % 2 == 0 ? x : -x);
            }
            shuffle(a.begin(), a.end());
        } else if (mode == 3) {
            vector<long long> pool = {-1000000000LL, -1000000LL, -1LL, 0LL,
                                      1LL, 1000000LL, 1000000000LL};
            for (int i = 0; i < n; ++i) {
                a[i] = rnd.any(pool);
            }
        } else if (mode == 4) {
            for (int i = 0; i < n; ++i) {
                if (rnd.next(0, 3) == 0) {
                    a[i] = 0;
                } else {
                    long long x = rnd.next(1, 25);
                    a[i] = rnd.next(0, 1) ? x : -x;
                }
            }
        } else {
            long long base = rnd.next(-1000000, 1000000);
            for (int i = 0; i < n; ++i) {
                a[i] = base + rnd.next(-20, 20);
            }
        }
    }

    println(n);
    println(a);
    return 0;
}
