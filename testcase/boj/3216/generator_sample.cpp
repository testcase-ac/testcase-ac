#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<pair<int, int>> segments;

    if (mode == 5) {
        n = rnd.next(60, 140);
    } else {
        n = rnd.next(1, 25);
    }
    segments.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(1, 20);
            int d = max(1, min(1000, base + rnd.next(-3, 3)));
            int v = max(1, min(1000, base + rnd.next(-3, 3)));
            segments.emplace_back(d, v);
        }
    } else if (mode == 1) {
        int heavyPrefix = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, 12);
            int v = (i < heavyPrefix) ? rnd.next(20, 1000) : rnd.next(1, 25);
            segments.emplace_back(d, v);
        }
    } else if (mode == 2) {
        int longPrefix = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            int d = (i < longPrefix) ? rnd.next(20, 1000) : rnd.next(1, 25);
            int v = rnd.next(1, 12);
            segments.emplace_back(d, v);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                segments.emplace_back(rnd.next(1, 8), rnd.next(30, 1000));
            } else {
                segments.emplace_back(rnd.next(30, 1000), rnd.next(1, 8));
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(0, 1) ? 1 : 1000;
            int v = rnd.next(0, 1) ? 1 : 1000;
            if (rnd.next(0, 3) == 0) d = rnd.next(1, 1000);
            if (rnd.next(0, 3) == 0) v = rnd.next(1, 1000);
            segments.emplace_back(d, v);
        }
    } else {
        int dLo = rnd.next(1, 800);
        int dHi = rnd.next(dLo, 1000);
        int vLo = rnd.next(1, 800);
        int vHi = rnd.next(vLo, 1000);
        for (int i = 0; i < n; ++i) {
            segments.emplace_back(rnd.next(dLo, dHi), rnd.next(vLo, vHi));
        }
    }

    if (rnd.next(0, 4) == 0) {
        reverse(segments.begin(), segments.end());
    }

    println(n);
    for (auto [d, v] : segments) {
        println(d, v);
    }

    return 0;
}
