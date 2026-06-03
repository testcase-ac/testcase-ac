#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static constexpr long long LIMIT = 1000000000LL;

static pair<long long, long long> randomPair(long long lo, long long hi) {
    return {rnd.next(lo, hi), rnd.next(lo, hi)};
}

static pair<long long, long long> applyRandomOperations(long long a, long long b) {
    int steps = rnd.next(1, 18);
    long long c = a;
    long long d = b;

    for (int i = 0; i < steps; ++i) {
        vector<int> choices;
        if (c < LIMIT && d < LIMIT) choices.push_back(0);
        if (c <= LIMIT / 2 && d <= LIMIT / 2) choices.push_back(1);

        if (choices.empty()) break;

        int op = rnd.any(choices);
        if (op == 0) {
            ++c;
            ++d;
        } else {
            c *= 2;
            d *= 2;
        }
    }

    return {c, d};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long a;
    long long b;
    long long c;
    long long d;

    int mode = rnd.next(0, 6);
    if (mode == 0) {
        tie(a, b) = randomPair(1, 200);
        c = a;
        d = b;
    } else if (mode == 1) {
        tie(a, b) = randomPair(1, 10000);
        long long add = rnd.next(1LL, 10000LL);
        c = a + add;
        d = b + add;
    } else if (mode == 2) {
        tie(a, b) = randomPair(1, 5000);
        tie(c, d) = applyRandomOperations(a, b);
    } else if (mode == 3) {
        tie(c, d) = randomPair(1, 200);
        a = rnd.next(c, min(LIMIT, c + 100));
        b = rnd.next(d, min(LIMIT, d + 100));
        if (a == c && b == d) a = min(LIMIT, a + 1);
    } else if (mode == 4) {
        tie(a, b) = randomPair(1, 1000);
        long long delta = rnd.next(0LL, 1000LL);
        c = min(LIMIT, a + delta);
        d = min(LIMIT, b + delta + rnd.next(1LL, 20LL));
    } else if (mode == 5) {
        tie(a, b) = randomPair(1, 100000);
        c = rnd.next(1LL, LIMIT);
        d = rnd.next(1LL, LIMIT);
    } else {
        long long base = rnd.next(LIMIT - 1000, LIMIT);
        a = rnd.next(max(1LL, base - 50), base);
        b = rnd.next(max(1LL, base - 50), base);
        c = rnd.next(base, LIMIT);
        d = rnd.next(base, LIMIT);
    }

    println(a, b, c, d);
    return 0;
}
