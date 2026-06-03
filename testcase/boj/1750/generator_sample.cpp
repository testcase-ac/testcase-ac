#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static int randomPrime() {
    static const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
        41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
    };
    return rnd.any(primes);
}

static int boundedMultiple(int base, int loFactor, int hiFactor) {
    hiFactor = min(hiFactor, 100000 / base);
    loFactor = min(loFactor, hiFactor);
    return base * rnd.next(loFactor, hiFactor);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    vector<int> values;

    if (mode == 0) {
        n = rnd.next(1, 12);
        values.resize(n);
        int ones = rnd.next(1, min(n, 3));
        for (int i = 0; i < ones; ++i) values[i] = 1;
        for (int i = ones; i < n; ++i) values[i] = rnd.next(1, 100000);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        int base = randomPrime();
        for (int i = 0; i < n; ++i) values.push_back(boundedMultiple(base, 1, 1200));
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        int a = randomPrime();
        int b = randomPrime();
        while (b == a) b = randomPrime();
        for (int i = 0; i < n; ++i) {
            int factor = (i % 3 == 0 ? a : (i % 3 == 1 ? b : a * b));
            values.push_back(boundedMultiple(factor, 1, 700));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 35);
        int distinct = rnd.next(1, min(n, 6));
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) pool.push_back(rnd.next(2, 100000));
        for (int i = 0; i < n; ++i) values.push_back(rnd.any(pool));
    } else if (mode == 4) {
        n = rnd.next(8, 50);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                values.push_back(rnd.next(90000, 100000));
            } else {
                values.push_back(rnd.next(2, 500));
            }
        }
    } else {
        n = rnd.next(2, 16);
        int currentGcd = 0;
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(2, 100000);
            if (i == n - 1 && currentGcd > 1) {
                for (int tries = 0; tries < 100 && gcd(currentGcd, x) != 1; ++tries) {
                    x = rnd.next(2, 100000);
                }
            }
            currentGcd = currentGcd == 0 ? x : gcd(currentGcd, x);
            values.push_back(x);
        }
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int x : values) println(x);

    return 0;
}
