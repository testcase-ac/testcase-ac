#include "testlib.h"

#include <vector>

using namespace std;

int modValue(int x, int m) {
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
                          43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

    int mode = rnd.next(0, 5);
    int m = rnd.any(primes);
    int seed = rnd.next(1, m - 1);
    int a = rnd.next(0, m - 1);
    int c = rnd.next(0, m - 1);

    if (mode == 0) {
        m = rnd.next(0, 1) ? 2 : 97;
        seed = rnd.next(1, m - 1);
        a = rnd.next(0, m - 1);
        c = rnd.next(0, m - 1);
    } else if (mode == 1) {
        a = 0;
        c = rnd.next(1, m - 1);
    } else if (mode == 2) {
        a = 1;
        c = rnd.next(0, m - 1);
    } else if (mode == 3) {
        c = 0;
        a = rnd.next(1, m - 1);
    } else if (mode == 4) {
        a = rnd.next(0, m - 1);
        c = modValue(seed - a * seed, m);
    }

    int x1 = modValue(a * seed + c, m);
    int x2 = modValue(a * x1 + c, m);

    while (x1 == 0 || x2 == 0) {
        m = rnd.any(primes);
        seed = rnd.next(1, m - 1);
        a = rnd.next(0, m - 1);
        c = rnd.next(0, m - 1);
        x1 = modValue(a * seed + c, m);
        x2 = modValue(a * x1 + c, m);
    }

    println(m, seed, x1, x2);
    return 0;
}
