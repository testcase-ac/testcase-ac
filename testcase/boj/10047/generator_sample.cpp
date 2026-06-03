#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(3, 8);
        long long base = rnd.next(1, 20);
        a.assign(n, base);
        for (long long& x : a) {
            x += rnd.next(0, 3);
        }
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        a.assign(n, rnd.next(1, 10));
        int spikes = rnd.next(1, min(4, n));
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < spikes; ++i) {
            a[pos[i]] = rnd.next(100000000LL, 1000000000LL);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 15);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 50));
        }
    } else if (mode == 3) {
        n = rnd.next(6, 20);
        long long low = rnd.next(1, 5);
        long long high = rnd.next(20, 200);
        for (int i = 0; i < n; ++i) {
            a.push_back((i % 2 == 0) ? low + rnd.next(0, 3) : high + rnd.next(0, 20));
        }
    } else if (mode == 4) {
        n = rnd.next(3, 10);
        long long cur = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            a.push_back(min(1000000000LL, cur));
            cur *= rnd.next(2, 4);
        }
        shuffle(a.begin(), a.end());
    } else {
        n = rnd.next(16, 60);
        long long limit = rnd.next(10, 10000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1LL, limit));
        }
    }

    if (rnd.next(0, 1) == 1) {
        shuffle(a.begin(), a.end());
    }

    println(n);
    for (long long x : a) {
        println(x);
    }

    return 0;
}
