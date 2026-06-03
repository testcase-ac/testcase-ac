#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    vector<long long> a;

    if (mode == 0) {
        long long x = rnd.next(1LL, 1000000000LL);
        a.assign(n, x);
    } else if (mode == 1) {
        int distinct = rnd.next(1, min(n, 8));
        vector<long long> pool;
        long long base = rnd.next(1LL, 999999900LL);
        for (int i = 0; i < distinct; ++i) {
            pool.push_back(base + i);
        }
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        long long start = rnd.next(1LL, 999999000LL);
        long long step = rnd.next(1LL, 10LL);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + step * i);
        }
    } else if (mode == 3) {
        long long center = rnd.next(2LL, 999999999LL);
        for (int i = 0; i < n; ++i) {
            a.push_back(center + rnd.next(-1LL, 1LL));
        }
    } else if (mode == 4) {
        int blocks = rnd.next(2, min(n + 1, 10));
        long long value = rnd.next(1LL, 999999000LL);
        for (int b = 0; b < blocks && (int)a.size() < n; ++b) {
            int remaining = n - (int)a.size();
            int count = (b + 1 == blocks) ? remaining : rnd.next(1, remaining);
            for (int i = 0; i < count; ++i) {
                a.push_back(value);
            }
            value += rnd.next(1LL, 20LL);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1LL, 1000000000LL));
        }
    }

    if (rnd.next(0, 2) == 0) {
        shuffle(a.begin(), a.end());
    } else if (rnd.next(0, 1) == 0) {
        sort(a.begin(), a.end());
    } else {
        sort(a.rbegin(), a.rend());
    }

    println(n);
    println(a);

    return 0;
}
