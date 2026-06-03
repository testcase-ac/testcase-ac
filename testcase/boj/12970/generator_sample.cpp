#include "testlib.h"

int maxPairs(int n) {
    int a = n / 2;
    int b = n - a;
    return a * b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int k;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = rnd.next(2, 50);
        k = 0;
    } else if (mode == 1) {
        n = rnd.next(2, 50);
        k = maxPairs(n);
    } else if (mode == 2) {
        n = rnd.next(3, 50);
        k = rnd.next(0, maxPairs(n));
    } else if (mode == 3) {
        n = rnd.next(3, 50);
        int feasible = maxPairs(n);
        int statementMax = n * (n - 1) / 2;
        k = rnd.next(feasible + 1, statementMax);
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        k = rnd.next(0, n * (n - 1) / 2);
    } else if (mode == 5) {
        n = rnd.next(40, 50);
        k = rnd.next(0, n * (n - 1) / 2);
    } else if (mode == 6) {
        n = rnd.next(2, 50);
        int feasible = maxPairs(n);
        int delta = rnd.next(0, 3);
        k = feasible - std::min(feasible, delta);
    } else {
        n = rnd.next(2, 50);
        int statementMax = n * (n - 1) / 2;
        int delta = rnd.next(0, std::min(3, statementMax));
        k = statementMax - delta;
    }

    println(n, k);
    return 0;
}
