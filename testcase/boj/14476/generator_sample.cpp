#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

const long long MAX_A = 2000000000LL;

long long randomMultiple(long long base, long long maxFactor) {
    return base * rnd.next(1LL, maxFactor);
}

vector<long long> makeSolvableCase(int n, long long g) {
    vector<long long> a;
    a.reserve(n);

    long long maxFactor = MAX_A / g;
    for (int i = 0; i < n - 1; ++i) {
        long long factor = rnd.next(1LL, maxFactor);
        if (rnd.next(0, 3) == 0) factor *= rnd.next(1LL, min(5LL, maxFactor / factor));
        a.push_back(g * factor);
    }

    long long removed;
    do {
        removed = rnd.next(1LL, MAX_A);
    } while (removed % g == 0);
    a.push_back(removed);

    shuffle(a.begin(), a.end());
    return a;
}

vector<long long> makeNoAnswerCase(int n, long long g) {
    vector<long long> a;
    a.reserve(n);

    long long maxFactor = MAX_A / g;
    for (int i = 0; i < n; ++i) {
        a.push_back(randomMultiple(g, maxFactor));
    }

    return a;
}

vector<long long> makePairGcdCase(int n) {
    vector<long long> primes = {2, 3, 5, 7, 11, 13, 17};
    long long base = primes[rnd.next(0, (int)primes.size() - 1)];
    long long special = primes[rnd.next(0, (int)primes.size() - 1)];
    while (special == base) special = primes[rnd.next(0, (int)primes.size() - 1)];

    vector<long long> a;
    a.reserve(n);
    for (int i = 0; i < n; ++i) {
        long long multiplier = rnd.next(1LL, MAX_A / (base * special));
        long long value = base * multiplier;
        if (i % 2 == 0) value *= special;
        a.push_back(value);
    }

    shuffle(a.begin(), a.end());
    return a;
}

vector<long long> makeLargeBoundaryCase(int n) {
    vector<long long> choices = {
        1,
        2,
        999999937LL,
        1000000000LL,
        1999999999LL,
        2000000000LL,
    };

    vector<long long> a;
    a.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 3) == 0) {
            a.push_back(rnd.any(choices));
        } else {
            long long g = rnd.any(vector<long long>{2, 4, 8, 16, 1000, 100000});
            a.push_back(randomMultiple(g, MAX_A / g));
        }
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(4, 30);
    if (rnd.next(0, 9) == 0) n = rnd.next(31, 80);

    vector<long long> a;
    if (mode == 0) {
        long long g = rnd.any(vector<long long>{2, 3, 4, 6, 12, 1000, 99991});
        a = makeSolvableCase(n, g);
    } else if (mode == 1) {
        long long g = rnd.any(vector<long long>{1, 2, 5, 10, 100, 1000000});
        a = makeNoAnswerCase(n, g);
    } else if (mode == 2) {
        a = makePairGcdCase(n);
    } else if (mode == 3) {
        a = makeLargeBoundaryCase(n);
    } else {
        a.reserve(n);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1LL, MAX_A));
    }

    println(n);
    println(a);

    return 0;
}
