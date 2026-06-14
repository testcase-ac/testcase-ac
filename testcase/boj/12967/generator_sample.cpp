#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

const int MAX_A = 100000000;

int boundedMultiple(int base, int lo, int hi) {
    int maxMul = hi / base;
    int minMul = (lo + base - 1) / base;
    if (minMul > maxMul) minMul = 1;
    return base * rnd.next(minMul, maxMul);
}

int randomDivisor(int x) {
    vector<int> divisors;
    for (int d = 1; 1LL * d * d <= x; ++d) {
        if (x % d != 0) continue;
        divisors.push_back(d);
        if (d * d != x) divisors.push_back(x / d);
    }
    return rnd.any(divisors);
}

int coprimeValue(int k) {
    for (int tries = 0; tries < 200; ++tries) {
        int value = rnd.next(1, 1000);
        if (gcd(value, k) == 1) return value;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(3, 8);
        k = rnd.any(vector<int>{1, 2, 6, 30, 210});
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(boundedMultiple(k, 1, min(MAX_A, max(k, 1000))));
            } else {
                a.push_back(rnd.next(1, 200));
            }
        }
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        k = rnd.any(vector<int>{999983, 999979, 999961});
        a.push_back(k);
        for (int i = 1; i < n; ++i) {
            a.push_back(rnd.next(1, 2000));
        }
    } else if (mode == 2) {
        n = rnd.next(6, 18);
        k = rnd.any(vector<int>{360, 840, 2520, 7560, 831600});
        for (int i = 0; i < n; ++i) {
            int d = randomDivisor(k);
            int value = d * rnd.next(1, max(1, min(20, MAX_A / d)));
            a.push_back(value);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 10);
        k = rnd.any(vector<int>{1000000, 999936, 720720});
        for (int i = 0; i < n; ++i) {
            int d = randomDivisor(k);
            int value = boundedMultiple(d, max(1, MAX_A - 500000), MAX_A);
            a.push_back(value);
        }
    } else if (mode == 4) {
        n = rnd.next(10, 30);
        k = rnd.next(2, 1000000);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a.push_back(randomDivisor(k));
            } else if (i % 3 == 1) {
                a.push_back(coprimeValue(k));
            } else {
                a.push_back(rnd.next(1, 1000000));
            }
        }
    } else if (mode == 5) {
        n = rnd.next(60, 140);
        k = rnd.any(vector<int>{64, 729, 4096, 59049, 1000000});
        for (int i = 0; i < n; ++i) {
            int value = 1;
            while (value <= MAX_A / 2 && rnd.next(0, 3) != 0) value *= 2;
            while (value <= MAX_A / 3 && rnd.next(0, 3) != 0) value *= 3;
            a.push_back(value);
        }
    } else {
        n = rnd.next(3, 40);
        k = rnd.next(1, 1000000);
        int limit = rnd.next(10, 100000000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, limit));
        }
    }

    shuffle(a.begin(), a.end());
    println(n, k);
    println(a);
    return 0;
}
