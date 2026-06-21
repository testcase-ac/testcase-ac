#include "testlib.h"

#include <vector>

using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes;
    for (int p = 2; p < 10000; ++p) {
        if (isPrime(p)) primes.push_back(p);
    }

    int p;
    int n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        p = rnd.any(smallPrimes);
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        p = primes[rnd.next(0, 50)];
        n = rnd.next(1, 2 * (p - 1));
    } else if (mode == 2) {
        p = rnd.any(primes);
        n = rnd.next(1, 10000);
    } else if (mode == 3) {
        p = primes[rnd.next((int)primes.size() - 25, (int)primes.size() - 1)];
        n = rnd.next(9000, 10000);
    } else if (mode == 4) {
        p = rnd.any(primes);
        int period = p - 1;
        n = rnd.next(1, 10000 / period) * period;
    } else {
        p = rnd.any(primes);
        int period = p - 1;
        n = rnd.next(0, 10000 / period) * period + rnd.next(1, period);
        if (n > 10000) n -= period;
    }

    println(p);
    println(n);

    return 0;
}
