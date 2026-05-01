#include "testlib.h"
#include <vector>
#include <cstdint>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const long long PMAX = 1000000000000000LL; // 1e15

    vector<long long> smallPrimes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
        73, 79, 83, 89, 97, 101, 10007, 10009
    };

    // total datasets between 7 and 12
    int K = rnd.next(7, 12);
    vector<long long> ps;

    // ensure at least one of each type
    for (int t = 0; t < 7; t++) {
        long long p;
        if (t == 0) {
            // trivial p = 1
            p = 1;
        } else if (t == 1) {
            // single small prime
            p = rnd.any(smallPrimes);
        } else if (t == 2) {
            // product of two small primes
            long long a = rnd.any(smallPrimes);
            long long b = rnd.any(smallPrimes);
            p = a * b;
        } else if (t == 3) {
            // perfect cube
            long long x = rnd.next(2LL, 10000LL);
            p = x * x * x;
        } else if (t == 4) {
            // product of three small ints
            long long a = rnd.next(2, 1000);
            long long b = rnd.next(2, 1000);
            long long c = rnd.next(2, 1000);
            p = a * b * c;
        } else if (t == 5) {
            // large power of two
            int e = rnd.next(40, 49);
            p = (1LL << e);
        } else {
            // random full-range
            p = rnd.next(1LL, PMAX - 1);
        }
        ps.push_back(p);
    }

    // fill remaining with random types
    for (int i = 7; i < K; i++) {
        int t = rnd.next(0, 6);
        long long p;
        if (t == 0) {
            p = 1;
        } else if (t == 1) {
            p = rnd.any(smallPrimes);
        } else if (t == 2) {
            long long a = rnd.any(smallPrimes);
            long long b = rnd.any(smallPrimes);
            p = a * b;
        } else if (t == 3) {
            long long x = rnd.next(2LL, 10000LL);
            p = x * x * x;
        } else if (t == 4) {
            long long a = rnd.next(2, 1000);
            long long b = rnd.next(2, 1000);
            long long c = rnd.next(2, 1000);
            p = a * b * c;
        } else if (t == 5) {
            int e = rnd.next(40, 49);
            p = (1LL << e);
        } else {
            p = rnd.next(1LL, PMAX - 1);
        }
        ps.push_back(p);
    }

    shuffle(ps.begin(), ps.end());
    for (auto v : ps) println(v);
    println(0);
    return 0;
}
