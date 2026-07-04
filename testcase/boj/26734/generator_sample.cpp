#include "testlib.h"

#include <vector>

using namespace std;

int pickPrime() {
    static const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47
    };
    return rnd.any(primes);
}

int boundedProduct(const vector<int>& factors) {
    long long value = 1;
    for (int factor : factors) {
        value *= factor;
    }
    return static_cast<int>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 4 ? 60 : 30);
    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a.push_back(1);
        }
    } else if (mode == 1) {
        int basePrime = pickPrime();
        for (int i = 0; i < n; ++i) {
            int multiplier = rnd.next(1, 100000000 / basePrime);
            a.push_back(basePrime * multiplier);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a.push_back(pickPrime());
        }
    } else if (mode == 3) {
        int left = pickPrime();
        for (int i = 0; i < n; ++i) {
            int right = pickPrime();
            a.push_back(boundedProduct({left, right, rnd.next(1, 20)}));
            left = right;
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int flavor = rnd.next(0, 3);
            if (flavor == 0) {
                a.push_back(1);
            } else if (flavor == 1) {
                a.push_back(pickPrime() * rnd.next(1, 200));
            } else if (flavor == 2) {
                a.push_back(boundedProduct({pickPrime(), pickPrime(), rnd.next(1, 50)}));
            } else {
                a.push_back(rnd.next(99900000, 100000000));
            }
        }
    } else {
        int blockCount = rnd.next(1, 6);
        for (int block = 0; block < blockCount && static_cast<int>(a.size()) < n; ++block) {
            int shared = pickPrime();
            int length = rnd.next(1, 8);
            for (int i = 0; i < length && static_cast<int>(a.size()) < n; ++i) {
                a.push_back(shared * rnd.next(1, 500));
            }
            if (static_cast<int>(a.size()) < n && rnd.next(0, 1)) {
                a.push_back(1);
            }
        }
        while (static_cast<int>(a.size()) < n) {
            a.push_back(pickPrime() * rnd.next(1, 500));
        }
    }

    println(static_cast<int>(a.size()));
    println(a);

    return 0;
}
