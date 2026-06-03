#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long clampToLimit(long long x) {
    const long long limit = 1000000000000000000LL;
    return max(1LL, min(limit, x));
}

long long randomSmooth() {
    const long long limit = 1000000000000000000LL;
    long long x = 1;

    while (x <= limit / 2 && rnd.next(0, 1)) x *= 2;
    while (x <= limit / 3 && rnd.next(0, 1)) x *= 3;

    return x;
}

long long randomNearSmooth() {
    long long base = randomSmooth();
    long long delta = rnd.next(-20, 20);
    if (delta == 0) delta = rnd.next(0, 1) ? 1 : -1;
    return clampToLimit(base + delta);
}

long long randomLarge() {
    const long long limit = 1000000000000000000LL;
    long long hi = rnd.next(1000000LL, limit);
    long long lo = rnd.next(1LL, hi);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 35);
    vector<long long> ns;
    ns.reserve(t);

    while ((int)ns.size() < t) {
        int mode = rnd.next(0, 5);
        long long n;

        if (mode == 0) {
            n = rnd.next(1, 30);
        } else if (mode == 1) {
            n = randomSmooth();
        } else if (mode == 2) {
            n = randomNearSmooth();
        } else if (mode == 3) {
            n = randomLarge();
        } else if (mode == 4) {
            long long edge = rnd.any(vector<long long>{
                1LL,
                2LL,
                3LL,
                10LL,
                999999999999999999LL,
                1000000000000000000LL
            });
            n = clampToLimit(edge + rnd.next(-3, 3));
        } else {
            long long a = randomSmooth();
            long long b = randomSmooth();
            n = clampToLimit(a + b + rnd.next(0, 1000));
        }

        ns.push_back(n);
    }

    shuffle(ns.begin(), ns.end());

    println(t);
    for (long long n : ns) println(n);

    return 0;
}
