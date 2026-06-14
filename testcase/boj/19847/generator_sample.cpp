#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int boundedValue(long long x) {
    return int(max(1LL, min(1000000LL, x)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    vector<int> x;

    if (mode == 0) {
        n = rnd.next(1, 12);
        int value = rnd.next(1, 1000000);
        x.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        int cur = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 20);
            x.push_back(boundedValue(cur));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        int cur = rnd.next(200, 1000000);
        for (int i = 0; i < n; ++i) {
            x.push_back(cur);
            cur = max(1, cur - rnd.next(1, max(1, cur / 4)));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 40);
        int high = rnd.next(1000, 1000000);
        int low = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                x.push_back(rnd.next(max(low, high - 5000), high));
            } else {
                x.push_back(rnd.next(1, low));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 25);
        int cur = rnd.next(2, 2000);
        x.push_back(cur);
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                cur = boundedValue(1LL * cur * rnd.next(1, 8));
            } else {
                cur = max(1, cur / rnd.next(2, 8));
            }
            x.push_back(cur);
        }
    } else if (mode == 5) {
        n = rnd.next(2, 35);
        int base = rnd.next(2, 1000);
        for (int i = 0; i < n; ++i) {
            int jitter = rnd.next(-base / 2, base / 2);
            x.push_back(boundedValue(base + jitter));
            if (rnd.next(0, 3) == 0) {
                base = rnd.next(1, 1000000);
            }
        }
    } else if (mode == 6) {
        n = rnd.next(2, 60);
        for (int i = 0; i < n; ++i) {
            x.push_back(rnd.any(vector<int>{1, 2, 3, 999999, 1000000}));
        }
    } else {
        n = rnd.next(10, 80);
        for (int i = 0; i < n; ++i) {
            x.push_back(rnd.next(1, 1000000));
        }
    }

    println(n);
    println(x);
    return 0;
}
