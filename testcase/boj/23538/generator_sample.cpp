#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N = 1000000000;

long long powerValue(int base, int exp) {
    long long value = 1;
    for (int i = 0; i < exp; ++i) value *= base;
    return value;
}

int clampN(long long n) {
    return static_cast<int>(max(1LL, min(1LL * MAX_N, n)));
}

int sumExpression(int x, int y, int z, int w, int t) {
    long long n = powerValue(x, 5) + powerValue(y, 4) + powerValue(z, 3)
                  + powerValue(w, 2) + t;
    return clampN(n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 25);
    } else if (mode == 1) {
        int x = rnd.next(1, 8);
        int y = rnd.next(1, 12);
        int z = rnd.next(1, 30);
        int w = rnd.next(1, 200);
        int t = rnd.next(1, 20);
        n = sumExpression(x, y, z, w, t) + rnd.next(-2, 2);
        n = clampN(n);
    } else if (mode == 2) {
        vector<int> anchors = {12, 2019, 1000000};
        int anchor = rnd.any(anchors);
        int delta = rnd.next(-200, 200);
        n = clampN(anchor + delta);
    } else if (mode == 3) {
        int base = rnd.next(1, 250);
        n = clampN(1LL * base * base + rnd.next(1, 5000));
    } else if (mode == 4) {
        int base = rnd.next(1, 1000);
        n = clampN(1LL * base * base * base + rnd.next(1, 100000));
    } else if (mode == 5) {
        n = rnd.next(1, MAX_N);
    } else {
        n = MAX_N - rnd.next(0, 1000000);
    }

    println(n);
    return 0;
}
