#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71
    };
    vector<int> ids;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 25);
        int base = rnd.any(primes);
        for (int i = 0; i < n; ++i) {
            int multiplier = rnd.next(1, 1000000 / base);
            ids.push_back(base * multiplier);
        }
    } else if (mode == 1) {
        int clusters = rnd.next(2, 5);
        for (int c = 0; c < clusters; ++c) {
            int base = primes[c];
            int count = rnd.next(1, 6);
            for (int i = 0; i < count; ++i) {
                int other = primes[rnd.next(c + 1, (int)primes.size() - 1)];
                ids.push_back(base * other);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(1, 15);
        vector<int> pool = primes;
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < n; ++i) ids.push_back(pool[i]);
    } else if (mode == 3) {
        int base = rnd.any(vector<int>{2, 3, 5, 7});
        int value = base;
        while (value <= 1000000) {
            ids.push_back(value);
            if (value > 1000000 / base) break;
            value *= base;
        }
        int keep = rnd.next(1, (int)ids.size());
        shuffle(ids.begin(), ids.end());
        ids.resize(keep);
    } else if (mode == 4) {
        int n = rnd.next(2, 25);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                ids.push_back(rnd.any(vector<int>{999983, 999979, 999961}));
            } else {
                ids.push_back(rnd.any(vector<int>{999984, 999990, 1000000}));
            }
        }
    } else {
        int n = rnd.next(2, 30);
        vector<int> anchors = {6, 10, 14, 15, 21, 35, 77, 143};
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                ids.push_back(rnd.any(anchors));
            } else {
                int a = rnd.any(primes);
                int b = rnd.any(primes);
                ids.push_back(a * b);
            }
        }
    }

    shuffle(ids.begin(), ids.end());
    println((int)ids.size());
    println(ids);

    return 0;
}
