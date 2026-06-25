#include "testlib.h"

#include <algorithm>
#include <array>

using namespace std;

int edgeBiased(int lo, int hi) {
    if (rnd.next(100) < 45) {
        return rnd.any(array<int, 2>{lo, hi});
    }
    return rnd.next(lo, hi);
}

long long powerParam() {
    int mode = rnd.next(5);
    if (mode == 0) return 1;
    if (mode == 1) return 2;
    if (mode == 2) return rnd.next(3, 20);
    if (mode == 3) return rnd.next(1000000, 1000000000);
    return 1000000000LL;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 20);
    } else if (mode == 2) {
        n = rnd.next(90000, 110000);
    } else if (mode == 3) {
        n = rnd.next(1000000, 50000000);
    } else if (mode == 4) {
        n = 50000000;
    } else {
        n = edgeBiased(1, 50000000);
    }

    int a = edgeBiased(1, 100);
    int d = edgeBiased(1, 3);
    int h = edgeBiased(1, 1000);
    int ma = edgeBiased(1, 100);
    int md = edgeBiased(1, 3);
    int mh = edgeBiased(1, 1000);

    if (mode == 0) {
        a = rnd.next(1, 5);
        d = rnd.next(1, 3);
        h = rnd.next(1, 10);
        ma = rnd.next(1, 5);
        md = rnd.next(1, 3);
        mh = rnd.next(1, 10);
    } else if (mode == 4) {
        a = rnd.any(array<int, 3>{1, 50, 100});
        d = rnd.next(1, 3);
        h = rnd.any(array<int, 3>{1, 500, 1000});
        ma = rnd.any(array<int, 3>{1, 50, 100});
        md = rnd.next(1, 3);
        mh = rnd.any(array<int, 3>{1, 500, 1000});
    }

    long long ap = powerParam();
    int aa = edgeBiased(0, 99);
    long long dp = powerParam();
    int da = edgeBiased(0, 2);
    long long hp = powerParam();
    int ha = edgeBiased(0, 999);

    if (mode == 5) {
        ap = rnd.any(array<long long, 4>{1, 2, 999999937LL, 1000000000LL});
        dp = rnd.any(array<long long, 4>{1, 2, 999999937LL, 1000000000LL});
        hp = rnd.any(array<long long, 4>{1, 2, 999999937LL, 1000000000LL});
    }

    println(n);
    println(a, d, h);
    println(ma, md, mh);
    println(ap, aa, dp, da, hp, ha);

    return 0;
}
