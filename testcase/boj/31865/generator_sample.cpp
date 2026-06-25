#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) {
        n = 2;
    } else if (sizeMode <= 2) {
        n = rnd.next(3, 10);
    } else if (sizeMode <= 4) {
        n = rnd.next(11, 30);
    } else {
        n = rnd.next(31, 80);
    }

    println(n);
    for (int i = 2; i <= n; ++i) {
        int pMode = rnd.next(0, 5);
        int p;
        if (pMode == 0) {
            p = 1;
        } else if (pMode == 1) {
            p = i - 1;
        } else if (pMode == 2) {
            p = rnd.next(max(1, i - 4), i - 1);
        } else {
            p = rnd.next(1, i - 1);
        }

        long long remaining = n - i + 1;
        int xMode = rnd.next(0, 7);
        long long x;
        if (xMode == 0) {
            x = 1;
        } else if (xMode == 1) {
            x = remaining;
        } else if (xMode == 2) {
            x = rnd.next(1LL, remaining);
        } else if (xMode == 3) {
            long long multiplier = rnd.next(1LL, 20LL);
            x = min(1000000000LL, remaining * multiplier);
        } else if (xMode == 4) {
            long long base = remaining * rnd.next(1LL, 20LL);
            x = min(1000000000LL, base + rnd.next(0LL, remaining - 1));
        } else if (xMode == 5) {
            x = rnd.next(999999900LL, 1000000000LL);
        } else {
            x = rnd.next(1LL, 1000000000LL);
        }

        println(p, x);
    }

    return 0;
}
