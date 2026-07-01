#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int pick(const vector<int>& values) {
    return values[rnd.next((int)values.size())];
}

int boundedMultiple(int base, int maxMul) {
    return base * rnd.next(1, maxMul);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    int x = 2;
    vector<int> a;

    if (mode == 0) {
        int p = pick(primes);
        x = p;
        n = rnd.next(1, 21);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                int v = pick(primes);
                if (v == p) ++v;
                a.push_back(v);
            } else {
                a.push_back(boundedMultiple(p, 40));
            }
        }
    } else if (mode == 1) {
        int p = pick(primes);
        int q = pick(primes);
        while (q == p) q = pick(primes);
        x = p * q;
        n = rnd.next(2, 24);
        for (int i = 0; i < n; ++i) {
            int kind = rnd.next(0, 4);
            if (kind == 0) a.push_back(boundedMultiple(p, 35));
            else if (kind == 1) a.push_back(boundedMultiple(q, 35));
            else if (kind == 2) a.push_back(boundedMultiple(p * q, 20));
            else a.push_back(1 + 2 * rnd.next(0, 35));
        }
    } else if (mode == 2) {
        int p = pick(vector<int>{2, 3, 5});
        int exp = rnd.next(2, 8);
        x = 1;
        for (int i = 0; i < exp; ++i) x *= p;
        n = rnd.next(3, 22);
        for (int i = 0; i < n; ++i) {
            int e = rnd.next(0, exp);
            int v = 1;
            for (int j = 0; j < e; ++j) v *= p;
            a.push_back(v * rnd.next(1, 9));
        }
    } else if (mode == 3) {
        x = 83160; // Many small divisors, still easy to inspect.
        n = rnd.next(8, 24);
        vector<int> divisors;
        for (int d = 1; d * d <= x; ++d) {
            if (x % d != 0) continue;
            divisors.push_back(d);
            if (d * d != x) divisors.push_back(x / d);
        }
        for (int i = 0; i < n; ++i) {
            int d = pick(divisors);
            a.push_back(d * rnd.next(1, 7));
        }
    } else if (mode == 4) {
        x = pick(vector<int>{999983, 999979, 1000000000});
        n = rnd.next(1, 18);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(rnd.next(1, 100));
            } else {
                int g = gcd(x, rnd.next(2, 2000));
                a.push_back(g == 1 ? x : g * rnd.next(1, 1000));
            }
        }
    } else {
        x = rnd.next(2, 500);
        n = rnd.next(1, 24);
        int repeated = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) a.push_back(repeated);
            else a.push_back(rnd.next(1, 1000));
        }
    }

    shuffle(a.begin(), a.end());
    println(n, x);
    println(a);
    return 0;
}
