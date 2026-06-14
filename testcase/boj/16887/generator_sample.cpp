#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_A = 1000000000000LL;
    const vector<long long> edges = {
        1LL, 2LL, 3LL, 4LL, 15LL, 16LL, 81LL, 82LL,
        6723LL, 6724LL, 50625LL, 50626LL,
        2562991875LL, 2562991876LL, MAX_A
    };

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1LL, 100LL));
        }
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            long long center = rnd.any(edges);
            long long lo = max(1LL, center - 3);
            long long hi = min(MAX_A, center + 3);
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        long long base = rnd.any(edges);
        long long lo = max(1LL, base - 5);
        long long hi = min(MAX_A, base + 5);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        n = rnd.next(1, 16);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(999999000000LL, MAX_A));
        }
    } else if (mode == 4) {
        n = rnd.next(8, 40);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(rnd.any(edges));
            } else if (rnd.next(0, 1) == 0) {
                a.push_back(rnd.next(1LL, 1000000LL));
            } else {
                a.push_back(rnd.next(1LL, MAX_A));
            }
        }
    } else {
        n = rnd.next(1, 25);
        long long value = rnd.any(edges);
        if (rnd.next(0, 1) == 0) {
            value = rnd.next(max(1LL, value - 2), min(MAX_A, value + 2));
        }
        a.assign(n, value);
    }

    shuffle(a.begin(), a.end());
    println(n);
    println(a);

    return 0;
}
