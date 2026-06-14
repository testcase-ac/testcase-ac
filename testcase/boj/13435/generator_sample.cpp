#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>

using namespace std;

const int MIN_H = 2;
const int MAX_H = 1000000000;

int clampHeight(long long x) {
    return int(max<long long>(MIN_H, min<long long>(MAX_H, x)));
}

int randomCoprimePartner(int base) {
    int a = base - 1;
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int b = rnd.next(1, MAX_H - 1);
        if (gcd(a, b) == 1) return b + 1;
    }
    return 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = 2;
    int m = 2;

    if (mode == 0) {
        n = rnd.next(2, 20);
        m = rnd.next(2, 20);
    } else if (mode == 1) {
        n = rnd.next(2, 100000);
        m = n;
    } else if (mode == 2) {
        n = rnd.next(2, 100000);
        m = clampHeight((long long)n + rnd.next(-5, 5));
    } else if (mode == 3) {
        n = rnd.next(2, 1000000);
        m = randomCoprimePartner(n);
    } else if (mode == 4) {
        int g = rnd.next(2, 10000);
        int a = rnd.next(1, 10000);
        int b = rnd.next(1, 10000);
        n = clampHeight(1LL + 1LL * g * a);
        m = clampHeight(1LL + 1LL * g * b);
    } else if (mode == 5) {
        n = rnd.next(2, 50);
        m = rnd.next(MAX_H - 1000, MAX_H);
    } else if (mode == 6) {
        n = rnd.next(MAX_H - 1000, MAX_H);
        m = rnd.next(MAX_H - 1000, MAX_H);
    } else {
        int center = rnd.next(2, 200000000);
        int spread = rnd.next(0, 200000000);
        n = clampHeight((long long)center - spread);
        m = clampHeight((long long)center + spread);
    }

    if (rnd.next(2)) swap(n, m);
    println(n, m);
    return 0;
}
