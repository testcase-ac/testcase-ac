#include "testlib.h"
#include <algorithm>
#include <utility>

using namespace std;

using int64 = long long;

const int64 LIMIT = 1000000000000LL;

int64 triangular(int64 n) {
    return n * (n + 1) / 2;
}

pair<int64, int64> randomFeasibleSplit(int64 n) {
    int64 total = triangular(n);
    int64 lo = max<int64>(0, total - LIMIT);
    int64 hi = min<int64>(LIMIT, total);
    int64 x = rnd.next(lo, hi);
    return {x, total - x};
}

pair<int64, int64> randomInvalidPair(int64 lo, int64 hi) {
    while (true) {
        int64 x = rnd.next(lo, hi);
        int64 y = rnd.next(lo, hi);
        int64 sum2 = 2 * (x + y);
        int64 q = 0;
        while ((q + 1) * (q + 2) <= sum2) q++;
        if (q * (q + 1) != sum2) return {x, y};
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    pair<int64, int64> score;

    if (mode == 0) {
        int64 n = rnd.next(0LL, 35LL);
        score = randomFeasibleSplit(n);
    } else if (mode == 1) {
        int64 n = rnd.next(1LL, 1999999LL);
        score = randomFeasibleSplit(n);
    } else if (mode == 2) {
        int64 n = rnd.next(0LL, 1414213LL);
        int64 total = triangular(n);
        if (rnd.next(0, 1) == 0) {
            score = {total, 0};
        } else {
            score = {0, total};
        }
    } else if (mode == 3) {
        score = randomInvalidPair(0, 1000);
    } else if (mode == 4) {
        int64 n = rnd.next(1LL, 1999999LL);
        score = randomFeasibleSplit(n);
        if (score.first < LIMIT) {
            score.first++;
        } else {
            score.second--;
        }
    } else if (mode == 5) {
        int64 base = rnd.next(999999999000LL, LIMIT);
        int64 other = rnd.next(0LL, 1000LL);
        if (rnd.next(0, 1) == 0) {
            score = {base, other};
        } else {
            score = {other, base};
        }
    } else {
        score = {LIMIT, LIMIT};
    }

    println(score.first, score.second);
    return 0;
}
