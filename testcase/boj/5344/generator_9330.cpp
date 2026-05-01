#include "testlib.h"
using namespace std;

long long mygcd(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide overall scale of the test
    int sizeType = rnd.next(0, 2);
    int n;
    long long limit;
    if (sizeType == 0) {
        n = rnd.next(1, 5);
        limit = 1000LL;
    } else if (sizeType == 1) {
        n = rnd.next(3, 9);
        limit = 100000LL;
    } else {
        n = rnd.next(6, 12);
        limit = 1000000000LL;
    }

    vector<pair<long long, long long>> cases;
    cases.reserve(n);

    auto genUniform = [&]() -> pair<long long, long long> {
        long long a = rnd.next(1LL, limit);
        long long b = rnd.next(1LL, limit);
        return {a, b};
    };

    auto genEqual = [&]() -> pair<long long, long long> {
        long long a = rnd.next(1LL, limit);
        return {a, a};
    };

    auto genDivisible = [&]() -> pair<long long, long long> {
        long long maxBase = max(1LL, limit / 2);
        long long base = rnd.next(1LL, maxBase);
        long long maxMul = max(2LL, limit / base);
        if (maxMul > 10) maxMul = 10;
        long long k = rnd.next(2LL, maxMul);
        long long x = base * k;
        if (rnd.next(0, 1) == 0)
            return {x, base};
        else
            return {base, x};
    };

    auto genCoprime = [&]() -> pair<long long, long long> {
        while (true) {
            long long a = rnd.next(1LL, limit);
            long long b = rnd.next(1LL, limit);
            if (mygcd(a, b) == 1) return {a, b};
        }
    };

    auto genPowers = [&]() -> pair<long long, long long> {
        vector<long long> pow2, pow3;
        pow2.push_back(1);
        while (pow2.back() <= limit / 2) pow2.push_back(pow2.back() * 2);
        pow3.push_back(1);
        while (pow3.back() <= limit / 3) pow3.push_back(pow3.back() * 3);

        bool useTwo = rnd.next(0, 1) == 0 || pow3.size() == 1;
        if (useTwo) {
            int i = rnd.next(0, (int)pow2.size() - 1);
            int j = rnd.next(0, (int)pow2.size() - 1);
            return {pow2[i], pow2[j]};
        } else {
            int i = rnd.next(0, (int)pow3.size() - 1);
            int j = rnd.next(0, (int)pow3.size() - 1);
            return {pow3[i], pow3[j]};
        }
    };

    auto genExtremeOrNear = [&]() -> pair<long long, long long> {
        if (limit <= 10) {
            // fallback to near equal small numbers
            long long x = rnd.next(2LL, max(2LL, limit));
            long long y = max(1LL, x - 1);
            return {x, y};
        }
        int kind = rnd.next(0, 1);
        if (kind == 0) {
            // small vs large
            long long smallMax = min(1000LL, limit);
            long long a = rnd.next(1LL, smallMax);
            long long b = rnd.next(max(1LL, limit / 2), limit);
            if (rnd.next(0, 1) == 0) return {a, b};
            else return {b, a};
        } else {
            // near equal
            long long x = rnd.next(2LL, limit);
            long long deltaMax = min(5LL, x - 1);
            long long d = rnd.next(1LL, deltaMax);
            long long y = x - d;
            if (rnd.next(0, 1) == 0) return {x, y};
            else return {y, x};
        }
    };

    auto genByType = [&](int t) -> pair<long long, long long> {
        if (t == 0) return genUniform();
        if (t == 1) return genEqual();
        if (t == 2) return genDivisible();
        if (t == 3) return genCoprime();
        if (t == 4) return genPowers();
        return genExtremeOrNear();
    };

    for (int i = 0; i < n; ++i) {
        pair<long long, long long> p;
        if (i == 0) p = genUniform();          // generic random
        else if (i == 1) p = genEqual();       // a == b
        else if (i == 2) p = genDivisible();   // one divides the other
        else if (i == 3) p = genCoprime();     // gcd = 1
        else if (i == 4) p = genPowers();      // powers of 2 or 3
        else if (i == 5) p = genExtremeOrNear(); // large diff or near equal
        else {
            int t = rnd.next(0, 5);
            p = genByType(t);
        }
        cases.push_back(p);
    }

    println(n);
    for (auto &pr : cases) {
        println(pr.first, pr.second);
    }

    return 0;
}
