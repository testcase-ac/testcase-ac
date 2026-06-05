#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 97, 101};
    const vector<int> large_primes = {999983, 1000003, 999999937};

    int mode = rnd.next(0, 5);
    int m;
    if (mode <= 2) {
        m = rnd.any(small_primes);
    } else if (mode <= 4) {
        m = rnd.any(large_primes);
    } else {
        m = rnd.next(2) ? rnd.any(small_primes) : rnd.any(large_primes);
    }

    int seed;
    long long x1;
    long long x2;

    if (mode == 0) {
        seed = rnd.next(1, m - 1);
        x1 = seed;
        x2 = seed;
    } else {
        while (true) {
            long long a;
            if (mode == 1) {
                a = 0;
            } else if (mode == 2) {
                a = 1;
            } else {
                a = rnd.next(0, m - 1);
            }
            long long c = rnd.next(0, m - 1);
            seed = rnd.next(1, m - 1);

            x1 = (a * seed + c) % m;
            x2 = (a * x1 + c) % m;
            if (x1 > 0 && x2 > 0) {
                break;
            }
        }
    }

    println(m, seed, x1, x2);
    return 0;
}
