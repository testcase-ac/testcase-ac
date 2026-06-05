#include "testlib.h"

#include <algorithm>

using namespace std;

const long long kMaxValue = 1LL << 60;
const long long kMaxRoot = 1LL << 30;

long long square(long long x) {
    return x * x;
}

void printCase(long long a, long long b) {
    println(a, b);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);

    if (mode == 0) {
        long long a = rnd.next(0LL, 200LL);
        long long b = rnd.next(a + 1, min(kMaxValue, a + rnd.next(1LL, 50LL)));
        printCase(a, b);
    } else if (mode == 1) {
        long long root = rnd.next(1LL, 100000LL);
        if (rnd.next(0, 9) == 0) root = rnd.next(kMaxRoot - 1000, kMaxRoot);
        long long s = square(root);
        printCase(s - 1, s);
    } else if (mode == 2) {
        long long root = rnd.next(1LL, 100000LL);
        long long a = square(root);
        long long b = square(root + 1) - 1;
        printCase(a, b);
    } else if (mode == 3) {
        long long root = rnd.next(1LL, 1000000LL);
        if (rnd.next(0, 7) == 0) root = rnd.next(kMaxRoot - 10000, kMaxRoot);
        long long center = square(root);
        long long left = rnd.next(0LL, 20LL);
        long long right = rnd.next(0LL, 20LL);
        long long a = max(0LL, center - left);
        long long b = min(kMaxValue, center + right);
        if (a == b) {
            if (b < kMaxValue) ++b;
            else --a;
        }
        printCase(a, b);
    } else if (mode == 4) {
        long long loRoot = rnd.next(0LL, 1000000LL);
        long long hiRoot = rnd.next(loRoot + 1, min(kMaxRoot, loRoot + rnd.next(1LL, 1000LL)));
        long long a = square(loRoot) + rnd.next(0LL, max(0LL, 2 * loRoot));
        long long b = square(hiRoot) + rnd.next(0LL, min(1000LL, kMaxValue - square(hiRoot)));
        if (a >= b) b = a + 1;
        printCase(a, b);
    } else {
        long long span = rnd.next(1LL, 1000000LL);
        long long a = kMaxValue - span;
        long long b = rnd.next(a + 1, kMaxValue);
        printCase(a, b);
    }

    return 0;
}
