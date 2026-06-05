#include "testlib.h"

#include <algorithm>

using namespace std;

const long long MAX_VALUE = 1000000000000000000LL;

long long randomLong(long long low, long long high) {
    return rnd.next(low, high);
}

long long clampToRange(long long value) {
    return max(1LL, min(MAX_VALUE, value));
}

long long valueWithNeed(long long d, long long need, long long maxQuotient) {
    if (need == 0) {
        return d * randomLong(1LL, maxQuotient);
    }
    long long quotient = randomLong(0LL, maxQuotient);
    return quotient * d + (d - need);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long d, n, m, k;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        d = randomLong(1LL, 20LL);
        n = randomLong(1LL, 80LL);
        m = randomLong(1LL, 80LL);
        k = randomLong(1LL, 80LL);
    } else if (mode == 1) {
        d = randomLong(2LL, 1000000LL);
        long long limit = min(MAX_VALUE / d, 1000000LL);
        long long needN = randomLong(0LL, d - 1);
        long long needM = randomLong(0LL, d - 1);
        n = valueWithNeed(d, needN, max(1LL, limit));
        m = valueWithNeed(d, needM, max(1LL, limit));
        k = randomLong(1LL, min(MAX_VALUE, max(1LL, needN + needM + d)));
    } else if (mode == 2) {
        d = randomLong(2LL, 1000000000LL);
        long long limit = max(1LL, MAX_VALUE / d - 1);
        long long needN = randomLong(1LL, d - 1);
        long long needM = randomLong(1LL, d - 1);
        n = valueWithNeed(d, needN, limit);
        m = valueWithNeed(d, needM, limit);
        long long options[5] = {
            max(1LL, min(needN, needM) - 1),
            min(needN, needM),
            max(needN, needM),
            min(MAX_VALUE, needN + needM - 1),
            min(MAX_VALUE, needN + needM)
        };
        k = options[rnd.next(0, 4)];
    } else if (mode == 3) {
        d = randomLong(1LL, 1000000LL);
        long long scale = randomLong(1LL, MAX_VALUE / d);
        n = clampToRange(d * scale);
        m = clampToRange(d * randomLong(1LL, MAX_VALUE / d));
        k = randomLong(1LL, MAX_VALUE);
    } else if (mode == 4) {
        d = randomLong(MAX_VALUE - 1000000LL, MAX_VALUE);
        n = randomLong(max(1LL, d - 1000LL), MAX_VALUE);
        m = randomLong(max(1LL, d - 1000LL), MAX_VALUE);
        k = randomLong(1LL, 2000LL);
    } else if (mode == 5) {
        d = 1;
        n = randomLong(1LL, MAX_VALUE);
        m = randomLong(1LL, MAX_VALUE);
        k = randomLong(1LL, MAX_VALUE);
    } else {
        d = MAX_VALUE;
        n = randomLong(1LL, MAX_VALUE);
        m = randomLong(1LL, MAX_VALUE);
        k = randomLong(1LL, MAX_VALUE);
    }

    println(d);
    println(n, m, k);

    return 0;
}
