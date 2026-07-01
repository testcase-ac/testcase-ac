#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

using Quad = vector<int>;

int quadGcd(const Quad& q) {
    int g = 0;
    for (int x : q) {
        g = gcd(g, x);
    }
    return g;
}

Quad makeCoprime(Quad q) {
    if (quadGcd(q) == 1) {
        return q;
    }

    for (int attempts = 0; attempts < 1000; ++attempts) {
        int pos = rnd.next(0, 3);
        q[pos] = rnd.next(2, 10000);
        if (quadGcd(q) == 1) {
            return q;
        }
    }

    q[rnd.next(0, 3)] = rnd.any(vector<int>{9973, 9991, 10000});
    if (quadGcd(q) != 1) {
        q[0] = 9991;
    }
    return q;
}

Quad randomQuad(int low, int high) {
    Quad q(4);
    for (int& x : q) {
        x = rnd.next(low, high);
    }
    return makeCoprime(q);
}

Quad duplicateHeavy() {
    int base = rnd.next(2, 10000);
    Quad q(4, base);
    int changes = rnd.next(1, 2);
    for (int i = 0; i < changes; ++i) {
        q[rnd.next(0, 3)] = rnd.next(2, 10000);
    }
    return makeCoprime(q);
}

Quad consecutiveNear(int low, int high) {
    int start = rnd.next(low, high - 3);
    Quad q = {start, start + 1, start + 2, start + 3};
    shuffle(q.begin(), q.end());
    return q;
}

Quad sharedFactorMostly() {
    int factor = rnd.next(2, 50);
    Quad q(4);
    for (int i = 0; i < 3; ++i) {
        q[i] = factor * rnd.next(1, 10000 / factor);
    }

    do {
        q[3] = rnd.next(2, 10000);
    } while (gcd(q[3], factor) != 1);

    shuffle(q.begin(), q.end());
    return makeCoprime(q);
}

Quad byMode(int mode) {
    if (mode == 0) {
        return randomQuad(2, 20);
    }
    if (mode == 1) {
        return duplicateHeavy();
    }
    if (mode == 2) {
        return consecutiveNear(2, 80);
    }
    if (mode == 3) {
        return randomQuad(9000, 10000);
    }
    if (mode == 4) {
        return consecutiveNear(9500, 9997);
    }
    return sharedFactorMostly();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(6, 18);
    println(testCases);

    for (int tc = 0; tc < testCases; ++tc) {
        int mode = rnd.next(0, 5);
        Quad q = byMode(mode);
        println(q);
    }

    return 0;
}
