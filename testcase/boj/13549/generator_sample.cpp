#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

namespace {
constexpr int kMaxPosition = 100000;

int clampPosition(int x) {
    return max(0, min(kMaxPosition, x));
}

pair<int, int> doublingCase() {
    int start = rnd.next(1, 50000);
    int current = start;
    int steps = rnd.next(1, 12);
    for (int i = 0; i < steps && current * 2 <= kMaxPosition; ++i) {
        current *= 2;
    }
    int offset = rnd.next(-3, 3);
    return {start, clampPosition(current + offset)};
}

pair<int, int> powerNeighborhoodCase() {
    vector<int> powers;
    for (int x = 1; x <= kMaxPosition; x *= 2) {
        powers.push_back(x);
    }
    int base = rnd.any(powers);
    int n = clampPosition(base + rnd.next(-8, 8));
    int k = clampPosition(base * rnd.next(1, 3) + rnd.next(-8, 8));
    return {n, k};
}
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 0;
    int k = 0;

    if (mode == 0) {
        n = rnd.next(0, kMaxPosition);
        k = n;
    } else if (mode == 1) {
        n = rnd.next(1, kMaxPosition);
        k = rnd.next(0, n - 1);
    } else if (mode == 2) {
        n = rnd.any(vector<int>{0, 1, 2, 99998, 99999, 100000});
        k = rnd.next(max(0, n - 20), min(kMaxPosition, n + 20));
    } else if (mode == 3) {
        tie(n, k) = doublingCase();
    } else if (mode == 4) {
        tie(n, k) = powerNeighborhoodCase();
    } else if (mode == 5) {
        n = rnd.next(0, 200);
        k = rnd.next(90000, kMaxPosition);
    } else if (mode == 6) {
        n = rnd.next(90000, kMaxPosition);
        k = rnd.next(0, 200);
    } else {
        n = rnd.next(0, kMaxPosition);
        k = rnd.next(0, kMaxPosition);
    }

    println(n, k);
    return 0;
}
