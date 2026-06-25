#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 100000;
    const int MAX_A = 1000000000;

    int mode = rnd.next(0, 7);
    int n;
    int k;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        k = rnd.next(1, MAX_A);
        a.push_back(rnd.any(vector<int>{1, rnd.next(1, 20), MAX_A}));
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        k = 1;
        int hi = rnd.any(vector<int>{rnd.next(1, 100), rnd.next(MAX_A - 1000, MAX_A)});
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, hi));
        }
        a[rnd.next(n)] = hi;
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        k = rnd.next(2, 12);
        int base = rnd.next(1, 80);
        for (int i = 0; i < n; ++i) {
            int q = rnd.next(0, 12);
            int rem = rnd.next(0, k - 2);
            a.push_back(min(MAX_A, base + q * (k - 1) + rem));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 40);
        k = rnd.next(2, 1000000000);
        int t = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            long long extra = 1LL * rnd.next(0, 4) * (k - 1) + rnd.next(0, max(0, k - 2));
            a.push_back((int)min<long long>(MAX_A, 1LL * t + extra));
        }
        a[rnd.next(n)] = min(MAX_A, t + k - 1);
    } else if (mode == 4) {
        n = rnd.next(10, 80);
        k = rnd.next(2, 1000);
        int lo = rnd.next(1, 1000);
        int hi = rnd.next(lo, min(MAX_A, lo + rnd.next(0, 20000)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 5) {
        n = rnd.next(5, 60);
        k = rnd.next(2, MAX_A);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(vector<int>{
                1,
                rnd.next(1, 1000),
                rnd.next(MAX_A - 100000, MAX_A),
                MAX_A
            }));
        }
    } else if (mode == 6) {
        n = rnd.next(5000, MAX_N);
        k = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 100000));
        }
    } else {
        n = rnd.next(2, 50);
        k = MAX_A;
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(max(1, MAX_A - 1000000), MAX_A));
        }
    }

    if (rnd.next(2)) {
        shuffle(a.begin(), a.end());
    } else {
        sort(a.begin(), a.end());
    }

    println(n);
    println(a);
    println(k);

    return 0;
}
