#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000LL;

long long multiplySmallPrimes(int terms) {
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    long long value = 1;
    for (int i = 0; i < terms; ++i) {
        vector<int> candidates;
        for (int p : primes) {
            if (value <= LIMIT / p) candidates.push_back(p);
        }
        if (candidates.empty()) break;
        value *= rnd.any(candidates);
    }
    return value;
}

long long primePower() {
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    long long value = rnd.any(primes);
    long long p = value;
    int extra = rnd.next(0, 20);
    while (extra-- > 0 && value <= LIMIT / p) value *= p;
    return value;
}

long long extendAncestor(long long ancestor) {
    vector<int> factors = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    if (ancestor > 1) {
        factors.clear();
        for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}) {
            if (ancestor % p == 0) {
                for (int q : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}) {
                    if (q <= p) factors.push_back(q);
                }
                break;
            }
        }
    }

    long long value = ancestor;
    int terms = rnd.next(1, 8);
    while (terms-- > 0) {
        vector<int> candidates;
        for (int p : factors) {
            if (value <= LIMIT / p) candidates.push_back(p);
        }
        if (candidates.empty()) break;
        value *= rnd.any(candidates);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long a = 1;
    long long b = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        a = rnd.next(1LL, LIMIT);
        b = rnd.next(1LL, LIMIT);
    } else if (mode == 1) {
        a = multiplySmallPrimes(rnd.next(1, 18));
        b = multiplySmallPrimes(rnd.next(1, 18));
    } else if (mode == 2) {
        a = primePower();
        b = primePower();
    } else if (mode == 3) {
        long long ancestor = multiplySmallPrimes(rnd.next(0, 5));
        a = extendAncestor(ancestor);
        b = extendAncestor(ancestor);
    } else if (mode == 4) {
        vector<long long> edges = {1, LIMIT, LIMIT - rnd.next(0, 1000), primePower()};
        shuffle(edges.begin(), edges.end());
        a = edges[0];
        b = edges[1];
    } else {
        a = extendAncestor(1);
        b = rnd.next(1, 2) == 1 ? 1 : multiplySmallPrimes(rnd.next(1, 12));
    }

    println(a, b);
    return 0;
}
