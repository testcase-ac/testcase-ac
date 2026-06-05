#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<long long> divisors(long long x) {
    vector<long long> result;
    for (long long d = 1; d * d <= x; ++d) {
        if (x % d == 0) {
            result.push_back(d);
            if (d * d != x) result.push_back(x / d);
        }
    }
    return result;
}

long long randomDivisor(long long x) {
    vector<long long> ds = divisors(x);
    return ds[rnd.next((int)ds.size())];
}

long long makeSmooth(long long limit) {
    vector<int> primes = {2, 3, 5, 7, 11, 13};
    long long value = 1;
    shuffle(primes.begin(), primes.end());
    for (int p : primes) {
        while (value <= limit / p && rnd.next(0, 2) != 0) value *= p;
    }
    return value;
}

void printCase(vector<long long> d, vector<long long> m) {
    shuffle(d.begin(), d.end());
    shuffle(m.begin(), m.end());
    println((int)d.size(), (int)m.size());
    println(d);
    println(m);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<long long> d, m;

    if (mode == 0) {
        long long l = makeSmooth(1000000);
        long long ratio = makeSmooth(1000000000LL / l);
        if (ratio == 1 && rnd.next(0, 1)) ratio = rnd.any(vector<long long>{2, 3, 5});
        while (l > 1000000000LL / ratio) ratio = max(1LL, ratio / 2);
        long long g = l * ratio;

        int n = rnd.next(1, 12);
        int k = rnd.next(1, 12);
        d.push_back(l);
        for (int i = 1; i < n; ++i) d.push_back(randomDivisor(l));
        m.push_back(g);
        for (int i = 1; i < k; ++i) {
            long long maxMul = 1000000000LL / g;
            m.push_back(g * rnd.next(1LL, maxMul));
        }
    } else if (mode == 1) {
        long long l = makeSmooth(10000000);
        if (l == 1) l = 2;
        long long g = makeSmooth(1000000000);
        while (g % l == 0) g = makeSmooth(1000000000);

        int n = rnd.next(2, 14);
        int k = rnd.next(1, 14);
        d.push_back(l);
        for (int i = 1; i < n; ++i) d.push_back(randomDivisor(l));
        m.push_back(g);
        for (int i = 1; i < k; ++i) {
            long long maxMul = 1000000000LL / g;
            m.push_back(g * rnd.next(1LL, maxMul));
        }
    } else if (mode == 2) {
        int n = rnd.next(1, 50);
        int k = rnd.next(1, 50);
        long long anchor = rnd.any(vector<long long>{1LL, 2LL, 4LL, 8LL, 16LL, 1000000000LL});
        d.assign(n, 1);
        m.assign(k, anchor);
        if (rnd.next(0, 1)) d[rnd.next(n)] = randomDivisor(anchor);
    } else if (mode == 3) {
        long long l = rnd.any(vector<long long>{6LL, 12LL, 60LL, 360LL, 2520LL, 27720LL});
        long long ratio = rnd.any(vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL, 10LL, 25LL});
        long long g = l * ratio;
        int n = rnd.next(20, 50);
        int k = rnd.next(20, 50);
        d.push_back(l);
        for (int i = 1; i < n; ++i) d.push_back(randomDivisor(l));
        m.push_back(g);
        for (int i = 1; i < k; ++i) {
            long long maxMul = 1000000000LL / g;
            m.push_back(g * rnd.next(1LL, maxMul));
        }
    } else {
        int n = rnd.next(2, 10);
        int k = rnd.next(1, 10);
        d.push_back(1000000000LL);
        d.push_back(999999937LL);
        for (int i = 2; i < n; ++i) d.push_back(rnd.next(900000000LL, 1000000000LL));
        for (int i = 0; i < k; ++i) m.push_back(rnd.next(1LL, 1000000000LL));
    }

    printCase(d, m);
    return 0;
}
