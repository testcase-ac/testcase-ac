#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int MAX_N = 20000;
const long long BASE = 1000000000LL;

long long scoreFromPair(int n, int x, int a) {
    return (BASE * x) / (2LL * n) + a;
}

pair<int, long long> makeCase(int mode) {
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 200);
    } else if (mode == 2) {
        n = rnd.next(1000, MAX_N);
    } else if (mode == 3) {
        vector<int> boundaries = {1, 2, 3, 10, 1000, MAX_N};
        n = rnd.any(boundaries);
    } else {
        n = rnd.next(1, MAX_N);
    }

    int scoreMode = rnd.next(0, 5);
    long long s;
    if (scoreMode == 0) {
        vector<long long> boundaries = {0, 1, BASE / 2, BASE - 1, BASE, BASE + n};
        s = rnd.any(boundaries);
    } else if (scoreMode <= 2) {
        int x = rnd.next(0, 2 * n);
        int minA = max(0, x - n);
        int maxA = min(n, x / 2);
        int a = rnd.next(minA, maxA);
        s = scoreFromPair(n, x, a);
    } else if (scoreMode == 3) {
        int x = rnd.next(0, 2 * n);
        int minA = max(0, x - n);
        int maxA = min(n, x / 2);
        int a = rnd.next(minA, maxA);
        long long delta = rnd.next(0, 1) == 0 ? -1 : 1;
        s = scoreFromPair(n, x, a) + delta;
        s = max(0LL, min(BASE + n, s));
    } else {
        s = rnd.next(0LL, BASE + n);
    }

    return {n, s};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 40);
    println(t);

    for (int i = 0; i < t; ++i) {
        auto tc = makeCase(i % 5);
        println(tc.first, tc.second);
    }

    return 0;
}
