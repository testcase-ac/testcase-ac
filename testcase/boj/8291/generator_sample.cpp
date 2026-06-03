#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 3000000;

int nearMaxValue() {
    return MAX_A - rnd.next(0, 80);
}

int randomPrime() {
    static const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
        41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
    };
    return primes[rnd.next(0, (int)primes.size() - 1)];
}

int boundedProduct(const vector<int>& factors) {
    int value = 1;
    for (int factor : factors) {
        if (value <= MAX_A / factor) value *= factor;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    if (mode == 6) n = rnd.next(60, 180);

    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        vector<int> anchors = {1, 2, 3, 4, 6, 12, 2999999, MAX_A};
        for (int i = 0; i < n; ++i) {
            a.push_back(anchors[rnd.next(0, (int)anchors.size() - 1)]);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 4) == 0 ? rnd.next(2, 40) : 1);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int value = randomPrime();
            if (rnd.next(0, 5) == 0) value *= randomPrime();
            a.push_back(value);
        }
    } else if (mode == 3) {
        int common = randomPrime();
        for (int i = 0; i < n; ++i) {
            int multiplier = rnd.next(1, 120);
            a.push_back(common * multiplier);
        }
    } else if (mode == 4) {
        int distinct = rnd.next(1, min(n, 8));
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) {
            vector<int> factors;
            int count = rnd.next(1, 4);
            for (int j = 0; j < count; ++j) factors.push_back(randomPrime());
            pool.push_back(boundedProduct(factors));
        }
        for (int i = 0; i < n; ++i) {
            a.push_back(pool[rnd.next(0, (int)pool.size() - 1)]);
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            int p = randomPrime();
            int value = p * p;
            while (value <= MAX_A / p && rnd.next(0, 1)) value *= p;
            if (rnd.next(0, 2) == 0) value *= rnd.next(1, min(20, MAX_A / value));
            a.push_back(value);
        }
    } else {
        vector<int> anchors = {1, 2, 3, 5, 30, 210, 2310, 30030, 510510, MAX_A};
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 9);
            if (bucket < 3) {
                a.push_back(rnd.next(1, 200));
            } else if (bucket < 5) {
                a.push_back(anchors[rnd.next(0, (int)anchors.size() - 1)]);
            } else if (bucket < 7) {
                a.push_back(randomPrime() * rnd.next(1, 1000));
            } else {
                a.push_back(nearMaxValue());
            }
        }
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
