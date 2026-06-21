#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 13};
    int mode = rnd.next(0, 7);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(2, 8);
        m = rnd.next(2, n);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        m = n;
    } else if (mode == 2) {
        vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        n = rnd.any(smallPrimes);
        m = rnd.next(2, n);
    } else if (mode == 3) {
        shuffle(primes.begin(), primes.end());
        n = 1;
        int factors = rnd.next(2, 5);
        for (int i = 0; i < factors; ++i) {
            int p = primes[i];
            int power = p;
            while (power * p <= 1000000 && rnd.next(0, 1)) {
                power *= p;
            }
            if (n <= 1000000 / power) {
                n *= power;
            }
        }
        m = rnd.next(2, min(n, factors + rnd.next(0, 4)));
    } else if (mode == 4) {
        vector<int> composites = {12, 18, 30, 42, 60, 66, 84, 90, 210, 420, 840};
        n = rnd.any(composites);
        m = rnd.next(2, min(n, 8));
    } else if (mode == 5) {
        n = rnd.next(900000, 1000000);
        m = rnd.next(2, min(n, 20));
    } else if (mode == 6) {
        n = 1000000;
        m = rnd.next(2, 100);
    } else {
        n = rnd.next(2, 200);
        m = rnd.next(2, n);
    }

    println(n, m);
    return 0;
}
