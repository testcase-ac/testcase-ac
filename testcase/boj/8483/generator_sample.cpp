#include "testlib.h"

#include <algorithm>

using namespace std;

static const long long MAX_AB = 1000000000LL;
static const long long MAX_FACTOR = 1000000000LL;

long long randLong(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

long long clampC(long long c, long long a, long long b) {
    long long limit = min(a, b) * MAX_FACTOR;
    return max(1LL, min(c, limit));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long a;
    long long b;
    long long c;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        a = randLong(1, 30);
        b = randLong(1, 30);
        c = randLong(1, min(a, b) * 30);
    } else if (mode == 1) {
        a = randLong(1, 2000);
        b = a;
        long long k = randLong(1, 1000000);
        c = clampC(a * k + rnd.next(-2LL, 2LL), a, b);
    } else if (mode == 2) {
        long long g = randLong(2, 100000);
        a = g * randLong(1, MAX_AB / g);
        b = g * randLong(1, MAX_AB / g);
        long long k = randLong(1, 1000000000LL / g);
        c = clampC(g * k + rnd.next(-1LL, 1LL), a, b);
    } else if (mode == 3) {
        a = randLong(MAX_AB - 1000000, MAX_AB);
        b = randLong(MAX_AB - 1000000, MAX_AB);
        c = clampC(randLong(min(a, b) * (MAX_FACTOR - 1000), min(a, b) * MAX_FACTOR), a, b);
    } else if (mode == 4) {
        a = randLong(1, 1000);
        b = randLong(MAX_AB - 1000000, MAX_AB);
        c = clampC(randLong(1, a * MAX_FACTOR), a, b);
    } else {
        a = randLong(1, MAX_AB);
        b = randLong(1, MAX_AB);
        long long base = rnd.next(0, 1) ? a : b;
        long long k = randLong(1, max(1LL, min(a, b) * MAX_FACTOR / base));
        c = clampC(base * k + rnd.next(-3LL, 3LL), a, b);
    }

    println(a, b, c);
    return 0;
}
