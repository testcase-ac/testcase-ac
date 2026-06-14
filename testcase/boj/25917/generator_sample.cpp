#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

bool isPrime(int value) {
    if (value < 2) {
        return false;
    }
    for (int divisor = 2; divisor * divisor <= value; ++divisor) {
        if (value % divisor == 0) {
            return false;
        }
    }
    return true;
}

vector<int> buildPrimePool() {
    vector<int> primes;
    for (int value = 2; value < 400; ++value) {
        if (isPrime(value)) {
            primes.push_back(value);
        }
    }

    for (int value = 9999800; value < 10000000; ++value) {
        if (isPrime(value)) {
            primes.push_back(value);
        }
    }
    return primes;
}

vector<int> makePermutation(int n, int mode) {
    vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
        permutation[i] = i + 1;
    }

    if (mode == 0) {
        return permutation;
    }
    if (mode == 1) {
        reverse(permutation.begin(), permutation.end());
        return permutation;
    }

    shuffle(permutation.begin(), permutation.end());
    return permutation;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r = 1;
    int c = 1;
    if (mode == 0) {
        r = 1;
        c = rnd.next(1, 12);
    } else if (mode == 1) {
        r = rnd.next(2, 12);
        c = 1;
    } else if (mode == 2) {
        r = rnd.next(2, 5);
        c = rnd.next(2, 5);
    } else if (mode == 3) {
        r = rnd.next(6, 12);
        c = rnd.next(2, 4);
    } else if (mode == 4) {
        r = rnd.next(2, 4);
        c = rnd.next(6, 12);
    } else {
        r = rnd.next(10, 20);
        c = rnd.next(1, 3);
    }

    vector<int> primes = buildPrimePool();
    shuffle(primes.begin(), primes.end());
    primes.resize(r * c);

    vector<int> permutation = makePermutation(r, rnd.next(0, 2));

    println(r, c);
    println(primes);
    println(permutation);

    return 0;
}
