#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 40);
    vector<long long> a;

    if (mode == 0) {
        int distinct = rnd.next(1, min(n, 6));
        vector<long long> pool;
        for (int i = 0; i < distinct; ++i) {
            pool.push_back(rnd.next(1, 100));
        }
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else if (mode == 1) {
        long long base = rnd.next(1, 1000);
        long long step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(base + step * i);
        }
    } else if (mode == 2) {
        long long base = rnd.next(1, 1000);
        long long step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(base + step * i);
        }
        reverse(a.begin(), a.end());
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 1) == 0 ? 1LL : 1000000000LL);
        }
    } else if (mode == 4) {
        long long lo = rnd.next(1, 1000000000 - 1000);
        long long hi = lo + rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else {
        n = rnd.next(40, 120);
        for (int i = 0; i < n; ++i) {
            long long value = rnd.next(1, 200);
            if (rnd.next(0, 4) == 0) {
                value = rnd.next(999999900LL, 1000000000LL);
            }
            a.push_back(value);
        }
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
