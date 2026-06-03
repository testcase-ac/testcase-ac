#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int oddSize(int lo, int hi) {
    int n = rnd.next(lo, hi);
    if (n % 2 == 0) {
        if (n == hi) {
            --n;
        } else {
            ++n;
        }
    }
    return n;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = (mode == 0) ? 1 : oddSize(3, 29);
    vector<long long> a;
    a.reserve(n);

    if (mode == 0) {
        a.push_back(rnd.next(-1000000000LL, 1000000000LL));
    } else if (mode == 1) {
        long long center = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(center + rnd.next(-2, 2));
        }
    } else if (mode == 2) {
        long long start = rnd.next(-100, 100);
        long long step = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + step * i);
        }
    } else if (mode == 3) {
        vector<long long> pool = {
            -1000000000LL,
            -999999999LL,
            -1LL,
            0LL,
            1LL,
            999999999LL,
            1000000000LL,
        };
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else if (mode == 4) {
        long long pivot = rnd.next(-1000, 1000);
        int lowCount = rnd.next(1, n - 1);
        for (int i = 0; i < lowCount; ++i) {
            a.push_back(pivot - rnd.next(0, 50));
        }
        while ((int)a.size() < n) {
            a.push_back(pivot + rnd.next(0, 50));
        }
    } else {
        long long lo = rnd.next(-1000000, 0);
        long long hi = rnd.next(0, 1000000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    }

    if (rnd.next(0, 1)) {
        sort(a.begin(), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
