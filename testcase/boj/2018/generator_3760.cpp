#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (int i = 3; i * 1LL * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose a type of N for diversity
    // 0: very small, 1: small-medium, 2: large-random
    // 3: power of two, 4: perfect square, 5: large prime
    int type = rnd.next(0, 5);
    int N;
    switch (type) {
        case 0:
            // very small, hand-checkable
            N = rnd.next(1, 20);
            break;
        case 1:
            // small to medium
            N = rnd.next(20, 100000);
            break;
        case 2:
            // large random
            N = rnd.next(100001, 10000000);
            break;
        case 3: {
            // power of two up to ~8 million
            int e = rnd.next(0, 23);
            N = 1 << e;
            // ensure within bounds
            if (N < 1 || N > 10000000)
                N = 1 << rnd.next(0, 23);
            break;
        }
        case 4: {
            // perfect square up to 10^7
            int k = rnd.next(1, 3162);
            N = k * k;
            break;
        }
        case 5: {
            // large prime near [1e6, 1e7]
            int x = rnd.next(1000000, 10000000);
            int tries = 0;
            while (!isPrime(x)) {
                x++;
                if (x > 10000000) x = 2;
                if (++tries > 20000000) break;
            }
            N = x;
            break;
        }
        default:
            N = rnd.next(1, 10000000);
    }

    // Output single test: N
    println(N);
    return 0;
}
