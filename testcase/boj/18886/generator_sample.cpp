#include "testlib.h"

#include <vector>

using namespace std;

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    if (x % 2 == 0) {
        return x == 2;
    }
    for (int d = 3; 1LL * d * d <= x; d += 2) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int randomPrime() {
    static const vector<int> knownPrimes = {
        100000007,
        437122297,
        993244853,
        999999937,
    };

    if (rnd.next(4) == 0) {
        return rnd.any(knownPrimes);
    }

    while (true) {
        int candidate = rnd.next(100000000, 1000000000);
        if (candidate % 2 == 0) {
            --candidate;
        }
        if (candidate < 100000000) {
            candidate += 2;
        }
        if (isPrime(candidate)) {
            return candidate;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 20);
    } else if (mode == 2) {
        n = rnd.next(100, 3000);
    } else if (mode == 3) {
        n = rnd.next(3001, 20000);
    } else if (mode == 4) {
        n = rnd.next(200000, 250000);
    } else {
        static const vector<int> boundaryN = {
            1,
            2,
            3,
            2019,
            2020,
            249999,
            250000,
        };
        n = rnd.any(boundaryN);
    }

    println(n, randomPrime());
    return 0;
}
