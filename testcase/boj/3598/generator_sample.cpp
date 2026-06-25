#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_H = 1000000000000000000LL;
    const int MAX_A = 100000;

    long long h;
    vector<int> step(3);
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        h = rnd.next(1LL, 30LL);
        int hi = rnd.next(1, 30);
        for (int& x : step) x = rnd.next(1, hi);
    } else if (mode == 1) {
        h = rnd.next(MAX_H - 1000000LL, MAX_H);
        step = {rnd.next(1, 3), rnd.next(99990, MAX_A), rnd.next(99990, MAX_A)};
    } else if (mode == 2) {
        h = rnd.next(1LL, MAX_H);
        int x = rnd.next(1, MAX_A);
        step = {x, x, x};
    } else if (mode == 3) {
        int g = rnd.next(2, 1000);
        int limit = MAX_A / g;
        h = rnd.next(1LL, MAX_H);
        for (int& x : step) x = g * rnd.next(1, limit);
    } else if (mode == 4) {
        h = rnd.next(1LL, 1000000LL);
        step = {1, rnd.next(1, MAX_A), rnd.next(1, MAX_A)};
    } else if (mode == 5) {
        h = rnd.next(1LL, 100000LL);
        int base = rnd.next(1, MAX_A - 2);
        step = {base, base + 1, base + 2};
    } else if (mode == 6) {
        h = rnd.next(1LL, 200000LL);
        for (int& x : step) x = rnd.next(90000, MAX_A);
    } else {
        h = rnd.next(1LL, MAX_H);
        for (int& x : step) x = rnd.next(1, MAX_A);
    }

    shuffle(step.begin(), step.end());

    println(h);
    println(step);
    return 0;
}
