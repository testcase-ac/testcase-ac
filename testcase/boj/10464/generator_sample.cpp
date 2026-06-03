#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(long long x) {
    if (x < 1) return 1;
    if (x > 1000000000LL) return 1000000000;
    return (int)x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(12, 60);
    vector<pair<int, int>> ranges;
    ranges.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 5);
        int s = 1;
        int f = 1;

        if (mode == 0) {
            s = rnd.next(1, 1000000000);
            f = s;
        } else if (mode == 1) {
            s = rnd.next(1, 200);
            f = rnd.next(s, min(1000000000, s + rnd.next(0, 80)));
        } else if (mode == 2) {
            int bit = rnd.next(1, 29);
            int center = 1 << bit;
            s = clampValue((long long)center + rnd.next(-12, 6));
            f = clampValue((long long)center + rnd.next(-6, 16));
            if (s > f) swap(s, f);
        } else if (mode == 3) {
            f = rnd.next(999999900, 1000000000);
            s = rnd.next(max(1, f - rnd.next(0, 150)), f);
        } else if (mode == 4) {
            s = rnd.next(1, 1000000000);
            f = rnd.next(s, min(1000000000, s + rnd.next(0, 1000000)));
        } else {
            int block = rnd.next(1, 250000000);
            int len = rnd.next(0, 2048);
            s = block * 4 - rnd.next(0, 3);
            s = clampValue(s);
            f = clampValue((long long)s + len);
        }

        ranges.emplace_back(s, f);
    }

    println(t);
    for (auto [s, f] : ranges) {
        println(s, f);
    }

    return 0;
}
