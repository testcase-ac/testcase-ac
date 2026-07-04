#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampToN(long long value, int n) {
    if (value < 1) return 1;
    if (value > n) return n;
    return static_cast<int>(value);
}

int randomPrimeLike(int n) {
    static const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    };

    vector<int> candidates;
    for (int p : primes) {
        if (p <= n) candidates.push_back(p);
    }
    if (candidates.empty()) return 1;
    return rnd.any(candidates);
}

int randomPower(int n) {
    if (n < 2) return 1;

    int base = rnd.next(2, min(n, 20));
    long long value = base;
    int exponent = rnd.next(1, 6);
    for (int i = 1; i < exponent && value * base <= n; ++i) {
        value *= base;
    }
    return static_cast<int>(value);
}

int randomComposite(int n) {
    if (n < 4) return rnd.next(1, n);

    int a = rnd.next(2, min(n / 2, 10000));
    int b = rnd.next(2, min(n / a, 10000));
    return clampToN(1LL * a * b, n);
}

int randomNearN(int n) {
    int width = min(n - 1, 1000);
    if (width == 0) return 1;
    return n - rnd.next(0, width);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(21, 1000);
    } else if (mode == 2) {
        n = rnd.next(1001, 100000);
    } else if (mode == 3) {
        n = rnd.next(99900000, 100000000);
    } else if (mode == 4) {
        static const vector<int> landmarks = {
            1, 2, 6, 20, 10000, 99999999, 100000000,
        };
        n = rnd.any(landmarks);
    } else {
        n = rnd.wnext(100000000, -4) + 1;
    }

    int q = rnd.next(1, 30);
    vector<int> queries;
    queries.reserve(q);

    vector<int> fixed = {1, n};
    if (n >= 2) fixed.push_back(2);
    if (n >= 3) fixed.push_back(3);
    if (n >= 4) fixed.push_back(4);
    shuffle(fixed.begin(), fixed.end());

    for (int x : fixed) {
        if (static_cast<int>(queries.size()) < q) queries.push_back(x);
    }

    while (static_cast<int>(queries.size()) < q) {
        int kind = rnd.next(0, 5);
        int x;
        if (kind == 0) {
            x = rnd.next(1, n);
        } else if (kind == 1) {
            x = randomPrimeLike(n);
        } else if (kind == 2) {
            x = randomPower(n);
        } else if (kind == 3) {
            x = randomComposite(n);
        } else if (kind == 4) {
            x = randomNearN(n);
        } else {
            x = clampToN(rnd.any(fixed) + rnd.next(-3, 3), n);
        }
        queries.push_back(x);
    }

    shuffle(queries.begin(), queries.end());

    println(n, q);
    for (int x : queries) {
        println(x);
    }

    return 0;
}
