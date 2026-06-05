#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long step(long long a, long long x, long long c, long long m) {
    return (a * x + c) % m;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    vector<int> mediumPrimes = {41, 43, 47, 53, 59, 61, 67, 71, 79, 83, 89, 97};
    vector<int> largePrimes = {9973, 10007, 32749, 65537, 99991};

    int mode = rnd.next(0, 5);
    int m;
    int seed;
    int a;
    int c;
    int x1;
    int x2;

    if (mode == 0) {
        m = rnd.any(smallPrimes);
        seed = rnd.next(1, m - 1);
        a = 1;
        c = 0;
        x1 = seed;
        x2 = seed;
    } else if (mode == 1) {
        m = rnd.any(smallPrimes);
        seed = rnd.next(1, m - 1);
        c = rnd.next(1, m - 1);
        a = 0;
        x1 = c;
        x2 = c;
    } else if (mode == 2) {
        m = rnd.any(mediumPrimes);
        seed = rnd.next(1, m - 1);
        a = rnd.next(1, m - 1);
        c = 0;
        x1 = step(a, seed, c, m);
        x2 = step(a, x1, c, m);
    } else if (mode == 3) {
        m = rnd.any(mediumPrimes);
        seed = rnd.next(1, m - 1);
        a = rnd.next(0, m - 1);
        c = rnd.next(0, m - 1);
        x1 = step(a, seed, c, m);
        x2 = step(a, x1, c, m);
    } else if (mode == 4) {
        m = rnd.any(largePrimes);
        seed = rnd.next(1, m - 1);
        a = rnd.next(max(0, m - 20), m - 1);
        c = rnd.next(0, min(m - 1, 20));
        x1 = step(a, seed, c, m);
        x2 = step(a, x1, c, m);
    } else {
        m = rnd.any(mediumPrimes);
        seed = rnd.next(1, m - 1);
        x1 = rnd.next(1, m - 1);
        x2 = rnd.next(1, m - 1);
        if (seed == x1 && x1 != x2) {
            x2 = x1;
        }
    }

    while (x1 == 0 || x2 == 0) {
        seed = rnd.next(1, m - 1);
        a = rnd.next(0, m - 1);
        c = rnd.next(0, m - 1);
        x1 = step(a, seed, c, m);
        x2 = step(a, x1, c, m);
    }

    println(m, seed, x1, x2);
    return 0;
}
