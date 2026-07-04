#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 25);
    long long d = rnd.next(1, 1000000000);
    vector<long long> sizes;

    if (mode == 0) {
        d = rnd.next(1, 30);
        long long base = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            sizes.push_back(base + rnd.next(0, static_cast<int>(d)));
        }
    } else if (mode == 1) {
        d = rnd.next(1, 20);
        long long cur = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            sizes.push_back(cur);
            cur += d + rnd.next(1, 20);
        }
    } else if (mode == 2) {
        d = rnd.next(1, 100);
        int distinct = rnd.next(1, min(n, 5));
        vector<long long> pool;
        long long base = rnd.next(1, 1000000);
        for (int i = 0; i < distinct; ++i) {
            pool.push_back(base + rnd.next(0, static_cast<int>(d)));
        }
        for (int i = 0; i < n; ++i) {
            sizes.push_back(rnd.any(pool));
        }
    } else if (mode == 3) {
        d = rnd.next(1, 50);
        int clusters = rnd.next(2, min(n, 5));
        vector<long long> bases;
        long long cur = rnd.next(1, 1000);
        for (int i = 0; i < clusters; ++i) {
            bases.push_back(cur);
            cur += d + rnd.next(1, 100);
        }
        for (int i = 0; i < n; ++i) {
            long long base = rnd.any(bases);
            sizes.push_back(base + rnd.next(0, static_cast<int>(d)));
        }
    } else {
        d = rnd.next(900000000, 1000000000);
        long long lo = rnd.next(1, 100);
        long long hi = rnd.next(999999900, 1000000000);
        for (int i = 0; i < n; ++i) {
            sizes.push_back(rnd.next(0, 1) == 0 ? lo + rnd.next(0, 100) : hi - rnd.next(0, 100));
        }
    }

    shuffle(sizes.begin(), sizes.end());

    println(n, d);
    println(sizes);
    return 0;
}
