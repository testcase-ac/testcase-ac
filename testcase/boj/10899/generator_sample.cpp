#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int p;
    int n;
    vector<int> times;

    if (mode == 0) {
        p = rnd.next(1, 12);
        n = rnd.next(1, 12);
        times.assign(n, 0);
    } else if (mode == 1) {
        p = rnd.next(2, 40);
        n = rnd.next(2, 14);
        int high = p - 1;
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 35) {
                times.push_back(0);
            } else if (rnd.next(0, 99) < 55) {
                times.push_back(high);
            } else {
                times.push_back(rnd.next(0, high));
            }
        }
    } else if (mode == 2) {
        n = rnd.next(3, 15);
        p = rnd.next(n, 80);
        int smallMax = max(1, p / max(2, n));
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(0, smallMax);
            if (i == n - 1 && sum < p) {
                value = min(p - 1, max(value, p - sum));
            }
            times.push_back(value);
            sum += value;
        }
    } else if (mode == 3) {
        p = rnd.next(10, 120);
        n = rnd.next(5, 18);
        int base = rnd.next(0, p - 1);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-2, 2);
            int value = min(p - 1, max(0, base + delta));
            times.push_back(value);
        }
    } else if (mode == 4) {
        p = rnd.next(100000000, 1000000000);
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                times.push_back(rnd.next(0, 20));
            } else if (i % 3 == 1) {
                times.push_back(rnd.next(p - 30, p - 1));
            } else {
                times.push_back(rnd.next(0, p - 1));
            }
        }
    } else if (mode == 5) {
        p = rnd.next(2, 70);
        n = rnd.next(4, 18);
        vector<int> pool;
        int poolSize = rnd.next(2, 5);
        for (int i = 0; i < poolSize; ++i) {
            pool.push_back(rnd.next(0, p - 1));
        }
        for (int i = 0; i < n; ++i) {
            times.push_back(rnd.any(pool));
        }
    } else {
        p = rnd.next(2, 90);
        n = rnd.next(1, 16);
        for (int i = 0; i < n; ++i) {
            times.push_back(rnd.next(0, p - 1));
        }
        sort(times.begin(), times.end());
        if (rnd.next(0, 1)) {
            reverse(times.begin(), times.end());
        }
    }

    shuffle(times.begin(), times.end());

    println(p, n);
    println(times);
    return 0;
}
