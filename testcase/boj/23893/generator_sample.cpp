#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 43, 47,
    };
    const vector<int> mediumPrimes = {
        53, 59, 61, 67, 71, 79, 83, 89, 97, 101, 127, 149, 197,
    };
    const vector<int> largerPrimes = {
        1009, 10007, 99991, 1000003, 999999937,
    };

    int mode = rnd.next(0, 5);
    int p;
    if (mode <= 2) {
        p = rnd.any(smallPrimes);
    } else if (mode == 3) {
        p = rnd.any(mediumPrimes);
    } else {
        p = rnd.any(largerPrimes);
    }

    int n;
    if (mode == 0) {
        n = rnd.next(2, min(p, 12));
    } else if (mode == 1) {
        n = min(p, rnd.next(2, 30));
    } else if (mode == 2) {
        n = p;
    } else {
        n = rnd.next(2, 35);
    }

    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) {
        k = 0;
    } else if (kMode == 1) {
        k = rnd.next(0, min(p - 1, 10));
    } else {
        k = rnd.next(0, p - 1);
    }

    vector<int> values;
    if (mode == 2 && n == p) {
        for (int x = 0; x < p; ++x) {
            values.push_back(x);
        }
    } else if (mode == 3) {
        int start = rnd.next(0, p - 1);
        int step = rnd.next(1, p - 1);
        for (int i = 0; static_cast<int>(values.size()) < n; ++i) {
            int x = static_cast<int>((start + 1LL * i * step) % p);
            if (find(values.begin(), values.end(), x) == values.end()) {
                values.push_back(x);
            }
        }
    } else {
        vector<int> pool;
        if (p <= 2000) {
            for (int x = 0; x < p; ++x) {
                pool.push_back(x);
            }
            shuffle(pool.begin(), pool.end());
            values.assign(pool.begin(), pool.begin() + n);
        } else {
            while (static_cast<int>(values.size()) < n) {
                int x;
                if (rnd.next(0, 2) == 0) {
                    x = rnd.next(0, min(p - 1, 100));
                } else {
                    x = rnd.next(0, p - 1);
                }
                if (find(values.begin(), values.end(), x) == values.end()) {
                    values.push_back(x);
                }
            }
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(values.begin(), values.end());
    }

    println(n, p, k);
    println(values);
    return 0;
}
