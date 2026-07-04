#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long randomN(int mode) {
    if (mode == 0) return rnd.next(3LL, 30LL);
    if (mode == 1) return rnd.next(3LL, 200LL);
    if (mode == 2) return rnd.next(900000LL, 1200000LL);
    return rnd.next(999999000000LL, 1000000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long n = randomN(mode);
    int maxD = static_cast<int>(min<long long>(n, 1000000LL));

    int k;
    vector<int> d;

    if (mode == 0) {
        k = rnd.next(1, 8);
        for (int i = 0; i < k; ++i) {
            d.push_back(rnd.next(2, maxD));
        }
    } else if (mode == 1) {
        k = rnd.next(6, 18);
        vector<int> pool;
        for (int x = 2; x <= min(maxD, 24); ++x) {
            pool.push_back(x);
        }
        for (int i = 0; i < k; ++i) {
            d.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        k = rnd.next(10, 22);
        vector<int> candidates = {2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20,
                                  24, 25, 27, 30, 36, 40, 45, 60, 72, 90};
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < k; ++i) {
            int value = candidates[i % static_cast<int>(candidates.size())];
            d.push_back(min(value, maxD));
        }
    } else if (mode == 3) {
        k = rnd.next(8, 22);
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
                              37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79};
        shuffle(primes.begin(), primes.end());
        for (int i = 0; i < k; ++i) {
            d.push_back(primes[i % static_cast<int>(primes.size())]);
        }
    } else {
        k = rnd.next(12, 22);
        vector<int> anchors = {2, 3, 5, 7, 11, 999983, 1000000, 999979, 999961};
        for (int i = 0; i < k; ++i) {
            if (rnd.next(0, 2) == 0) {
                d.push_back(min(rnd.any(anchors), maxD));
            } else {
                d.push_back(rnd.next(2, maxD));
            }
        }
    }

    shuffle(d.begin(), d.end());

    println(n);
    println(k);
    println(d);

    return 0;
}
