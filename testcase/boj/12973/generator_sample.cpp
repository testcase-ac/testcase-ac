#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int nearMultiple(int p, int maxK, int delta) {
    int k = rnd.next(1, maxK);
    int value = p * k + delta;
    if (value < 2) value += p;
    if (value > 1000000000) value -= p;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 9973};
    int mode = rnd.next(0, 5);
    int n = mode == 0 ? rnd.next(1, 8) : rnd.next(2, 35);
    long long a = rnd.next(1, 30);
    long long b = rnd.next(1, 30);
    if (rnd.next(0, 9) == 0) a = rnd.next(900000000, 1000000000);
    if (rnd.next(0, 9) == 0) b = rnd.next(900000000, 1000000000);

    int p = rnd.any(primes);
    int maxK = max(1, 1000000000 / p);
    vector<int> values(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            values[i] = nearMultiple(p, min(maxK, 30), 0);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            values[i] = nearMultiple(p, min(maxK, 60), rnd.any(vector<int>{-1, 0, 1}));
        }
    } else if (mode == 2) {
        p = rnd.any(vector<int>{5, 7, 11, 13, 17});
        maxK = max(1, 1000000000 / p);
        int left = rnd.next(0, n - 1);
        int right = rnd.next(left, n - 1);
        for (int i = 0; i < n; ++i) {
            if (left <= i && i <= right) {
                values[i] = rnd.next(2, 70);
                while (values[i] % p == 0 || (values[i] + 1) % p == 0 || (values[i] - 1) % p == 0) {
                    values[i] = rnd.next(2, 70);
                }
            } else {
                values[i] = nearMultiple(p, min(maxK, 50), rnd.any(vector<int>{-1, 0, 1}));
            }
        }
    } else if (mode == 3) {
        values[0] = nearMultiple(p, min(maxK, 40), rnd.any(vector<int>{-1, 0, 1}));
        values[n - 1] = nearMultiple(p, min(maxK, 40), rnd.any(vector<int>{-1, 0, 1}));
        for (int i = 1; i + 1 < n; ++i) {
            int q = rnd.any(primes);
            values[i] = nearMultiple(q, min(1000000000 / q, 45), rnd.any(vector<int>{-1, 0, 1}));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            values[i] = rnd.next(2, 25);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            values[i] = rnd.next(999999900, 1000000000);
        }
    }

    if (rnd.next(0, 3) == 0) {
        shuffle(values.begin(), values.end());
    }

    println(n, a, b);
    println(values);

    return 0;
}
