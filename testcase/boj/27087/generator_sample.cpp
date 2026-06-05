#include "testlib.h"
#include <array>
#include <vector>
using namespace std;

int multipleOfPrimeUpTo100(int p) {
    return p * rnd.next(1, 100 / p);
}

int nonMultipleOfPrimeUpTo100(int p) {
    int x = rnd.next(1, 100);
    while (x % p == 0) x = rnd.next(1, 100);
    return x;
}

int edgeBiasedDimension(int p, bool divisible) {
    if (divisible) return multipleOfPrimeUpTo100(p);

    vector<int> candidates = {1, 100};
    for (int x : {2, 3, 4, 5, 97, 98, 99}) {
        if (x % p != 0) candidates.push_back(x);
    }
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
                                43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

    int T = rnd.next(20, 60);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int p = rnd.any(primes);
        int mode = rnd.next(0, 5);
        array<int, 3> dims{};

        if (mode == 0) {
            for (int i = 0; i < 3; ++i) dims[i] = multipleOfPrimeUpTo100(p);
        } else if (mode == 1) {
            dims = {multipleOfPrimeUpTo100(p), multipleOfPrimeUpTo100(p),
                    nonMultipleOfPrimeUpTo100(p)};
        } else if (mode == 2) {
            dims = {multipleOfPrimeUpTo100(p), nonMultipleOfPrimeUpTo100(p),
                    nonMultipleOfPrimeUpTo100(p)};
        } else if (mode == 3) {
            for (int i = 0; i < 3; ++i) dims[i] = nonMultipleOfPrimeUpTo100(p);
        } else {
            int divisibleCount = rnd.next(0, 3);
            for (int i = 0; i < 3; ++i) {
                dims[i] = edgeBiasedDimension(p, i < divisibleCount);
            }
        }

        shuffle(dims.begin(), dims.end());
        println(dims[0], dims[1], dims[2], p);
    }

    return 0;
}
