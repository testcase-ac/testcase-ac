#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long clampN(long long n) {
    return max(2LL, min(1000000000LL, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    if (mode == 0) {
        t = rnd.next(1, 5);
    } else if (mode == 1) {
        t = rnd.next(6, 20);
    } else {
        t = rnd.next(1, 12);
    }

    vector<long long> special = {
        2LL, 3LL, 4LL, 5LL, 6LL, 7LL, 8LL, 9LL, 10LL,
        15LL, 16LL, 17LL, 31LL, 32LL, 33LL,
        999999937LL, 999999999LL, 1000000000LL,
    };

    vector<long long> ns;
    for (int i = 0; i < t; ++i) {
        int kind = rnd.next(0, 6);
        long long n;
        if (kind == 0) {
            n = rnd.any(special);
        } else if (kind == 1) {
            n = rnd.next(2, 30);
        } else if (kind == 2) {
            long long base = 1LL << rnd.next(1, 29);
            n = clampN(base + rnd.next(-3, 3));
        } else if (kind == 3) {
            long long k = rnd.next(2, 40000);
            n = clampN(k * k + rnd.next(-2, 2));
        } else if (kind == 4) {
            n = rnd.next(900000000LL, 1000000000LL);
        } else {
            n = rnd.next(2LL, 1000000LL);
        }
        ns.push_back(n);
    }

    if (rnd.next(0, 3) == 0) {
        shuffle(ns.begin(), ns.end());
    }

    println(t);
    for (long long n : ns) {
        printf("\n");
        println(n);
    }

    return 0;
}
